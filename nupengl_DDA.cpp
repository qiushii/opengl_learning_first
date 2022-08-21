/*********************************************************************
DDA算法
	1、在x轴和y轴上移动描点
	2、起始点和终点获得 dx 和 dy(绝对值）， step = dx > dy ? dx : dy ;
	3、在x轴每次偏移量 stepX = dx / step
	4、在y轴每次偏移量 stepY = dy / step
**********************************************************************/


#include <GL/glut.h>
#include <iostream>

void DDA(GLfloat& x1, GLfloat& y1, GLfloat& x2, GLfloat& y2)
{
	GLfloat dx = fabs(x2 - x1);
	GLfloat dy = fabs(y2 - y1);
	GLfloat step = dx > dy ? dx : dy;
	GLfloat stepX = dx / step, stepY = dy / step;
	glBegin(GL_POINTS);
	for (GLint i = 0; i < (GLint)step; i++)
	{
		glVertex2f(x1, y1);
		x1 += stepX;
		y1 += stepY;
	}
	glEnd();
	glFlush();
}

void Line(GLfloat& x1, GLfloat& y1, GLfloat& x2, GLfloat& y2)
{
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glFlush();
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10);
	glColor3f(0.2f, 0.3f, 0.4f);
	GLfloat x1 = 0.0f, y1 = 0.0f, x2 = 80.0f, y2 = 80.0f;
	Line(x1, y1, x2, y2);
}

void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 400);
	glutCreateWindow("myDDA");

	init();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}