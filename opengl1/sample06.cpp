#include "gl/glut.h"

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//カラー・バッファをクリア

	glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);//赤色
		glVertex2f(0.f, 0.5f);

		glColor3f(0.f, 1.f, 0.f);//緑色
		glVertex2f(-0.5f, -0.5f);	

		glColor3f(0.f, 0.f, 1.f);//青色
		glVertex2f(0.5f, -0.5f);
	glEnd();

	glFlush();//命令の実行
}

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);

	glutInitWindowSize(400,400);
	glutInitDisplayMode(GLUT_RGBA); //ディスプレイモード
	glutCreateWindow("Draw Triangle");
		
	glutDisplayFunc(display);//コールバック関数登録

	/* カラー・バッファの初期値*/
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glutMainLoop();

	return 0;
}
