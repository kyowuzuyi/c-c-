#include <stdio.h>
#include <stdlib.h>//glut.h����ɃC���N���[�h
#include <gl/glut.h>
#include <cv.h>//OpenCV�̃w�b�_
#include <highgui.h>//OpenCV�̃w�b�_

//�O���ϐ�
int alphaFlag = 0;
GLclampf alphaRef = 0.5f;
const char *imagefile = "star2.png";//�摜�t�@�C����
GLuint texId;//�e�N�X�`��Id

//--------  �e��R�[���o�b�N�֐�------//
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glBindTexture(GL_TEXTURE_2D,texId);//�o�C���h
	glColor3f(0.f, 1.f, 0.f);//�ΐF
	
	//�t���O�ɂ��ꍇ����
	if(alphaFlag){
		glEnable(GL_ALPHA_TEST);
	}else{
		glDisable(GL_ALPHA_TEST);
	}

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.f);	glVertex3f(-0.5f,-0.5f,0.f);
	glTexCoord2f(1.f, 0.f);	glVertex3f(0.5f,-0.5f,0.f);
	glTexCoord2f(1.f, 1.f);	glVertex3f(0.5f,0.5f,0.f);
	glTexCoord2f(0.f, 1.f);	glVertex3f(-0.5f,0.5f,0.f);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	
	glColor3f(1.f, 1.f, 1.f);

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
	case 'a':
		alphaFlag = ++alphaFlag % 2;//0��1���Ƃ�
		if(alphaFlag){
			puts("[ALPHA TEST]: ON");
		}else{
			puts("[ALPHA TEST]: OFF");
		}
		break;
	case 'r':
		alphaRef +=0.05f;
		if(alphaRef > 1.f) {alphaRef = 0.f;}
		glAlphaFunc(GL_LESS,alphaRef);//���e�X�g�̎�
		printf("alphaRef = %f\n",alphaRef);
		break;

	case 'q':
	case 'Q':
	case '\033'://Esc�L�[
		glDeleteTextures(1,&texId);//�e�N�X�`���̔j��
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

//���̑������ݒ�
void otherInit(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_DEPTH);
	glAlphaFunc(GL_LESS,alphaRef);//���e�X�g�̎�
}

//--------  �g���@�\�̊m�F-----//
void checkExtension(void)
{
	//�g���@�\�̊m�F
	if(	glutExtensionSupported(
		"GL_ARB_texture_non_power_of_two"))
	{
		puts("ARB_texture_non_power_of_two : OK");
	}else{
		puts("ARB_texture_non_power_of_two : BAD");
	}	
}

//-------- �e�N�X�`���̓ǂݍ���----//
void LoadTexture(void)
{
	//�O���C�X�P�[���摜�œǂݍ���
	IplImage *imgA = cvLoadImage(imagefile,0);
	if(imgA == NULL)
	{
		puts("Can't Load Image");
		exit(0);
	}

	cvFlip(imgA,imgA,0);//�㉺���]�݂̂ł悢

	glGenTextures(1,&texId);
	glBindTexture(GL_TEXTURE_2D,texId);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	//�A���t�@�f�[�^�Ƃ��ăe�N�X�`���Ɋi�[
	glTexImage2D(GL_TEXTURE_2D,0,GL_ALPHA,
		imgA->width,imgA->height,0,
		GL_ALPHA,GL_UNSIGNED_BYTE,imgA->imageData);

	cvReleaseImage(&imgA);//���������
}

//-------- ���C���֐�---------//
int main(int argc, char *argv[])
{
	//glut�̏����ݒ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("TextureMaping and alpha test");
	
	checkExtension();//�g���@�\�̊m�F

	//�R�[���o�b�N�֐��o�^
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	otherInit();//���̑������ݒ�
	LoadTexture();//�e�N�X�`���̓ǂݍ���

	glutMainLoop();
	return 0;
}
