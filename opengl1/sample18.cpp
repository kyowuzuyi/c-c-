#include <stdio.h>
#include <stdlib.h>//glut.h����ɃC���N���[�h
#include <gl/glew.h>//glut.h����ɃC���N���[�h
#include <gl/glut.h>
#include <cv.h>//OpenCV�̃w�b�_
#include <highgui.h>//OpenCV�̃w�b�_

//�摜�t�@�C����
const char *imagefile = "block3.png";

//�e�N�X�`��Id
int filter = 0;
GLuint texId[4];


//--- �e��R�[���o�b�N�֐�---//
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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
	case 'f':
		filter = ++filter % 4;//0�`�̊Ԃ��Ƃ�
		printf("now filter is %d\n",filter);
		break;

	case 'q':
	case 'Q':
	case '\033'://Esc�L�[
		glDeleteTextures(4,texId);//�e�N�X�`���̔j��
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
}

//�e�N�X�`���̓ǂݍ���
void LoadTexture(void)
{
	int loop;

	IplImage *imgA = cvLoadImage(imagefile,1);
	if(imgA==NULL)
	{
		puts("Can't Load Image");
		exit(0);
	}

	cvConvertImage(imgA,imgA,
		CV_CVTIMG_FLIP|CV_CVTIMG_SWAP_RB);

	//�~�b�v�}�b�v�̏k���t�B���^
	GLenum minFilter[4]={
		GL_NEAREST_MIPMAP_NEAREST,
		GL_LINEAR_MIPMAP_NEAREST,
		GL_NEAREST_MIPMAP_LINEAR,
		GL_LINEAR_MIPMAP_LINEAR};


	glGenTextures(4,texId);
	for(loop = 0;loop < 4;++loop)
	{
		glBindTexture(GL_TEXTURE_2D,texId[loop]);
		//�g��E�k���t�B���^
		glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER,minFilter[loop]);
		//�~�b�v�}�b�v�쐬
		gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,
			imgA->width,imgA->height,
			GL_RGB,GL_UNSIGNED_BYTE,imgA->imageData);
	}

	cvReleaseImage(&imgA);
}

//---- GLEW�̃Z�b�g�A�b�v�Ɗg���@�\�̊m�F----//
void setUpGLEW(void)
{
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		fprintf(stderr,"Error: %s\n",
			glewGetErrorString(err) );
		exit(0);
	}
	//�g���@�\�̊m�F
	if(glewIsSupported("GL_ARB_texture_non_power_of_two"))
	{
		puts("[GL_ARB_texture_non_power_of_two] : OK");
	}else
	{
		puts("[GL_ARB_texture_non_power_of_two] : BAD");
	}
}


//---- ���C���֐� ----//
int main(int argc, char *argv[])
{
	//glut�̏����ݒ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("TextureMaping with Mipmap");
	
	setUpGLEW();//GLEW�̃Z�b�g�A�b�v

	//�R�[���o�b�N�֐��o�^
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	otherInit();//���̑������ݒ�
	LoadTexture();//�e�N�X�`���̓ǂݍ���

	glutMainLoop();
	return 0;
}
