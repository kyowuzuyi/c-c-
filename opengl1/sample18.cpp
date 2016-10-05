#include <stdio.h>
#include <stdlib.h>//glut.hより先にインクルード
#include <gl/glew.h>//glut.hより先にインクルード
#include <gl/glut.h>
#include <cv.h>//OpenCVのヘッダ
#include <highgui.h>//OpenCVのヘッダ

//画像ファイル名
const char *imagefile = "block3.png";

//テクスチャId
int filter = 0;
GLuint texId[4];


//--- 各種コールバック関数---//
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glBindTexture(GL_TEXTURE_2D,texId[filter]);//バインド
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.f);	glVertex3f(-0.5f,-0.5f,0.f);
	glTexCoord2f(1.f, 0.f);	glVertex3f(0.5f,-0.5f,0.f);
	glTexCoord2f(1.f, 1.f);	glVertex3f(0.5f,0.5f,0.f);
	glTexCoord2f(0.f, 1.f);	glVertex3f(-0.5f,0.5f,0.f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(30.0,double(w)/h,0.1,200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'f':
		filter = ++filter % 4;//0～の間をとる
		printf("now filter is %d\n",filter);
		break;

	case 'q':
	case 'Q':
	case '\033'://Escキー
		glDeleteTextures(4,texId);//テクスチャの破棄
		exit(0);
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

//その他初期設定
void otherInit(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_DEPTH);
}

//テクスチャの読み込み
void LoadTexture(void)
{
	int loop;

	IplImage *imgA = cvLoadImage(imagefile,1);
	if(imgA==NULL)
	{
		puts("Can't Load Image");
		exit(0);
	}

	cvConvertImage(imgA,imgA,
		CV_CVTIMG_FLIP|CV_CVTIMG_SWAP_RB);

	//ミップマップの縮小フィルタ
	GLenum minFilter[4]={
		GL_NEAREST_MIPMAP_NEAREST,
		GL_LINEAR_MIPMAP_NEAREST,
		GL_NEAREST_MIPMAP_LINEAR,
		GL_LINEAR_MIPMAP_LINEAR};


	glGenTextures(4,texId);
	for(loop = 0;loop < 4;++loop)
	{
		glBindTexture(GL_TEXTURE_2D,texId[loop]);
		//拡大・縮小フィルタ
		glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER,minFilter[loop]);
		//ミップマップ作成
		gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,
			imgA->width,imgA->height,
			GL_RGB,GL_UNSIGNED_BYTE,imgA->imageData);
	}

	cvReleaseImage(&imgA);
}

//---- GLEWのセットアップと拡張機能の確認----//
void setUpGLEW(void)
{
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		fprintf(stderr,"Error: %s\n",
			glewGetErrorString(err) );
		exit(0);
	}
	//拡張機能の確認
	if(glewIsSupported("GL_ARB_texture_non_power_of_two"))
	{
		puts("[GL_ARB_texture_non_power_of_two] : OK");
	}else
	{
		puts("[GL_ARB_texture_non_power_of_two] : BAD");
	}
}


//---- メイン関数 ----//
int main(int argc, char *argv[])
{
	//glutの初期設定
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("TextureMaping with Mipmap");
	
	setUpGLEW();//GLEWのセットアップ

	//コールバック関数登録
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	otherInit();//その他初期設定
	LoadTexture();//テクスチャの読み込み

	glutMainLoop();
	return 0;
}
