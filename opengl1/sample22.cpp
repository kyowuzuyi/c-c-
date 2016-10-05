#include <gl/glut.h>

//------- ���_�f�[�^-----------//
//�6��ʤ�4����_�1���_��x,y,z�̢3��v�f
GLfloat vertexAry[6][4][3] =
{
	//1�߂̖�(v0-v1-v2-v3)
	{ 
		{0.f,0.f,0.f},{1.f,0.f,0.f},
		{1.f,1.f,0.f},{0.f,1.f,0.f} 
	},
	//2�߂̖�(v1-v5-v6-v2)
	{ 
		{1.f,0.f,0.f},{1.f,0.f,-1.f},
		{1.f,1.f,-1.f},{1.f,1.f,0.f} 
	},
	//3�߂̖�(v4-v7-v6-v5)
	{ 
		{0.f,0.f,-1.f},{0.f,1.f,-1.f},
		{1.f,1.f,-1.f},{1.f,0.f,-1.f} 
	},
	//4�߂̖�(v4-v0-v3-v7)
	{ 
		{0.f,0.f,-1.f},{0.f,0.f,0.f},
		{0.f,1.f,0.f},{0.f,1.f,-1.f} 
	},
	//5�߂̖�(v3-v2-v6-v7)
	{ 
		{0.f,1.f,0.f},{1.f,1.f,0.f},
		{1.f,1.f,-1.f},{0.f,1.f,-1.f} 
	},
	//6�߂̖�(v0-v4-v5-v1)
	{ 
		{0.f,0.f,0.f},{0.f,0.f,-1.f},
		{1.f,0.f,-1.f},{1.f,0.f,0.f} 
	}
};

//�@���f�[�^
GLfloat normalAry[6][4][3] =
{
	//1�߂̖�(v0-v1-v2-v3)
	{ 
		{0.f,0.f,1.f},{0.f,0.f,1.f},
		{0.f,0.f,1.f},{0.f,0.f,1.f} 
	},
	//2�߂̖�(v1-v5-v6-v2)
	{ 
		{1.f,0.f,0.f},{1.f,0.f,0.f},
		{1.f,0.f,0.f},{1.f,0.f,0.f} 
	},
	//3�߂̖�(v4-v7-v6-v5)
	{ 
		{0.f,0.f,-1.f},{0.f,0.f,-1.f},
		{0.f,0.f,-1.f},{0.f,0.f,-1.f} 
	},
	//4�߂̖�(v4-v0-v3-v7)
	{ 
		{-1.f,0.f,0.f},{-1.f,0.f,0.f},
		{-1.f,0.f,0.f},{-1.f,0.f,0.f} 
	},
	//5�߂̖�(v3-v2-v6-v7)
	{ 
		{0.f,1.f,0.f},{0.f,1.f,0.f},
		{0.f,1.f,0.f},{0.f,1.f,0.f} 
	},
	//6�߂̖�(v0-v4-v5-v1)
	{ 
		{0.f,-1.f,0.f},{0.f,-1.f,0.f}, 
		{0.f,-1.f,0.f},{0.f,-1.f,0.f} 
	}
};

//�F�f�[�^
GLfloat colorAry[6][4][3] =
{
	//1�߂̖�(v0-v1-v2-v3)
	{ 
		{0.f,0.f,1.f},{0.f,0.f,1.f},
		{0.f,0.f,1.f},{0.f,0.f,1.f} 
	},
	//2�߂̖�(v1-v5-v6-v2)
	{ 
		{1.f,0.f,0.f},{1.f,0.f,0.f},
		{1.f,0.f,0.f},{1.f,0.f,0.f} 
	},
	//3�߂̖�(v4-v7-v6-v5)
	{ 
		{0.f,1.f,1.f},{0.f,1.f,1.f},
		{0.f,1.f,1.f},{0.f,1.f,1.f} 
	},
	//4�߂̖�(v4-v0-v3-v7)
	{ 
		{1.f,1.f,0.f},{1.f,1.f,0.f},
		{1.f,1.f,0.f},{1.f,1.f,0.f} 
	},
	//5�߂̖�(v3-v2-v6-v7)
	{ 
		{0.f,1.f,0.f},{0.f,1.f,0.f},
		{0.f,1.f,0.f},{0.f,1.f,0.f} 
	},
	//6�߂̖�(v0-v4-v5-v1)
	{ 
		{1.f,0.f,1.f},{1.f,0.f,1.f},
		{1.f,0.f,1.f},{1.f,0.f,1.f} 
	}
};

void drawAry(void)
{
	//�L����
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//�f�[�^�̊֘A�t��
	glVertexPointer(3, GL_FLOAT, 0, vertexAry);//���W 
	glNormalPointer(GL_FLOAT, 0, normalAry);//�@��
	glColorPointer(3,GL_FLOAT, 0, colorAry);//�F

	glDrawArrays(GL_QUADS,0,4*6); //�`��(4���_*6��)

	//������
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
//------- �e��R�[���o�b�N----------//
void display(void)
{
	static int angle = 0;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glPushMatrix();
	glRotatef(float(angle),1.f,0.f,0.f);
	glRotatef(float(angle+45),0.f,1.f,0.f);
	drawAry();
	glPopMatrix();

	glutSwapBuffers();
	if(++angle >= 360) angle = 0;
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, double(w)/h, 0.1, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle(void)
{
	glutPostRedisplay();
}
//------ ���̑������ݒ�-------//
void otherInit(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);//�@���̐��K��
}
//----------- ���C���֐�------------//
int main(int argc, char *argv[])
{
	//GLUT�̏����ݒ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("glDrawArray");

	//�R�[���o�b�N
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	otherInit();//���̑������ݒ�
	glutMainLoop();

	return 0;
}
