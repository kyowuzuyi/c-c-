#include <gl/glut.h>

//--- �O���ϐ�---//
GLclampf fColor[4]={0.f, 0.7f, 1.f, 1.f};//�t�H�O�̐F
GLfloat zTrans = 0.f;//���s�ړ���

//------- �e��R�[���o�b�N�֐�-----//
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glEnable(GL_FOG);//�L����
	glColor3f(1.f, 1.f, 1.f);
	glPushMatrix();
	glTranslatef(0.f,0.f,zTrans);
	glutWireTeapot(0.5);//�`��
	glPopMatrix();
	glDisable(GL_FOG);//������
	
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0,double(w)/h,0.1,200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void specialkey(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_UP:
		zTrans -= 0.2f;
		break;
	case GLUT_KEY_DOWN:
		zTrans += 0.2f;
		break;
	case GLUT_KEY_F1:
		zTrans = 0.f;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

//���̑������ݒ�
void otherInit(void)
{
	//�w�i���t�H�O�̐F�ɐݒ�
	glClearColor(fColor[0],fColor[1],fColor[2],fColor[3]);	
	glEnable(GL_DEPTH);
	//�t�H�O�̐ݒ�
	glFogfv(GL_FOG_COLOR,fColor);//�F�ݒ�
	glFogf(GL_FOG_START,5.f);//�������̐ݒ�
	glFogf(GL_FOG_END,20.f);
	glFogi(GL_FOG_MODE,GL_LINEAR);
	glHint(GL_FOG_HINT,GL_FASTEST);//�q���g��ݒ�
}
//------- ���C���֐�----------//
int main(int argc, char *argv[])
{
	//glut�̏����ݒ�
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("Basic Fog");

	//�R�[���o�b�N�֐��̓o�^
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(specialkey);

	otherInit();//���̑������ݒ�
	glutMainLoop();

	return 0;
}
