#include "gl/glut.h"

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//カラー・バッファを初期化
	
	glFlush();//命令の実行
}

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);

	glutInitWindowSize(640,480);
	glutInitDisplayMode(GLUT_RGBA); //ディスプレイ・モード
	glutCreateWindow("Color Buffer");
		
	glutDisplayFunc(display);//コールバック関数登録

	/* カラー・バッファの初期値*/
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glutMainLoop();

	return 0;
}
