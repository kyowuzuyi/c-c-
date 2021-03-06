#include <gl/glut.h>

//頂点データ(8頂点､xyz３要素)
GLfloat vertexes[8][3]=
{
	{-0.5f, 0.5f, 0.5f},//v0
	{-0.5f, -0.5f, 0.5f},//v1
	{0.5f, -0.5f, 0.5f},//v2
	{0.5f, 0.5f, 0.5f},//v3

	{-0.5f, 0.5f, -0.5f},//v4
	{-0.5f, -0.5f, -0.5f},//v5
	{0.5f, -0.5f, -0.5f},//v6
	{0.5f, 0.5f, -0.5f}//v7
};

//------------ 各種材質パラメータ--------------//
//光源(環境光､拡散光､鏡面光､位置)
GLfloat lightAmb[] = {0.f, 0.f, 0.f, 1.f };
GLfloat lightDiff[] = {1.f, 1.f, 1.f, 1.f};
GLfloat lightSpec[] = {1.f, 1.f, 1.f, 1.f};
GLfloat lightPos[] = {1.f, 1.f, 1.f, 0.f};//平行光源

//材質(環境光､拡散光､鏡面光､鏡面指数)
GLfloat goldAmb[] = { 0.24725f, 0.1995f, 0.0745f, 1.f };
GLfloat goldDiff[] = { 0.75164f, 0.60648f , 0.22648f, 1.f };
GLfloat goldSpec[] = { 0.628281f, 0.555802f,0.366065f,1.f };
GLfloat goldShin =  51.2f ;


//立方体の描画
void drawCube(void)
{
	//top
	glNormal3f(0,1,0);
	glBegin(GL_QUADS);
	glVertex3fv(vertexes[0]);
	glVertex3fv(vertexes[3]);
	glVertex3fv(vertexes[7]);
	glVertex3fv(vertexes[4]);
	glEnd();

	//buttom
	glNormal3f(0,-1,0);
	glBegin(GL_QUADS);
	glVertex3fv(vertexes[5]);
	glVertex3fv(vertexes[6]);
	glVertex3fv(vertexes[2]);
	glVertex3fv(vertexes[1]);
	glEnd();

	//front
	glNormal3f(0,0,1);
	glBegin(GL_QUADS);
	glVertex3fv(vertexes[0]);
	glVertex3fv(vertexes[1]);
	glVertex3fv(vertexes[2]);
	glVertex3fv(vertexes[3]);
	glEnd();

	//back
	glNormal3f(0,0,-1);
	glBegin(GL_QUADS);
	glVertex3fv(vertexes[4]);
	glVertex3fv(vertexes[7]);
	glVertex3fv(vertexes[6]);
	glVertex3fv(vertexes[5]);
	glEnd();

	//left
	glNormal3f(-1,0,0);
	glBegin(GL_QUADS);
	glVertex3fv(vertexes[0]);
	glVertex3fv(vertexes[4]);
	glVertex3fv(vertexes[5]);
	glVertex3fv(vertexes[1]);
	glEnd();

	//right
	glNormal3f(1,0,0);
	glBegin(GL_QUADS);
	glVertex3fv(vertexes[3]);
	glVertex3fv(vertexes[2]);
	glVertex3fv(vertexes[6]);
	glVertex3fv(vertexes[7]);
	glEnd();
}

//--------- 各種コールバック関数-------//
void display(void)
{
	static int angle = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	gluLookAt(0.0, 3.0, 4,0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	//光源の位置設定
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

	//材質設定と描画
	glPushMatrix();
	glRotatef(float(angle), 0.f, 1.f, 0.f);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,goldAmb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,goldDiff);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,goldSpec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,goldShin);
	drawCube();//立方体の描画
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
	glEnable(GL_NORMALIZE);//法線ベクトルの正規化
}

//---------- メイン関数-------------//
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("Normal");

	//コールバック関数登録
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	otherInit();//その他設定

	glutMainLoop();

	return 0;
}
