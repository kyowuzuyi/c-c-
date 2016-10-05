#include <math.h>
#include <stdio.h>
#include <stdlib.h>//glut.h����ɃC���N���[�h
#include "gl/glew.h"//glut.h����ɃC���N���[�h
#include "gl/glut.h"

//------- ���_�f�[�^-----------//
//�6��ʤ�4����_�1���_��x,y,z�̢3��v�f
GLfloat vertexAry[6][4][3] =
{
	�c�@�y���10-1�z�Ɠ����ł��@�c
};

//�@���f�[�^
GLfloat normalAry[6][4][3] =
{
	�c�@�y���10-1�z�Ɠ����ł��@�c
};

//�F�f�[�^
GLfloat colorAry[6][4][3] =
{
	�c�@�y���10-1�z�Ɠ����ł��@�c
};
//�C���f�b�N�X
GLubyte indexAry[]=
{
	0,1,2,3,
	4,5,6,7,
	8,9,10,11,
	12,13,14,15,
	16,17,18,19,
	20,21,22,23
};

// ��/180�̒l
const float PI_OVER_180 = 0.0174532925f;

//VBO�pID
GLuint VboId[3];//�R��
GLuint VboIndex;//�C���f�b�N�X

//�`��֐�
void drawAry(void)
{
	GLfloat *clientPtr;//�N���C�A���g���p
	GLfloat tmp[3];
	int idloop;
	int loop;
	static float angle = 2*PI_OVER_180;

	//�f�[�^�̏ꏊ��m�点��
	//���W
	glBindBuffer(GL_ARRAY_BUFFER,VboId[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	//�@��
	glBindBuffer(GL_ARRAY_BUFFER,VboId[1]);
	glNormalPointer(GL_FLOAT, 0, 0);
	//�F
	glBindBuffer(GL_ARRAY_BUFFER,VboId[2]);
	glColorPointer(3,GL_FLOAT, 0, 0);
	//�C���f�b�N�X���o�C���h
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboIndex);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//�`��
	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,0);
	
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	//���W�Ɩ@������]������
	for(idloop = 0; idloop < 2;++idloop)
	{
		//idloop�Ԗڂ̃o�b�t�@�I�u�W�F�N�g�ɒ���
		glBindBuffer(GL_ARRAY_BUFFER,VboId[idloop]);
		
		//�Ή��t��
		clientPtr = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER,
												GL_READ_WRITE);
		if(clientPtr != NULL)
		{
			//24���_*3���W
			 for(loop = 0; loop < 24*3;loop += 3)	{
				//�ǂݏo��(READ)
				tmp[0] = clientPtr[loop];
				tmp[1] = clientPtr[loop+1];
				tmp[2] = clientPtr[loop+2];
				//��������(WRITE)
				clientPtr[loop] = cos(angle)*tmp[0]
									+ sin(angle)*tmp[2];
				clientPtr[loop+1] = tmp[1];
				clientPtr[loop+2] = -sin(angle)*tmp[0]
										+ cos(angle)*tmp[2];
			 }
			glUnmapBuffer(GL_ARRAY_BUFFER);//�Ή��t���̉��
		}
	}
	//�N���C�A���g���ɖ߂�
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
//------- �e��R�[���o�b�N----------//
void display(void)
{
	static int angle = 0;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glPushMatrix();
	glRotatef(float(angle),1.f,0.f,0.f);//x����]
	drawAry();
	glPopMatrix();

	glutSwapBuffers();
	if(++angle >= 360) angle = 0;
}

void reshape(int w, int h)
{
	�c�@�y���10-1�z�Ɠ����ł��@�c
}

void idle(void)
{
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'q':
	case 'Q':
	case '\033':
		//�I������
		glDeleteBuffers(3,&VboId[0]);
		glDeleteBuffers(1,&VboIndex);
		exit(0);
		break;
	}
}
//------ ���̑������ݒ�-------//
void otherInit(void)
{
	�c�@�y���10-1�z�Ɠ����ł��@�c
}

//---- VBO�̍쐬----//
void buildVBO(void)
{
	glGenBuffers(3,&VboId[0]);//���W��@����F�̂R��
	
	//���_
	glBindBuffer(GL_ARRAY_BUFFER,VboId[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexAry),
				vertexAry,GL_DYNAMIC_DRAW);//�f�[�^�ύX����

	//�@��
	glBindBuffer(GL_ARRAY_BUFFER,VboId[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(normalAry),
				normalAry,GL_DYNAMIC_DRAW);//�f�[�^�ύX����

	//�F
	glBindBuffer(GL_ARRAY_BUFFER,VboId[2]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(colorAry),
					colorAry,GL_STREAM_DRAW);//�f�[�^�ύX�Ȃ�

	//�C���f�b�N�X
	glGenBuffers(1,&VboIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,VboIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indexAry),
					indexAry,GL_STATIC_DRAW);//�f�[�^�ύX�Ȃ�
}
//----------- ���C���֐�------------//
int main(int argc, char *argv[])
{
	//GLUT�̏����ݒ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("VBO Sample");
	//GLEW�̏����ݒ�
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		fprintf(stderr,"Err:%s\n",
			glewGetErrorString(err));
		return -1;
	}
	//�g���`�F�b�N
	if(!glewIsExtensionSupported(
					"GL_ARB_vertex_buffer_object")){
		puts("you Can't use VBO");
		return -1;
	}

	//�R�[���o�b�N
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	otherInit();
	
	buildVBO();//VBO�̍쐬
	glutMainLoop();

	return 0;
}
