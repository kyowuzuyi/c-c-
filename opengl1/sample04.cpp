#include "gl/glut.h"

void display(void)
{
	/* ��̊֐� */
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv); //GLUT�̏�����

	/* �E�B���h�E�̍쐬 */
	glutInitWindowSize(640,480);
	glutCreateWindow("Hello OpenGL");

	glutDisplayFunc(display);//�R�[���o�b�N�֐��o�^(2-2�ߎQ��)

	glutMainLoop();

	return 0;
}