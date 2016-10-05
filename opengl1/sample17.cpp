#include <stdlib.h> //glut.hより先に記述する
#include <stdio.h>
#include <cv.h>//OpenCVのヘッダ
#include <highgui.h>//openCVのヘッダ
#include <gl/glut.h>

//画像ファイル
const char *texturefile = "sampleImage.png";//256x256の画像

//テクスチャID
GLuint texId[2];
int filter = 0;//フィルタモード

//-------- 各種コールバック関数-----//
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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
	case 'l':
		filter = 0;//GL_LINEAR
		break;

	case 'n':
		filter = 1;//GL_NEAREST
		break;

	case 'q':
	case 'Q':
	case '\033'://ESCキー
		glDeleteTextures(2,texId);//テクスチャの破棄
		exit(0);
		break;

	default:
		break;
	}

	glutPostRedisplay();//再描画
}

//-------- その他の初期設定------//
void otherInit(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_DEPTH_TEST);
}
//---- テクスチャ読み込み ----//
void LoadTexture(void)
{
	//画像読み込み
	IplImage *imgA = cvLoadImage(texturefile,1);
	if(imgA == NULL)
	{
		puts("Can't Load Image");
		exit(0);
	}

	//上下反転と色データの入れ替え
	cvFlip(imgA,imgA,0);
	cvCvtColor(imgA,imgA,CV_BGR2RGB);

	glGenTextures(2,texId);//テクスチャ・オブジェクト２つぶん

	//１つ目のテクスチャ
	glBindTexture(GL_TEXTURE_2D,texId[0]);//バインド
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,
		imgA->width,imgA->height,
		0,GL_RGB,GL_UNSIGNED_BYTE,imgA->imageData);
	
	//２つ目のテクスチャ
	glBindTexture(GL_TEXTURE_2D,texId[1]);//バインド
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,
		imgA->width,imgA->height,
		0,GL_RGB,GL_UNSIGNED_BYTE,imgA->imageData);

	cvReleaseImage(&imgA);//メモリ解放
}

//-------- メイン関数----------//
int main(int argc, char *argv[])
{
	//GLUT初期設定
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("Texture Mapping");
	
	//コールバック関数の登録
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	otherInit();//その他の初期設定
	LoadTexture();//テクスチャのロード
	glutMainLoop();

	return 0;
}
