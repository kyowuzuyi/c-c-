#include <stdio.h>
#include <gl/glew.h> //先に記述する
#include <gl/glut.h>

//---------- main関数-----------//
int main(int argc, char **argv)
{
	//glutの初期化とウィンドウの作成
	glutInit(&argc,argv);
	glutCreateWindow("Extention Check");

	//glewの初期化
	GLenum err;
	err = glewInit();
	if (err != GLEW_OK){
		fprintf(stderr, "Error: %s\n", 
			glewGetErrorString(err));
		return -1;
	}

	//GLEWのバージョンチェック
	fprintf(stdout, "GLEW Version: %s\n", 
		glewGetString(GLEW_VERSION));

	//OpenGLのバージョン確認
	if(GLEW_VERSION_2_0){
		puts("OpenGL 2.0 is Supported");
	}else{
		puts("OpenGL 2.0 is not  Supported");
	}

	//glewIsSupported関数を使った場合
	if(glewIsSupported("GL_ARB_point_sprite")){
		puts("point_sprite is Supported");
	}else{
		puts("point_sprite is not Supported");
	}

	return 0;
}
