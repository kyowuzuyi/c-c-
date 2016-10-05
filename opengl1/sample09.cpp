#include <stdio.h>
#include <stdlib.h> //glut.hより先にインクルード
#include <gl/glut.h>

/* 各種コールバック関数*/
//ディスプレイ
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//キーボード処理(押したとき)
void keyboard(unsigned char key, int x, int y)
{
	if(key == 27)//[ESC]キーのとき
	{
		puts("Exit...");
		exit(0);
	}

	printf("%c が押されました@ (%d, %d)\n",key,x,y);
}

//キーボード処理(離したとき)
void keyboardUp(unsigned char key, int x, int y)
{
	printf("%c が離されました@ (%d, %d)\n",key,x,y);
}

//特殊キーを押したとき
void specialKey(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		printf("[←]が押されました@ (%d, %d)\n",x,y);
		break;

	case GLUT_KEY_UP:
		printf("[↑]が押されました@ (%d, %d)\n",x,y);
		break;

	case GLUT_KEY_RIGHT:
		printf("[→]が押されました@ (%d, %d)\n",x,y);
		break;

	case GLUT_KEY_DOWN:
		printf("[↓]が押されました@ (%d, %d)\n",x,y);
		break;
	}
}

//特殊キーを離したとき
void specialUpKey(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		printf("[←]が離れました@ (%d, %d)\n",x,y);
		break;

	case GLUT_KEY_UP:
		printf("[↑]が離れました@ (%d, %d)\n",x,y);
		break;

	case GLUT_KEY_RIGHT:
		printf("[→]が離れました@ (%d, %d)\n",x,y);
		break;

	case GLUT_KEY_DOWN:
		printf("[↓]が離れました@ (%d, %d)\n",x,y);
		break;
	}
}

/*	メイン関数	*/
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutCreateWindow("Key Callback");

	//各種コールバック関数の登録
	glutDisplayFunc(display);

	//通常キー
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	//特殊キー
	glutSpecialFunc(specialKey);
	glutSpecialUpFunc(specialUpKey);
	glutIgnoreKeyRepeat(GL_TRUE);//キー・リピート無視

	glClearColor(1.0, 1.0, 1.0,1.0);

	glutMainLoop();

	return 0;
}
