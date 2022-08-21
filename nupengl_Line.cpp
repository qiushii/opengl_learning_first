#include <GL/glut.h>

void myLines()
{
	int p1[] = { 6, 4 }, p2[] = { 1,1 }, p3[] = { 3, 7 };
	int p4[] = { 5, 1 }, p5[] = { 0, 4 };
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.3, 0.1, 0.8);
	glPointSize(3);
	//画线
	/************************
	#define GL_LINES                          0x0001
	#define GL_LINE_LOOP                      0x0002
	#define GL_LINE_STRIP                     0x0003

	GL_LINES：两个点之间相连接
	GL_LINE_STRIP：所有点相连
	GL_LINE_LOOP ：所有点连成环
	*************************/
	glBegin(GL_LINE_STRIP);

	glVertex3iv(p1);
	glVertex2iv(p2);
	glVertex2iv(p3);
	glVertex2iv(p4);
	glVertex2iv(p5);
	glEnd();
	//缓存
	glFlush();
}

void init()
{
	glClearColor(128.0, 128.0, 128.0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 500);
	glutCreateWindow("Lines");

	init();
	glutDisplayFunc(myLines);
	glutMainLoop();
	return 0;
}