#include <GL/glut.h>

GLint w = 400, d = 400;

GLint dx = 0, dy = 0;

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.91, 0.91, 0.19);
	glPointSize(20);
	glBegin(GL_POLYGON);
	glVertex2i(0 + dx, 0 + dy);
	glVertex2i(0 + dx, 100 + dy);
	glVertex2i(100 + dx, 100 + dy);
	glVertex2i(100 + dx, 0 + dy);
	glEnd();
	glFlush();
}

void myMouse(GLint button, GLint state, GLint x, GLint y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		dx = x;
		dy = d - y;
		glutPostRedisplay();
	}

}

void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, d);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(w, d);
	glutCreateWindow("myMouse");

	init();
	
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutMainLoop();
}
