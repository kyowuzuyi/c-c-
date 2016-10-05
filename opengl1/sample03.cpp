#include <stdio.h>
#include <gl/glew.h> //��ɋL�q����
#include <gl/glut.h>

//---------- main�֐�-----------//
int main(int argc, char **argv)
{
	//glut�̏������ƃE�B���h�E�̍쐬
	glutInit(&argc,argv);
	glutCreateWindow("Extention Check");

	//glew�̏�����
	GLenum err;
	err = glewInit();
	if (err != GLEW_OK){
		fprintf(stderr, "Error: %s\n", 
			glewGetErrorString(err));
		return -1;
	}

	//GLEW�̃o�[�W�����`�F�b�N
	fprintf(stdout, "GLEW Version: %s\n", 
		glewGetString(GLEW_VERSION));

	//OpenGL�̃o�[�W�����m�F
	if(GLEW_VERSION_2_0){
		puts("OpenGL 2.0 is Supported");
	}else{
		puts("OpenGL 2.0 is not  Supported");
	}

	//glewIsSupported�֐����g�����ꍇ
	if(glewIsSupported("GL_ARB_point_sprite")){
		puts("point_sprite is Supported");
	}else{
		puts("point_sprite is not Supported");
	}

	return 0;
}
