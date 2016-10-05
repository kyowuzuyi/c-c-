#include <gl/glut.h>


//--------- コールバック関数--------------//
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//カラー・バッファをクリア
	glColor3f(1.f, 0.f, 0.f);

	glutWireTeapot(1.0);//ティーポットを描画

	glFlush();//命令の実行
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);  //ビューポートの設定

	glMatrixMode(GL_PROJECTION);//射影行列の設定
	glLoadIdentity();
	gluPerspective(30.0, (double)w / h, 1.0, 100.0); 

	glMatrixMode(GL_MODELVIEW);//モデルビュー行列の設定
	glLoadIdentity();
	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


//---------- メイン関数-------------//
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);

	glutInitWindowSize(640,480);
	glutInitDisplayMode(GLUT_RGBA); //ディスプレイ・モード
	glutCreateWindow("Hello 3D Graphics");
		
	glutDisplayFunc(display);//コールバック関数登録
	glutReshapeFunc(reshape);

	/* カラー・バッファの初期値*/
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glutMainLoop();

	return 0;
}
