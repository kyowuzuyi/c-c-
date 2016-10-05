#include <stdio.h>
#include <gl/glut.h>

/*	外部変数	*/
int status = 0;//ボタンの状態

/* 各種コールバック関数*/
//ディスプレイ
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//マウス(クリック)
void mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("左ボタンを押しました@ (%d,%d)\n",x,y);
		status = 1;
	}else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		printf("左ボタンを離しました@ (%d,%d)\n",x,y);
		status = 0;
	}
}

//ドラッグ
void dragMotion(int x, int y)
{
	if(status == 1){
		printf("DragMotion @ (%d,%d)\n",x,y);
	}
}

//パッシブ
void passiveMotion(int x, int y)
{
	printf("PassiveMotion @ (%d,%d)\n",x,y);
}

/*	メイン関数	*/
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutCreateWindow("Mouse Callback");

	//各種コールバック関数の登録
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(dragMotion);
	glutPassiveMotionFunc(passiveMotion);

	glClearColor(1.0, 1.0, 1.0,1.0);

	glutMainLoop();

	return 0;
}
