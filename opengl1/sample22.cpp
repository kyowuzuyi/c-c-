#include <gl/glut.h>

//------- 頂点データ-----------//
//｢6｣面､｢4｣頂点､1頂点はx,y,zの｢3｣要素
GLfloat vertexAry[6][4][3] =
{
	//1つめの面(v0-v1-v2-v3)
	{ 
		{0.f,0.f,0.f},{1.f,0.f,0.f},
		{1.f,1.f,0.f},{0.f,1.f,0.f} 
	},
	//2つめの面(v1-v5-v6-v2)
	{ 
		{1.f,0.f,0.f},{1.f,0.f,-1.f},
		{1.f,1.f,-1.f},{1.f,1.f,0.f} 
	},
	//3つめの面(v4-v7-v6-v5)
	{ 
		{0.f,0.f,-1.f},{0.f,1.f,-1.f},
		{1.f,1.f,-1.f},{1.f,0.f,-1.f} 
	},
	//4つめの面(v4-v0-v3-v7)
	{ 
		{0.f,0.f,-1.f},{0.f,0.f,0.f},
		{0.f,1.f,0.f},{0.f,1.f,-1.f} 
	},
	//5つめの面(v3-v2-v6-v7)
	{ 
		{0.f,1.f,0.f},{1.f,1.f,0.f},
		{1.f,1.f,-1.f},{0.f,1.f,-1.f} 
	},
	//6つめの面(v0-v4-v5-v1)
	{ 
		{0.f,0.f,0.f},{0.f,0.f,-1.f},
		{1.f,0.f,-1.f},{1.f,0.f,0.f} 
	}
};

//法線データ
GLfloat normalAry[6][4][3] =
{
	//1つめの面(v0-v1-v2-v3)
	{ 
		{0.f,0.f,1.f},{0.f,0.f,1.f},
		{0.f,0.f,1.f},{0.f,0.f,1.f} 
	},
	//2つめの面(v1-v5-v6-v2)
	{ 
		{1.f,0.f,0.f},{1.f,0.f,0.f},
		{1.f,0.f,0.f},{1.f,0.f,0.f} 
	},
	//3つめの面(v4-v7-v6-v5)
	{ 
		{0.f,0.f,-1.f},{0.f,0.f,-1.f},
		{0.f,0.f,-1.f},{0.f,0.f,-1.f} 
	},
	//4つめの面(v4-v0-v3-v7)
	{ 
		{-1.f,0.f,0.f},{-1.f,0.f,0.f},
		{-1.f,0.f,0.f},{-1.f,0.f,0.f} 
	},
	//5つめの面(v3-v2-v6-v7)
	{ 
		{0.f,1.f,0.f},{0.f,1.f,0.f},
		{0.f,1.f,0.f},{0.f,1.f,0.f} 
	},
	//6つめの面(v0-v4-v5-v1)
	{ 
		{0.f,-1.f,0.f},{0.f,-1.f,0.f}, 
		{0.f,-1.f,0.f},{0.f,-1.f,0.f} 
	}
};

//色データ
GLfloat colorAry[6][4][3] =
{
	//1つめの面(v0-v1-v2-v3)
	{ 
		{0.f,0.f,1.f},{0.f,0.f,1.f},
		{0.f,0.f,1.f},{0.f,0.f,1.f} 
	},
	//2つめの面(v1-v5-v6-v2)
	{ 
		{1.f,0.f,0.f},{1.f,0.f,0.f},
		{1.f,0.f,0.f},{1.f,0.f,0.f} 
	},
	//3つめの面(v4-v7-v6-v5)
	{ 
		{0.f,1.f,1.f},{0.f,1.f,1.f},
		{0.f,1.f,1.f},{0.f,1.f,1.f} 
	},
	//4つめの面(v4-v0-v3-v7)
	{ 
		{1.f,1.f,0.f},{1.f,1.f,0.f},
		{1.f,1.f,0.f},{1.f,1.f,0.f} 
	},
	//5つめの面(v3-v2-v6-v7)
	{ 
		{0.f,1.f,0.f},{0.f,1.f,0.f},
		{0.f,1.f,0.f},{0.f,1.f,0.f} 
	},
	//6つめの面(v0-v4-v5-v1)
	{ 
		{1.f,0.f,1.f},{1.f,0.f,1.f},
		{1.f,0.f,1.f},{1.f,0.f,1.f} 
	}
};

void drawAry(void)
{
	//有効化
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//データの関連付け
	glVertexPointer(3, GL_FLOAT, 0, vertexAry);//座標 
	glNormalPointer(GL_FLOAT, 0, normalAry);//法線
	glColorPointer(3,GL_FLOAT, 0, colorAry);//色

	glDrawArrays(GL_QUADS,0,4*6); //描画(4頂点*6面)

	//無効化
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
//------- 各種コールバック----------//
void display(void)
{
	static int angle = 0;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glPushMatrix();
	glRotatef(float(angle),1.f,0.f,0.f);
	glRotatef(float(angle+45),0.f,1.f,0.f);
	drawAry();
	glPopMatrix();

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

void idle(void)
{
	glutPostRedisplay();
}
//------ その他初期設定-------//
void otherInit(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);//法線の正規化
}
//----------- メイン関数------------//
int main(int argc, char *argv[])
{
	//GLUTの初期設定
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("glDrawArray");

	//コールバック
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	otherInit();//その他初期設定
	glutMainLoop();

	return 0;
}
