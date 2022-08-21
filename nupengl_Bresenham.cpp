/*********************************************************************
Bresenham算法
	1、在x轴和y轴上移动描点，分析取Yk点还是Yk+1点
	2、PointY = du < dl ? Yk+1 : Yk ;  dx = xn - x1, dy = yn - y1
	3、dl - du = 2 * K * Xk+1 - 2 * Yk + 2 * b - 1;
	4、令Pk = dl - du, 推导得到公式 Pk = 2*dy*Xk - 2*dx*Yk + 2*dy + dx*(2*b - 1) 
	5、递推公式 Pk+1 = Pk + 2*dy - 2*dx*(Yk+1 - Yk)
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
	GLfloat getY(const GLfloat &x){
		return _LineK * x + _LineB;
	}
	GLfloat getDx() {
		return 600.0f;
	}
	GLfloat getDy() {
		return getY(300.0f) - getY(-300.0f);
	}
	GLfloat getK() {
		return _LineK;
	}
	GLfloat getB() {
		return _LineB;
	}
};

void Bresenham(Line &line, const GLint &x1, const  GLint &x2){
	glBegin(GL_POINTS);
	GLfloat Pi = 0;
	GLfloat P = 2*line.getDy()*x1 - 2*line.getDx()*line.getY(x1) 
				+ 2*line.getDy() + line.getDx()*(2*line.getB()-1);
	GLfloat Yn = line.getY(x1);
	for (GLfloat i = x1; i < x2; i = i + 0.01f){
		if (P < 0){
			Pi = P + 2 * line.getDy();
		}else{
			Yn = line.getY(i);
			Pi = P + 2 * line.getDy() - 2 * line.getDx() * (line.getY(i+0.01f) - line.getY(i));		
		}
		P = Pi;
		glVertex2f(i, Yn);
	}
	glEnd();
	glFlush();
}

void DrawLine(GLfloat& x1, GLfloat& y1, GLfloat& x2, GLfloat& y2){
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glFlush();
}

void myDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1);
	glColor3f(0.2f, 0.3f, 0.4f);
	Line line(-1, -100);
	Bresenham(line, -300, 300);
}

void init(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-300, 300, -300, 300);
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(600, 600);
	glutInitWindowSize(600, 600);
	glutCreateWindow("myBresenham");

	init();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}