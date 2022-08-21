#include <gl/glew.h>
#include <gl/glfw3.h>
#include <gl/glut.h>
#include <iostream>
#include <gltools.h>
#include <GLShaderManager.h>
#pragma comment (lib, "glew32s.lib")
#pragma comment (lib, "gltools.lib")

// ����һ������ɫ������
GLShaderManager shaderManager;
// �򵥵��������������ڽ����������ύ����ɫ��ʹ��
GLBatch triangleBatch;

void RenderScene(void) {
	// 1.���һ������һ���ض��Ļ����������������Ҫ�õ���Щ������������Ҫ��գ���Ȼ�����֮ǰʹ�õ������ݣ�����Ȼ���������ɫ��������ģ�建�����ȣ�
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// 2.����һ����ɫ�������������
	GLfloat vRed[] = { 1.0, 0.0, 0.0, 1.0f };

	// 3. ʹ�õ�Ԫ��ɫ��������ͼ�ν�����ɫ����GLT_SHADER_IDENTITY��ɫ���������ɫ��ֻ��ʹ��ָ����ɫ��Ĭ�ϵѿ������������Ļ����Ⱦ����ͼ��
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);

	// 4. �ύ�������ݵ���ɫ�������л���
	triangleBatch.Draw();

	// �ڿ�ʼ������openGL ���ڵ�ʱ������ָ��Ҫһ��˫����������Ⱦ�����������ζ�Ž��ں�̨������������Ⱦ����Ⱦ�����󽻻���ǰ̨��
	glutSwapBuffers();
}


void setupRC() {
	// ����������ɫ��������ɫ����ɫ��
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// û����ɫ������OpenGL ���Ŀ�������޷������κ���Ⱦ�ġ������ʼ��һ����Ⱦ����������renderSence���õ�������ʹ�ù̶�������ɫ��
	shaderManager.InitializeStockShaders();

	// �����ζ���
	GLfloat vVerts[] = {
		-0.5f,0.0f,0.0f,
		0.5f,0.0f,0.0f,
		0.0f,0.5f,0.0f
	};

	// ���������ݴ��ݵ���������������
	triangleBatch.Begin(GL_TRIANGLES, 3);
	triangleBatch.CopyVertexData3f(vVerts);
	triangleBatch.End();
}

void changeSize(int w, int h) {
	// x,y ��������������ͼ�����½����꣬����ȡ��߶�������Ϊ��ʾ��ͨ��x,y ����Ϊ0
	glViewport(0, 0, w, h);
}

int main_2(int argc, char *argv[]) {
	//��ʼ��GLUT��,�������ֻ�Ǵ�˵����������ҳ�ʼ��glut��
	glutInit(&argc, argv);
	/*
	 ��ʼ��˫���崰�ڣ����б�־GLUT_DOUBLE��GLUT_RGBA��GLUT_DEPTH��GLUT_STENCIL�ֱ�ָ
	 ˫���崰�ڡ�RGBA��ɫģʽ����Ȳ��ԡ�ģ�建����

	 --GLUT_DOUBLE`��˫���洰�ڣ���ָ��ͼ����ʵ����������������ִ�еģ�Ȼ��Ѹ��ת���ɴ�����ͼ�����ַ�ʽ�������������ɶ���Ч����
	 --GLUT_DEPTH`����־��һ����Ȼ���������Ϊ��ʾ��һ���֣���������ܹ�ִ����Ȳ��ԣ�
	 --GLUT_STENCIL`��ȷ������Ҳ����һ�����õ�ģ�建������
	 ��ȡ�ģ����Ժ����ϸ�½���
	 */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);

	//GLUT���ڴ�С�����ڱ���
	glutInitWindowSize(800, 600);
	glutCreateWindow("Triangle");

	// ע�ᴰ�ڸı��¼�
	glutReshapeFunc(changeSize);
	// ע����ʾ����������Ҫ���»��Ƶ�ʱ�򣬻����
	glutDisplayFunc(RenderScene);

	// ��ʼ��һ��GLEW�⣬�����Ƿ񱨴�ȷ��OpenGL API�Գ�����ȫ���á�
	GLenum status = glewInit();
	if (GLEW_OK != status) {
		printf("GLEW Error:%s\n", glewGetErrorString(status));
		return 1;
	}

	// ׼��������Ҫ��Ⱦ������
	setupRC();

	// �����¼�ѭ�����൱��iOS��runloop
	glutMainLoop();
	return  0;
}
