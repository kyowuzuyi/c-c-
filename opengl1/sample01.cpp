#include <stdio.h>
#include "gl/glut.h"

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutCreateWindow("Check OpenGL");

	//èoóÕÇ∑ÇÈ
	printf("Vendor:%s\n",glGetString(GL_VENDOR));
	printf("GPU:%s\n",glGetString(GL_RENDERER));
	printf("OpenGL ver. %s\n",glGetString(GL_VERSION));

	return 0;
}
