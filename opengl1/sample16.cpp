#include <gl/glut.h>

//------------ �e��ގ��p�����[�^--------------//
//����(������g�U������ʌ���ʒu)
GLfloat lightAmb[] = {0.f, 0.f, 0.f, 1.f };
GLfloat lightDiff[] = {1.f, 1.f, 1.f, 1.f};
GLfloat lightSpec[] = {1.f, 1.f, 1.f, 1.f};
GLfloat lightPos[] = {1.f, 1.f, 1.f, 0.f};//���s����

//�ގ�(������g�U������ʌ�����ʎw��)
GLfloat pearlAmb[] = {0.25f,0.20725f,0.20725f,1.f };
GLfloat pearlDiff[] = {1.f,0.829f,0.829f,1.f};
GLfloat pearlSpec[] = {0.296648f,0.296648f,0.296648f,1.f};
GLfloat pearlShin =  10.24f;

//glu�I�u�W�F�N�g
GLUquadricObj *quadric = NULL;

//--------- GLUquadric�I�u�W�F�N�g�̕`��----------------//
void DrawQuadricObj(void)
{
	//�V�����_
	gluQuadricOrientation(quadric,GLU_OUTSIDE);
	gluCylinder(quadric, 0.5, 0.3, 1.0, 20, 15);

	//���
	glPushMatrix();
		glTranslatef(0.f,0.f,1.f);//���������s�ړ�
		gluDisk(quadric, 0, 0.3, 20,10);
	glPopMatrix();

	//���(�@���̌������t�ɂ���)
	gluQuadricOrientation(quadric,GLU_INSIDE);
	gluDisk(quadric, 0, 0.5, 20,10);
}


//--------- �e��R�[���o�b�N�֐�-------//
void display(void)
{
	static int angle = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	gluLookAt(0.0, 1.5, 4,0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	//�����̈ʒu�ݒ�
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

	//�ގ��ݒ�
	glPushMatrix();
	glRotatef(float(angle), 0.f, 1.f, 0.f);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,pearlAmb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,pearlDiff);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,pearlSpec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,pearlShin);
	DrawQuadricObj();//�`��
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
	glEnable(GL_NORMALIZE);

	//GLUquadric�I�u�W�F�N�g�̐ݒ�
	quadric =  gluNewQuadric(); //�I�u�W�F�N�g����
	gluQuadricDrawStyle(quadric, GLU_FILL); //�|���S���`��
	gluQuadricNormals(quadric, GLU_SMOOTH); //�V�F�[�f�B���O
}

//---------- ���C���֐�-------------//
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("GLUquadric Object");

	//�R�[���o�b�N�֐��o�^
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	otherInit();//���̑��ݒ�

	glutMainLoop();
	
	//�s�v�ɂȂ�����j��
	gluDeleteQuadric(quadric);//�{���͏I�����������ŋL�q����
	return 0;
}
