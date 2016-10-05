#include <gl/glut.h>

//�O�p�`�̕`��
void drawTriangle(void)
{
	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, 0.5f, 0.f);
	glVertex3f(-0.5f, -0.5f, 0.f);
	glVertex3f(0.5f, -0.5f, 0.f);
	glEnd();
}

//-------- XYZ���̕`�� -------------//
void drawXYZ(void)
{
	glBegin(GL_LINES);
		glColor3f(1.f, 0.f, 0.f);//X��:��
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(200.f, 0.f, 0.f);

		glColor3f(0.f, 1.f, 0.f);//Y��:��
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 200.f, 0.f);

		glColor3f(0.f, 0.f, 1.f);//Z��:��
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 200.f);
	glEnd();

	glColor3f(1.f, 1.f, 1.f);//�F�̃��Z�b�g
}


//-------- �e��R�[���o�b�N�֐�------------//
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glPushMatrix();
		glTranslatef(1.f, 0.f, 0.f);
		glRotatef(45.f, 0.f, 1.f, 0.f);
		glColor3f(1.f, 1.f, 0.f);//���F
		drawTriangle();
	glPopMatrix();

	glPushMatrix();
		glRotatef(45.f, 0.f, 1.f, 0.f);
		glTranslatef(1.f, 0.f, 0.f);
		glColor3f(0.7f, 0.7f, 0.7f);//�D�F
		drawTriangle();
	glPopMatrix();

	drawXYZ();//XYZ���̕`��
	glFinish();
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0,double(w)/h, 0.1, 200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0, 2.5, 4,0, 0.0, 0.0, 0.0, 1.0, 0.0);	
}

//-------- ���̑��e��ݒ�-----------------//
void otherInit(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClearDepth(1.f);
	glEnable(GL_DEPTH_TEST);
}

//--------- ���C���֐�------------//
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutCreateWindow("Depth and Affine");
	
	//�R�[���o�b�N�֐��o�^
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	otherInit();//���̑��ݒ�

	glutMainLoop();

	return 0;
}
