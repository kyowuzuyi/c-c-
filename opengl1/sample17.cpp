#include <stdlib.h> //glut.h����ɋL�q����
#include <stdio.h>
#include <cv.h>//OpenCV�̃w�b�_
#include <highgui.h>//openCV�̃w�b�_
#include <gl/glut.h>

//�摜�t�@�C��
const char *texturefile = "sampleImage.png";//256x256�̉摜

//�e�N�X�`��ID
GLuint texId[2];
int filter = 0;//�t�B���^���[�h

//-------- �e��R�[���o�b�N�֐�-----//
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glBindTexture(GL_TEXTURE_2D,texId[filter]);//�o�C���h
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.f);	glVertex3f(-0.5f,-0.5f,0.f);
	glTexCoord2f(1.f, 0.f);	glVertex3f(0.5f,-0.5f,0.f);
	glTexCoord2f(1.f, 1.f);	glVertex3f(0.5f,0.5f,0.f);
	glTexCoord2f(0.f, 1.f);	glVertex3f(-0.5f,0.5f,0.f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
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

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'l':
		filter = 0;//GL_LINEAR
		break;

	case 'n':
		filter = 1;//GL_NEAREST
		break;

	case 'q':
	case 'Q':
	case '\033'://ESC�L�[
		glDeleteTextures(2,texId);//�e�N�X�`���̔j��
		exit(0);
		break;

	default:
		break;
	}

	glutPostRedisplay();//�ĕ`��
}

//-------- ���̑��̏����ݒ�------//
void otherInit(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_DEPTH_TEST);
}
//---- �e�N�X�`���ǂݍ��� ----//
void LoadTexture(void)
{
	//�摜�ǂݍ���
	IplImage *imgA = cvLoadImage(texturefile,1);
	if(imgA == NULL)
	{
		puts("Can't Load Image");
		exit(0);
	}

	//�㉺���]�ƐF�f�[�^�̓���ւ�
	cvFlip(imgA,imgA,0);
	cvCvtColor(imgA,imgA,CV_BGR2RGB);

	glGenTextures(2,texId);//�e�N�X�`���E�I�u�W�F�N�g�Q�Ԃ�

	//�P�ڂ̃e�N�X�`��
	glBindTexture(GL_TEXTURE_2D,texId[0]);//�o�C���h
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,
		imgA->width,imgA->height,
		0,GL_RGB,GL_UNSIGNED_BYTE,imgA->imageData);
	
	//�Q�ڂ̃e�N�X�`��
	glBindTexture(GL_TEXTURE_2D,texId[1]);//�o�C���h
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,
		imgA->width,imgA->height,
		0,GL_RGB,GL_UNSIGNED_BYTE,imgA->imageData);

	cvReleaseImage(&imgA);//���������
}

//-------- ���C���֐�----------//
int main(int argc, char *argv[])
{
	//GLUT�����ݒ�
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("Texture Mapping");
	
	//�R�[���o�b�N�֐��̓o�^
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	otherInit();//���̑��̏����ݒ�
	LoadTexture();//�e�N�X�`���̃��[�h
	glutMainLoop();

	return 0;
}
