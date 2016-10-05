#include <stdio.h>
#include <stdlib.h> //glut.h����ɃC���N���[�h
#include <gl/glut.h>

/* �e��R�[���o�b�N�֐�*/
//�f�B�X�v���C
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//�L�[�{�[�h����(�������Ƃ�)
void keyboard(unsigned char key, int x, int y)
{
	if(key == 27)//[ESC]�L�[�̂Ƃ�
	{
		puts("Exit...");
		exit(0);
	}

	printf("%c ��������܂���@ (%d, %d)\n",key,x,y);
}

//�L�[�{�[�h����(�������Ƃ�)
void keyboardUp(unsigned char key, int x, int y)
{
	printf("%c ��������܂���@ (%d, %d)\n",key,x,y);
}

//����L�[���������Ƃ�
void specialKey(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		printf("[��]��������܂���@ (%d, %d)\n",x,y);
		break;

	case GLUT_KEY_UP:
		printf("[��]��������܂���@ (%d, %d)\n",x,y);
		break;

	case GLUT_KEY_RIGHT:
		printf("[��]��������܂���@ (%d, %d)\n",x,y);
		break;

	case GLUT_KEY_DOWN:
		printf("[��]��������܂���@ (%d, %d)\n",x,y);
		break;
	}
}

//����L�[�𗣂����Ƃ�
void specialUpKey(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		printf("[��]������܂���@ (%d, %d)\n",x,y);
		break;

	case GLUT_KEY_UP:
		printf("[��]������܂���@ (%d, %d)\n",x,y);
		break;

	case GLUT_KEY_RIGHT:
		printf("[��]������܂���@ (%d, %d)\n",x,y);
		break;

	case GLUT_KEY_DOWN:
		printf("[��]������܂���@ (%d, %d)\n",x,y);
		break;
	}
}

/*	���C���֐�	*/
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutCreateWindow("Key Callback");

	//�e��R�[���o�b�N�֐��̓o�^
	glutDisplayFunc(display);

	//�ʏ�L�[
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	//����L�[
	glutSpecialFunc(specialKey);
	glutSpecialUpFunc(specialUpKey);
	glutIgnoreKeyRepeat(GL_TRUE);//�L�[�E���s�[�g����

	glClearColor(1.0, 1.0, 1.0,1.0);

	glutMainLoop();

	return 0;
}
