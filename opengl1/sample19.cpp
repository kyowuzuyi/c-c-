#include "gl/glut.h"

//----------- 各種コールバック-------------//
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(1.0, 2.0, 3.0, 0.0 ,0.0 ,0.0, 0.0,1.0, 0.0);

	glDisable(GL_DEPTH_TEST);//デプステストの無効化
	glEnable(GL_BLEND);//ブレンドの有効化
	
	//正確には奥にあるものを先に描画
	glPushMatrix();
	glTranslatef(0.f,0.f,-1.f);
	glColor4f(0.f, 0.f, 1.f, 0.5f);//青
	glRectf(-0.5,0.5,0.5,-0.5);
	glPopMatrix();
	
	glColor4f(1.f, 0.f, 0.f, 0.7f);//赤
	glRectf(-0.5,0.5,0.5,-0.5);

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	glutSwapBuffers();
	glColor3f(1.f, 1.f, 1.f);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, double(w)/h, 0.1, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//その他初期設定
void otherInit(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_DEPTH_TEST);
	//ブレンディング係数の設定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//----------- メイン関数-----------//
int main(int argc, char *argv[])
{
	//glutの初期化
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("blending sample");

	//コールバック関数の登録
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	otherInit();//その他初期設定

	glutMainLoop();
	return 0;
}
