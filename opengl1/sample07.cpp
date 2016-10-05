#include <stdio.h>
#include <gl/glut.h>

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	puts("display callback");
	glFlush();
}

void reshape(int width, int height)
{
	printf("(w, h) = (%d,%d)\n",width,height);
}

//---------- メイン関数------------//
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);

	glutInitWindowSize(400,400);
	glutInitDisplayMode(GLUT_RGBA); 
	glutCreateWindow("CallBack Test");
		
	/* コールバック関数の登録*/
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glClearColor(1.f, 1.f, 1.f, 1.f);

	glutMainLoop();

	return 0;
}
