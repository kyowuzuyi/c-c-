#include <gl/glut.h>

//--- 外部変数---//
GLclampf fColor[4]={0.f, 0.7f, 1.f, 1.f};//フォグの色
GLfloat zTrans = 0.f;//平行移動量

//------- 各種コールバック関数-----//
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glEnable(GL_FOG);//有効化
	glColor3f(1.f, 1.f, 1.f);
	glPushMatrix();
	glTranslatef(0.f,0.f,zTrans);
	glutWireTeapot(0.5);//描画
	glPopMatrix();
	glDisable(GL_FOG);//無効化
	
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0,double(w)/h,0.1,200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void specialkey(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_UP:
		zTrans -= 0.2f;
		break;
	case GLUT_KEY_DOWN:
		zTrans += 0.2f;
		break;
	case GLUT_KEY_F1:
		zTrans = 0.f;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

//その他初期設定
void otherInit(void)
{
	//背景をフォグの色に設定
	glClearColor(fColor[0],fColor[1],fColor[2],fColor[3]);	
	glEnable(GL_DEPTH);
	//フォグの設定
	glFogfv(GL_FOG_COLOR,fColor);//色設定
	glFogf(GL_FOG_START,5.f);//方程式の設定
	glFogf(GL_FOG_END,20.f);
	glFogi(GL_FOG_MODE,GL_LINEAR);
	glHint(GL_FOG_HINT,GL_FASTEST);//ヒントを設定
}
//------- メイン関数----------//
int main(int argc, char *argv[])
{
	//glutの初期設定
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("Basic Fog");

	//コールバック関数の登録
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(specialkey);

	otherInit();//その他初期設定
	glutMainLoop();

	return 0;
}
