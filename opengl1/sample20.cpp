#include <stdio.h>
#include <stdlib.h>//glut.hより先にインクルード
#include <gl/glut.h>
#include <cv.h>//OpenCVのヘッダ
#include <highgui.h>//OpenCVのヘッダ

//外部変数
int alphaFlag = 0;
GLclampf alphaRef = 0.5f;
const char *imagefile = "star2.png";//画像ファイル名
GLuint texId;//テクスチャId

//--------  各種コールバック関数------//
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glBindTexture(GL_TEXTURE_2D,texId);//バインド
	glColor3f(0.f, 1.f, 0.f);//緑色
	
	//フラグによる場合分け
	if(alphaFlag){
		glEnable(GL_ALPHA_TEST);
	}else{
		glDisable(GL_ALPHA_TEST);
	}

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.f);	glVertex3f(-0.5f,-0.5f,0.f);
	glTexCoord2f(1.f, 0.f);	glVertex3f(0.5f,-0.5f,0.f);
	glTexCoord2f(1.f, 1.f);	glVertex3f(0.5f,0.5f,0.f);
	glTexCoord2f(0.f, 1.f);	glVertex3f(-0.5f,0.5f,0.f);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	
	glColor3f(1.f, 1.f, 1.f);

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
	case 'a':
		alphaFlag = ++alphaFlag % 2;//0か1をとる
		if(alphaFlag){
			puts("[ALPHA TEST]: ON");
		}else{
			puts("[ALPHA TEST]: OFF");
		}
		break;
	case 'r':
		alphaRef +=0.05f;
		if(alphaRef > 1.f) {alphaRef = 0.f;}
		glAlphaFunc(GL_LESS,alphaRef);//αテストの式
		printf("alphaRef = %f\n",alphaRef);
		break;

	case 'q':
	case 'Q':
	case '\033'://Escキー
		glDeleteTextures(1,&texId);//テクスチャの破棄
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
	glAlphaFunc(GL_LESS,alphaRef);//αテストの式
}

//--------  拡張機能の確認-----//
void checkExtension(void)
{
	//拡張機能の確認
	if(	glutExtensionSupported(
		"GL_ARB_texture_non_power_of_two"))
	{
		puts("ARB_texture_non_power_of_two : OK");
	}else{
		puts("ARB_texture_non_power_of_two : BAD");
	}	
}

//-------- テクスチャの読み込み----//
void LoadTexture(void)
{
	//グレイスケール画像で読み込む
	IplImage *imgA = cvLoadImage(imagefile,0);
	if(imgA == NULL)
	{
		puts("Can't Load Image");
		exit(0);
	}

	cvFlip(imgA,imgA,0);//上下反転のみでよい

	glGenTextures(1,&texId);
	glBindTexture(GL_TEXTURE_2D,texId);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	//アルファデータとしてテクスチャに格納
	glTexImage2D(GL_TEXTURE_2D,0,GL_ALPHA,
		imgA->width,imgA->height,0,
		GL_ALPHA,GL_UNSIGNED_BYTE,imgA->imageData);

	cvReleaseImage(&imgA);//メモリ解放
}

//-------- メイン関数---------//
int main(int argc, char *argv[])
{
	//glutの初期設定
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("TextureMaping and alpha test");
	
	checkExtension();//拡張機能の確認

	//コールバック関数登録
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	otherInit();//その他初期設定
	LoadTexture();//テクスチャの読み込み

	glutMainLoop();
	return 0;
}
