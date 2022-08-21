#include <GL/glut.h>

void myPolygonTriangle()
{
	int p1[] = { 0, 0 }, p2[] = { 0, 5 }, p4[] = { 5, 5 };
	int p3[] = { 5, 0 }, p5[] = { 6, 6 }, p6[] = { 3, 6 };
	int p7[] = { 4, 8 }, p8[] = { 6, 8 };
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.2, 0.2, 0.2);
	//�����
	/*******************************
	#define GL_TRIANGLES                      0x0004
	#define GL_TRIANGLE_STRIP                 0x0005
	#define GL_TRIANGLE_FAN                   0x0006
	#define GL_QUADS                          0x0007
	#define GL_QUAD_STRIP                     0x0008
	#define GL_POLYGON                        0x0009

	
	GL_TRIANGLES��p1->p3 ������һ�������� ��p4->p6 ������һ��������
	GL_TRIANGLE_STRIP��p1->p2->...->p7->p8 ���������� p1->p3, p2->p4, p5->p7 ....
				����GL_TRIANGLES�Ļ����Ͻ�����˳�������������������
	GL_TRIANGLE_FAN��p2->p1, p3->p1..., pn-1 ->p1, pn->p1�� ���������� p2->p3, p3->p4, p4->p5 ....
				(���е����ӵ�һ���㣬�������е㰴��˳������)
	GL_QUADS��p1->p4 ������һ���Ľ��� ��p5->p8 ������һ���Ľ���
	GL_QUAD_STRIP��p1->p4 ������һ���Ľ��� ��p5->p8 ������һ���Ľ���... ��p3->p5��p4->p6...
				����GL_QUAD_STRIP�Ļ����Ͻ�����˳��������Ľ���������
	GL_POLYGON��p1->p8 �������
	*******************************/
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2iv(p1);
	glVertex2iv(p2);
	glVertex2iv(p3);
	glVertex2iv(p4);
	//glVertex2iv(p5);
	//glVertex2iv(p6);
	//glVertex2iv(p7);
	//glVertex2iv(p8);
	glEnd();
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
	glutCreateWindow("myPolygonTriangle");

	init();
	glutDisplayFunc(myPolygonTriangle);
	glutMainLoop();
	return 0;
}