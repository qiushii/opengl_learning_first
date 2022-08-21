#include <gl/glut.h>

int yd = 0, xd = 0;


void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.6);
	glPointSize(10);
	glBegin(GL_POLYGON);
	glVertex2i(0 + xd, 0 + yd);
	glVertex2i(0 + xd, 5 + yd);
	glVertex2i(5 + xd, 5 + yd);
	glVertex2i(5 + xd, 0 + yd);
	glEnd();
	glFlush();
}

void myKeyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w' : yd++; break;
	case 's' : yd--; break;
	case 'a' : xd--; break;
	case 'd' : xd++; break;
	default:
		break;
	}
	glutPostRedisplay();
}

void init()
{
	glClearColor(128.0, 128.0, 128.0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-20,20, -20, 20);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 500);
	glutCreateWindow("myKeyBoard");

	init();
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(myKeyBoard);
	glutMainLoop();
	return 0;
}