#include <stdlib.h>//glut.hより先にインクルードする
#include <gl/glut.h>

//外部変数(キューブ､トーラス､オクタ)
GLuint cubeId,torusId,octaId;
GLuint listId = 0;//制御用Id

//------- 各種コールバック-------//
void display(void)
{
	static int angle = 0;
	static GLfloat Light0Pos[]={1,1,1,0}; //光源の位置
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 2.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, Light0Pos);//位置設定

	glColor3f(0.f, 1.f, 0.f);
	glPushMatrix();
	glRotatef(float(angle),0.f, 1.f, 0.f);
	glCallList(listId);//ディスプレイ・リストの呼び出し
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
		//不要になったら削除
		glDeleteLists(listId, 3); //先頭Idから３つ分
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

//その他設定
void otherInit(void)
{
	glClearColor(1.f ,1.f, 1.f, 1.f);
	glEnable(GL_DEPTH_TEST);
	//カラーマテリアル
	glColorMaterial(GL_FRONT_AND_BACK,
					GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
    //光源の設定   
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//ディスプレイリスト作成
	//Idを設定
	listId = glGenLists(3); //3つ作成(先頭番号が返る)
	cubeId = listId;
	torusId = listId + 1;
	octaId = listId + 2 ;
	//1つめ
	glNewList(cubeId,GL_COMPILE);
	glutSolidCube(1.0);
	glEndList();
	//2つめ
	glNewList(torusId,GL_COMPILE);
	glutSolidTorus(0.2,0.4,30,30);
	glEndList();
	//3つめ
	glNewList(octaId,GL_COMPILE);
	glutSolidOctahedron();
	glEndList();
}

//--------- メイン関数-----------//
int main(int argc, char *argv[])
{
	//glutの初期設定
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("display list");

	//コールバック関数の登録
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	otherInit();//その他初期設定

	glutMainLoop();

	return 0;
}
