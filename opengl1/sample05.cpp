#include "gl/glut.h"

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//�J���[�E�o�b�t�@��������
	
	glFlush();//���߂̎��s
}

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);

	glutInitWindowSize(640,480);
	glutInitDisplayMode(GLUT_RGBA); //�f�B�X�v���C�E���[�h
	glutCreateWindow("Color Buffer");
		
	glutDisplayFunc(display);//�R�[���o�b�N�֐��o�^

	/* �J���[�E�o�b�t�@�̏����l*/
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glutMainLoop();

	return 0;
}
