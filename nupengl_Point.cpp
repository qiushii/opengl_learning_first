#include <GL/glut.h>

void myPoints()
{
	//清屏
	glClear(GL_COLOR_BUFFER_BIT);
	//每个点占3个像素
	glPointSize(3);
	//设置为绘制点
	glBegin(GL_POINTS);
	//设置颜色
	glColor3f(1.0, 0.0, 0.0);
	//顶点
	/***************************
	#define GL_POINTS                         0x000
	***************************/
	glVertex2i(-3, 3);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(10, 20);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(0, -15);
	//结束
	glEnd();
	//缓存
	glFlush();
}

void init()
{
	//给frame buff定义为黑色
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//显示范围
	gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	//显示模式
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); 
	//窗口位置
	glutInitWindowPosition(200, 300);
	//窗口大小
	glutInitWindowSize(300, 300);
	//窗口名字
	glutCreateWindow("Display Points");

	//初始化
	init();
	//显示回调
	glutDisplayFunc(myPoints);
	glutMainLoop();

	return 0;

}