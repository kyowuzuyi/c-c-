#include <gl/glut.h>

//------------ �e��ގ��p�����[�^--------------//
//����(������g�U������ʌ���ʒu)
GLfloat lightAmb[] = {0.f, 0.f, 0.f, 1.f };
GLfloat lightDiff[] = {1.f, 1.f, 1.f, 1.f};
GLfloat lightSpec[] = {1.f, 1.f, 1.f, 1.f};
GLfloat lightPos[] = {1.f, 1.f, 1.f, 0.f};//���s����

//�ގ�(������g�U������ʌ�����ʎw��)
GLfloat goldAmb[] = { 0.24725f, 0.1995f, 0.0745f, 1.f };
GLfloat goldDiff[] = { 0.75164f, 0.60648f , 0.22648f, 1.f };
GLfloat goldSpec[] = { 0.628281f, 0.555802f,0.366065f,1.f };
GLfloat goldShin =  51.2f ;


//--------- �e��R�[���o�b�N�֐�-------//
void display(void)
{
	static int angle = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	gluLookAt(0.0, 1.0, 5.0, 0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	//�����̈ʒu�ݒ�
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

	//�ގ��ݒ�ƕ`��
	glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();
	glRotatef(float(angle), 0.f, 1.f, 0.f);
	//���ʎw��
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,goldShin);

    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT);//����
    glColor4fv(goldAmb);
	
	glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);//�g�U��
    glColor4fv(goldDiff);

	glColorMaterial(GL_FRONT_AND_BACK,GL_SPECULAR);//���ʌ�
    glColor4fv(goldSpec);

	glutSolidSphere(1,60,60);//�`��

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glutSwapBuffers();
	if(++angle >= 360){ angle = 0;}
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0,double(w)/h, 0.1, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

void idle(void)
{
	glutPostRedisplay();
}

//--------- ���̑��e��ݒ�-----------//
void otherInit(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClearDepth(1.f);
	glEnable(GL_DEPTH_TEST);

	//�����ݒ�(����g�U����ʂ̂�)
	glLightfv(GL_LIGHT0,GL_AMBIENT,lightAmb);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightDiff);
	glLightfv(GL_LIGHT0,GL_SPECULAR,lightSpec);

	//�����ƃ��C�e�B���O�L����
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);//�@���x�N�g���̐��K��
}

//---------- ���C���֐�-------------//
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("glColormaterial");

	//�R�[���o�b�N�֐��o�^
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	otherInit();//���̑��ݒ�

	glutMainLoop();

	return 0;
}
