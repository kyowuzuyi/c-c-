#include <gl/glut.h>

//---- 頂点データ----//
//4面､3角形､3要素
GLfloat vertexAry[]=
{
	//v0-v1-v3
	0.f, 0.f, 0.f,//0番目
	0.f, 0.f, 1.f,//1番目
	0.f, 1.f, 0.f,//...
	//v0-v2-v1
	0.f, 0.f, 0.f,
	1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 
	//v0-v3-v2
	0.f, 0.f, 0.f,
	0.f, 1.f, 0.f,
	1.f, 0.f, 0.f,
	//v3-v1-v2
	0.f, 1.f, 0.f,//...
	0.f, 0.f, 1.f,//10番目
	1.f, 0.f, 0.f //11番目
};
//法線
GLfloat normalAry[]=
{
	//v0-v1-v3
	-1.f, 0.f, 0.f,//0番目
	-1.f, 0.f, 0.f,//1番目
	-1.f, 0.f, 0.f,//...
	//v0-v2-v1
	0.f, -1.f, 0.f,
	0.f, -1.f, 0.f,
	0.f, -1.f, 0.f,
	//v0-v3-v2
	0.f, 0.f, -1.f,
	0.f, 0.f, -1.f,
	0.f, 0.f, -1.f,
	//v3-v1-v2
	1.f, 1.f, 1.f,//...
	1.f, 1.f, 1.f,//10番目
	1.f, 1.f, 1.f //11番目
};
//色
GLfloat colorAry[]=
{
	//v0-v1-v3
	1.f, 0.f, 0.f,//0番目
	1.f, 0.f, 0.f,//1番目
	1.f, 0.f, 0.f,//...
	//v0-v2-v1
	0.f, 1.f, 0.f,
	0.f, 1.f, 0.f,
	0.f, 1.f, 0.f,
	//v0-v3-v2
	0.f, 0.f, 1.f,
	0.f, 0.f, 1.f,
	0.f, 0.f, 1.f,
	//v3-v1-v2
	1.f, 0.f, 1.f,//...
	1.f, 0.f, 1.f,//10番目
	1.f, 0.f, 1.f //11番目
};

//インデックス
GLubyte idxAry[]=
{
	0,1,2,
	3,4,5,
	6,7,8,
	9,10,11
};
//----- 描画--------//
void draw(void)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(3,GL_FLOAT,0,vertexAry);
	glNormalPointer(GL_FLOAT,0,normalAry);
	glColorPointer(3,GL_FLOAT,0,colorAry);
	glDrawElements(GL_TRIANGLES,12,
				GL_UNSIGNED_BYTE,idxAry);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

//----- 各種コールバック-----///
void display(void)
{
	static int angle = 0;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 4.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glPushMatrix();
	glRotatef(float(angle),0.f,1.f,0.f);
	glRotatef(float(angle+45),1.f,0.f,0.f);
	draw();	//描画
	glPopMatrix();
	
	glutSwapBuffers();
	if(++angle >= 360) angle = 0;
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, double(w)/h,0.1, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle(void)
{
	glutPostRedisplay();
}
//その他初期設定
void otherInit(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_DEPTH_TEST);
	//光源設定
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);//法線の正規化
	//カラーマテリアル設定
	glColorMaterial(GL_FRONT_AND_BACK,
					GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}
//---------- メイン関数----------//
int main(int argc, char *argv[])
{
	//glutの初期設定
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("glDrawElements");

	//コールバック関数の登録
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	otherInit();//その他初期設定

	glutMainLoop();
	return 0;
}
