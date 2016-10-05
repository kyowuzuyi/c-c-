#include <gl/glut.h>

//三角形の描画
void drawTriangle(void)
{
	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, 0.5f, 0.f);
	glVertex3f(-0.5f, -0.5f, 0.f);
	glVertex3f(0.5f, -0.5f, 0.f);
	glEnd();
}

//-------- XYZ軸の描画 -------------//
void drawXYZ(void)
{
	glBegin(GL_LINES);
		glColor3f(1.f, 0.f, 0.f);//X軸:赤
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(200.f, 0.f, 0.f);

		glColor3f(0.f, 1.f, 0.f);//Y軸:緑
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 200.f, 0.f);

		glColor3f(0.f, 0.f, 1.f);//Z軸:青
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 200.f);
	glEnd();

	glColor3f(1.f, 1.f, 1.f);//色のリセット
}


//-------- 各種コールバック関数------------//
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glPushMatrix();
		glTranslatef(1.f, 0.f, 0.f);
		glRotatef(45.f, 0.f, 1.f, 0.f);
		glColor3f(1.f, 1.f, 0.f);//黄色
		drawTriangle();
	glPopMatrix();

	glPushMatrix();
		glRotatef(45.f, 0.f, 1.f, 0.f);
		glTranslatef(1.f, 0.f, 0.f);
		glColor3f(0.7f, 0.7f, 0.7f);//灰色
		drawTriangle();
	glPopMatrix();

	drawXYZ();//XYZ軸の描画
	glFinish();
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0,double(w)/h, 0.1, 200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0, 2.5, 4,0, 0.0, 0.0, 0.0, 1.0, 0.0);	
}

//-------- その他各種設定-----------------//
void otherInit(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClearDepth(1.f);
	glEnable(GL_DEPTH_TEST);
}

//--------- メイン関数------------//
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutCreateWindow("Depth and Affine");
	
	//コールバック関数登録
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	otherInit();//その他設定

	glutMainLoop();

	return 0;
}
