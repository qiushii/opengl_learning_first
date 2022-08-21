/*********************************************************************
中点画线算法
	1、在x轴和y轴上移动描点，和中点比较大小分析取Yk点还是Yk+1点
	2、Point_y = y > Yk+0.5 ? Yk : Yk+1;  dx = xn - x1, dy = yn - y1
	3、di = Yk + 0.5 - k * Xk - b
	4、递推公式 di + 1 = di - m
**********************************************************************/


#include <GL/glut.h>
#include <iostream>

class Line {
private:
	GLfloat _LineX = 0, _LineY = 0, _LineK = 0, _LineB = 0;
public:
	Line(const GLfloat &k, const GLfloat &b) {
		_LineK = k, _LineB = b;
	}
	GLfloat getY(const GLfloat &x) {
		return _LineK * x + _LineB;
	}
	GLfloat getDx() {
		return 10.0f;
	}
	GLfloat getDy() {
		return getY(5.0f) - getY(-5.0f);   //符号问题 显示只适用于斜率为正数的直线
	}
	GLfloat getK() {
		return _LineK;
	}
	GLfloat getB() {
		return _LineB;
	}
};

void Middraw(Line &line, const GLint &x1, const  GLint &x2) {
	glBegin(GL_POINTS);
	GLfloat di = line.getY(x1) + 0.05 - line.getK() * x1 - line.getK();
	GLfloat d = di, Yn = line.getY(x1);
	for (GLfloat i = x1; i < x2; i++) {
		if (d > 0) {
			di = d - line.getK();
			Yn = line.getY(i - 1);
		}
		else {
			di = d + 1 - line.getK();
			Yn = line.getY(i);
		}
		d = di;
		glVertex2f(i, Yn);
		std::cout << Yn << std::endl;
	}
	glEnd();
	glFlush();
}

void DrawLine(GLfloat& x1, GLfloat& y1, GLfloat& x2, GLfloat& y2) {
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glFlush();
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1);
	glColor3f(0.2f, 0.3f, 0.4f);
	Line line(-0.4, 98);
	Middraw(line, -300, 300);
}

void init() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-300, 300, -300, 300);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(600, 600);
	glutInitWindowSize(600, 600);
	glutCreateWindow("myMid");

	init();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}