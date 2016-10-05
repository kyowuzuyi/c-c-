#include "gl/glut.h"

//----------- �e��R�[���o�b�N-------------//
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(1.0, 2.0, 3.0, 0.0 ,0.0 ,0.0, 0.0,1.0, 0.0);

	glDisable(GL_DEPTH_TEST);//�f�v�X�e�X�g�̖�����
	glEnable(GL_BLEND);//�u�����h�̗L����
	
	//���m�ɂ͉��ɂ�����̂��ɕ`��
	glPushMatrix();
	glTranslatef(0.f,0.f,-1.f);
	glColor4f(0.f, 0.f, 1.f, 0.5f);//��
	glRectf(-0.5,0.5,0.5,-0.5);
	glPopMatrix();
	
	glColor4f(1.f, 0.f, 0.f, 0.7f);//��
	glRectf(-0.5,0.5,0.5,-0.5);

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	glutSwapBuffers();
	glColor3f(1.f, 1.f, 1.f);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, double(w)/h, 0.1, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//���̑������ݒ�
void otherInit(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_DEPTH_TEST);
	//�u�����f�B���O�W���̐ݒ�
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//----------- ���C���֐�-----------//
int main(int argc, char *argv[])
{
	//glut�̏�����
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("blending sample");

	//�R�[���o�b�N�֐��̓o�^
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	otherInit();//���̑������ݒ�

	glutMainLoop();
	return 0;
}
