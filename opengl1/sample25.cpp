#include <math.h>
#include <stdio.h>
#include <stdlib.h>//glut.hより先にインクルード
#include "gl/glew.h"//glut.hより先にインクルード
#include "gl/glut.h"

//------- 頂点データ-----------//
//｢6｣面､｢4｣頂点､1頂点はx,y,zの｢3｣要素
GLfloat vertexAry[6][4][3] =
{
	…　【問題10-1】と同じです　…
};

//法線データ
GLfloat normalAry[6][4][3] =
{
	…　【問題10-1】と同じです　…
};

//色データ
GLfloat colorAry[6][4][3] =
{
	…　【問題10-1】と同じです　…
};
//インデックス
GLubyte indexAry[]=
{
	0,1,2,3,
	4,5,6,7,
	8,9,10,11,
	12,13,14,15,
	16,17,18,19,
	20,21,22,23
};

// π/180の値
const float PI_OVER_180 = 0.0174532925f;

//VBO用ID
GLuint VboId[3];//３つ分
GLuint VboIndex;//インデックス

//描画関数
void drawAry(void)
{
	GLfloat *clientPtr;//クライアント側用
	GLfloat tmp[3];
	int idloop;
	int loop;
	static float angle = 2*PI_OVER_180;

	//データの場所を知らせる
	//座標
	glBindBuffer(GL_ARRAY_BUFFER,VboId[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	//法線
	glBindBuffer(GL_ARRAY_BUFFER,VboId[1]);
	glNormalPointer(GL_FLOAT, 0, 0);
	//色
	glBindBuffer(GL_ARRAY_BUFFER,VboId[2]);
	glColorPointer(3,GL_FLOAT, 0, 0);
	//インデックスもバインド
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboIndex);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//描画
	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,0);
	
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	//座標と法線を回転させる
	for(idloop = 0; idloop < 2;++idloop)
	{
		//idloop番目のバッファオブジェクトに注目
		glBindBuffer(GL_ARRAY_BUFFER,VboId[idloop]);
		
		//対応付け
		clientPtr = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER,
												GL_READ_WRITE);
		if(clientPtr != NULL)
		{
			//24頂点*3座標
			 for(loop = 0; loop < 24*3;loop += 3)	{
				//読み出し(READ)
				tmp[0] = clientPtr[loop];
				tmp[1] = clientPtr[loop+1];
				tmp[2] = clientPtr[loop+2];
				//書き込み(WRITE)
				clientPtr[loop] = cos(angle)*tmp[0]
									+ sin(angle)*tmp[2];
				clientPtr[loop+1] = tmp[1];
				clientPtr[loop+2] = -sin(angle)*tmp[0]
										+ cos(angle)*tmp[2];
			 }
			glUnmapBuffer(GL_ARRAY_BUFFER);//対応付けの解放
		}
	}
	//クライアント側に戻す
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
//------- 各種コールバック----------//
void display(void)
{
	static int angle = 0;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glPushMatrix();
	glRotatef(float(angle),1.f,0.f,0.f);//x軸回転
	drawAry();
	glPopMatrix();

	glutSwapBuffers();
	if(++angle >= 360) angle = 0;
}

void reshape(int w, int h)
{
	…　【問題10-1】と同じです　…
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
		//終了処理
		glDeleteBuffers(3,&VboId[0]);
		glDeleteBuffers(1,&VboIndex);
		exit(0);
		break;
	}
}
//------ その他初期設定-------//
void otherInit(void)
{
	…　【問題10-1】と同じです　…
}

//---- VBOの作成----//
void buildVBO(void)
{
	glGenBuffers(3,&VboId[0]);//座標､法線､色の３つ
	
	//頂点
	glBindBuffer(GL_ARRAY_BUFFER,VboId[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexAry),
				vertexAry,GL_DYNAMIC_DRAW);//データ変更する

	//法線
	glBindBuffer(GL_ARRAY_BUFFER,VboId[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(normalAry),
				normalAry,GL_DYNAMIC_DRAW);//データ変更あり

	//色
	glBindBuffer(GL_ARRAY_BUFFER,VboId[2]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(colorAry),
					colorAry,GL_STREAM_DRAW);//データ変更なし

	//インデックス
	glGenBuffers(1,&VboIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,VboIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indexAry),
					indexAry,GL_STATIC_DRAW);//データ変更なし
}
//----------- メイン関数------------//
int main(int argc, char *argv[])
{
	//GLUTの初期設定
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("VBO Sample");
	//GLEWの初期設定
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		fprintf(stderr,"Err:%s\n",
			glewGetErrorString(err));
		return -1;
	}
	//拡張チェック
	if(!glewIsExtensionSupported(
					"GL_ARB_vertex_buffer_object")){
		puts("you Can't use VBO");
		return -1;
	}

	//コールバック
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	otherInit();
	
	buildVBO();//VBOの作成
	glutMainLoop();

	return 0;
}
