#include <stdio.h>
#include "gl/glut.h"

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutCreateWindow("Check OpenGL");

	printf("%s\n",glGetString(GL_EXTENSIONS));

	return 0;
}
