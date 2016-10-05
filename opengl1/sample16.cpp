#include <gl/glut.h>

//------------ 各種材質パラメータ--------------//
//光源(環境光､拡散光､鏡面光､位置)
GLfloat lightAmb[] = {0.f, 0.f, 0.f, 1.f };
GLfloat lightDiff[] = {1.f, 1.f, 1.f, 1.f};
GLfloat lightSpec[] = {1.f, 1.f, 1.f, 1.f};
GLfloat lightPos[] = {1.f, 1.f, 1.f, 0.f};//平行光源

//材質(環境光､拡散光､鏡面光､鏡面指数)
GLfloat pearlAmb[] = {0.25f,0.20725f,0.20725f,1.f };
GLfloat pearlDiff[] = {1.f,0.829f,0.829f,1.f};
GLfloat pearlSpec[] = {0.296648f,0.296648f,0.296648f,1.f};
GLfloat pearlShin =  10.24f;

//gluオブジェクト
GLUquadricObj *quadric = NULL;

//--------- GLUquadricオブジェクトの描画----------------//
void DrawQuadricObj(void)
{
	//シリンダ
	gluQuadricOrientation(quadric,GLU_OUTSIDE);
	gluCylinder(quadric, 0.5, 0.3, 1.0, 20, 15);

	//上面
	glPushMatrix();
		glTranslatef(0.f,0.f,1.f);//高さ分平行移動
		gluDisk(quadric, 0, 0.3, 20,10);
	glPopMatrix();

	//底面(法線の向きを逆にする)
	gluQuadricOrientation(quadric,GLU_INSIDE);
	gluDisk(quadric, 0, 0.5, 20,10);
}


//--------- 各種コールバック関数-------//
void display(void)
{
	static int angle = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	gluLookAt(0.0, 1.5, 4,0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	//光源の位置設定
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

	//材質設定
	glPushMatrix();
	glRotatef(float(angle), 0.f, 1.f, 0.f);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,pearlAmb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,pearlDiff);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,pearlSpec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,pearlShin);
	DrawQuadricObj();//描画
	glPopMatrix();

	glutSwapBuffers();
	if(++angle >= 360){ angle = 0;}
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0,double(w)/h, 0.1, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

void idle(void)
{
	glutPostRedisplay();
}

//--------- その他各種設定-----------//
void otherInit(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClearDepth(1.f);
	glEnable(GL_DEPTH_TEST);

	//光源設定(環境､拡散､鏡面のみ)
	glLightfv(GL_LIGHT0,GL_AMBIENT,lightAmb);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightDiff);
	glLightfv(GL_LIGHT0,GL_SPECULAR,lightSpec);

	//光源とライティング有効化
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	//GLUquadricオブジェクトの設定
	quadric =  gluNewQuadric(); //オブジェクト生成
	gluQuadricDrawStyle(quadric, GLU_FILL); //ポリゴン描画
	gluQuadricNormals(quadric, GLU_SMOOTH); //シェーディング
}

//---------- メイン関数-------------//
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("GLUquadric Object");

	//コールバック関数登録
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	otherInit();//その他設定

	glutMainLoop();
	
	//不要になったら破棄
	gluDeleteQuadric(quadric);//本来は終了処理部分で記述する
	return 0;
}
