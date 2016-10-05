#include "gl/glut.h"

void display(void)
{
	/* 空の関数 */
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv); //GLUTの初期化

	/* ウィンドウの作成 */
	glutInitWindowSize(640,480);
	glutCreateWindow("Hello OpenGL");

	glutDisplayFunc(display);//コールバック関数登録(2-2節参照)

	glutMainLoop();

	return 0;
}