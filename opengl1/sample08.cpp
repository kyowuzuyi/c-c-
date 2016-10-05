#include <stdio.h>
#include <gl/glut.h>

/*	�O���ϐ�	*/
int status = 0;//�{�^���̏��

/* �e��R�[���o�b�N�֐�*/
//�f�B�X�v���C
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//�}�E�X(�N���b�N)
void mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("���{�^���������܂���@ (%d,%d)\n",x,y);
		status = 1;
	}else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		printf("���{�^���𗣂��܂���@ (%d,%d)\n",x,y);
		status = 0;
	}
}

//�h���b�O
void dragMotion(int x, int y)
{
	if(status == 1){
		printf("DragMotion @ (%d,%d)\n",x,y);
	}
}

//�p�b�V�u
void passiveMotion(int x, int y)
{
	printf("PassiveMotion @ (%d,%d)\n",x,y);
}

/*	���C���֐�	*/
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutCreateWindow("Mouse Callback");

	//�e��R�[���o�b�N�֐��̓o�^
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(dragMotion);
	glutPassiveMotionFunc(passiveMotion);

	glClearColor(1.0, 1.0, 1.0,1.0);

	glutMainLoop();

	return 0;
}
