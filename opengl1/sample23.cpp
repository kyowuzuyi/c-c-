#include <gl/glut.h>

//---- ���_�f�[�^----//
//4�ʤ3�p�`�3�v�f
GLfloat vertexAry[]=
{
	//v0-v1-v3
	0.f, 0.f, 0.f,//0�Ԗ�
	0.f, 0.f, 1.f,//1�Ԗ�
	0.f, 1.f, 0.f,//...
	//v0-v2-v1
	0.f, 0.f, 0.f,
	1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 
	//v0-v3-v2
	0.f, 0.f, 0.f,
	0.f, 1.f, 0.f,
	1.f, 0.f, 0.f,
	//v3-v1-v2
	0.f, 1.f, 0.f,//...
	0.f, 0.f, 1.f,//10�Ԗ�
	1.f, 0.f, 0.f //11�Ԗ�
};
//�@��
GLfloat normalAry[]=
{
	//v0-v1-v3
	-1.f, 0.f, 0.f,//0�Ԗ�
	-1.f, 0.f, 0.f,//1�Ԗ�
	-1.f, 0.f, 0.f,//...
	//v0-v2-v1
	0.f, -1.f, 0.f,
	0.f, -1.f, 0.f,
	0.f, -1.f, 0.f,
	//v0-v3-v2
	0.f, 0.f, -1.f,
	0.f, 0.f, -1.f,
	0.f, 0.f, -1.f,
	//v3-v1-v2
	1.f, 1.f, 1.f,//...
	1.f, 1.f, 1.f,//10�Ԗ�
	1.f, 1.f, 1.f //11�Ԗ�
};
//�F
GLfloat colorAry[]=
{
	//v0-v1-v3
	1.f, 0.f, 0.f,//0�Ԗ�
	1.f, 0.f, 0.f,//1�Ԗ�
	1.f, 0.f, 0.f,//...
	//v0-v2-v1
	0.f, 1.f, 0.f,
	0.f, 1.f, 0.f,
	0.f, 1.f, 0.f,
	//v0-v3-v2
	0.f, 0.f, 1.f,
	0.f, 0.f, 1.f,
	0.f, 0.f, 1.f,
	//v3-v1-v2
	1.f, 0.f, 1.f,//...
	1.f, 0.f, 1.f,//10�Ԗ�
	1.f, 0.f, 1.f //11�Ԗ�
};

//�C���f�b�N�X
GLubyte idxAry[]=
{
	0,1,2,
	3,4,5,
	6,7,8,
	9,10,11
};
//----- �`��--------//
void draw(void)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(3,GL_FLOAT,0,vertexAry);
	glNormalPointer(GL_FLOAT,0,normalAry);
	glColorPointer(3,GL_FLOAT,0,colorAry);
	glDrawElements(GL_TRIANGLES,12,
				GL_UNSIGNED_BYTE,idxAry);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

//----- �e��R�[���o�b�N-----///
void display(void)
{
	static int angle = 0;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 4.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glPushMatrix();
	glRotatef(float(angle),0.f,1.f,0.f);
	glRotatef(float(angle+45),1.f,0.f,0.f);
	draw();	//�`��
	glPopMatrix();
	
	glutSwapBuffers();
	if(++angle >= 360) angle = 0;
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, double(w)/h,0.1, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle(void)
{
	glutPostRedisplay();
}
//���̑������ݒ�
void otherInit(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_DEPTH_TEST);
	//�����ݒ�
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);//�@���̐��K��
	//�J���[�}�e���A���ݒ�
	glColorMaterial(GL_FRONT_AND_BACK,
					GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}
//---------- ���C���֐�----------//
int main(int argc, char *argv[])
{
	//glut�̏����ݒ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("glDrawElements");

	//�R�[���o�b�N�֐��̓o�^
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	otherInit();//���̑������ݒ�

	glutMainLoop();
	return 0;
}
