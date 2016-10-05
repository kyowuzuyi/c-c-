#include <stdlib.h>//glut.h����ɃC���N���[�h����
#include <gl/glut.h>

//�O���ϐ�(�L���[�u��g�[���X��I�N�^)
GLuint cubeId,torusId,octaId;
GLuint listId = 0;//����pId

//------- �e��R�[���o�b�N-------//
void display(void)
{
	static int angle = 0;
	static GLfloat Light0Pos[]={1,1,1,0}; //�����̈ʒu
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 2.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, Light0Pos);//�ʒu�ݒ�

	glColor3f(0.f, 1.f, 0.f);
	glPushMatrix();
	glRotatef(float(angle),0.f, 1.f, 0.f);
	glCallList(listId);//�f�B�X�v���C�E���X�g�̌Ăяo��
	glPopMatrix();
	glColor3f(1.f, 1.f, 1.f);

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

void keyboard(unsigned char key, int w, int h)
{
	switch(key)
	{
	case '1':
		listId = cubeId;
		break;
	case '2':
		listId = torusId;
		break;
	case '3':
		listId = octaId;
		break;
	case 'q':
	case '\033':
		//�s�v�ɂȂ�����폜
		glDeleteLists(listId, 3); //�擪Id����R��
		exit(0);
		break;
	default:
		break;
	}
}

void idle(void)
{
	glutPostRedisplay();
}

//���̑��ݒ�
void otherInit(void)
{
	glClearColor(1.f ,1.f, 1.f, 1.f);
	glEnable(GL_DEPTH_TEST);
	//�J���[�}�e���A��
	glColorMaterial(GL_FRONT_AND_BACK,
					GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
    //�����̐ݒ�   
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//�f�B�X�v���C���X�g�쐬
	//Id��ݒ�
	listId = glGenLists(3); //3�쐬(�擪�ԍ����Ԃ�)
	cubeId = listId;
	torusId = listId + 1;
	octaId = listId + 2 ;
	//1��
	glNewList(cubeId,GL_COMPILE);
	glutSolidCube(1.0);
	glEndList();
	//2��
	glNewList(torusId,GL_COMPILE);
	glutSolidTorus(0.2,0.4,30,30);
	glEndList();
	//3��
	glNewList(octaId,GL_COMPILE);
	glutSolidOctahedron();
	glEndList();
}

//--------- ���C���֐�-----------//
int main(int argc, char *argv[])
{
	//glut�̏����ݒ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("display list");

	//�R�[���o�b�N�֐��̓o�^
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	otherInit();//���̑������ݒ�

	glutMainLoop();

	return 0;
}
