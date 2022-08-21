#include <GL/glut.h>

void myPoints()
{
	//����
	glClear(GL_COLOR_BUFFER_BIT);
	//ÿ����ռ3������
	glPointSize(3);
	//����Ϊ���Ƶ�
	glBegin(GL_POINTS);
	//������ɫ
	glColor3f(1.0, 0.0, 0.0);
	//����
	/***************************
	#define GL_POINTS                         0x000
	***************************/
	glVertex2i(-3, 3);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(10, 20);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(0, -15);
	//����
	glEnd();
	//����
	glFlush();
}

void init()
{
	//��frame buff����Ϊ��ɫ
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//��ʾ��Χ
	gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	//��ʾģʽ
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); 
	//����λ��
	glutInitWindowPosition(200, 300);
	//���ڴ�С
	glutInitWindowSize(300, 300);
	//��������
	glutCreateWindow("Display Points");

	//��ʼ��
	init();
	//��ʾ�ص�
	glutDisplayFunc(myPoints);
	glutMainLoop();

	return 0;

}