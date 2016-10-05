#include "gl/glut.h"

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//�J���[�E�o�b�t�@���N���A

	glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);//�ԐF
		glVertex2f(0.f, 0.5f);

		glColor3f(0.f, 1.f, 0.f);//�ΐF
		glVertex2f(-0.5f, -0.5f);	

		glColor3f(0.f, 0.f, 1.f);//�F
		glVertex2f(0.5f, -0.5f);
	glEnd();

	glFlush();//���߂̎��s
}

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);

	glutInitWindowSize(400,400);
	glutInitDisplayMode(GLUT_RGBA); //�f�B�X�v���C���[�h
	glutCreateWindow("Draw Triangle");
		
	glutDisplayFunc(display);//�R�[���o�b�N�֐��o�^

	/* �J���[�E�o�b�t�@�̏����l*/
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glutMainLoop();

	return 0;
}
