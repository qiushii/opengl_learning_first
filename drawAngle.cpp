#include <gl/glew.h>
#include <gl/glfw3.h>
#include <gl/glut.h>
#include <iostream>
#include <gltools.h>
#include <GLShaderManager.h>
#pragma comment (lib, "glew32s.lib")
#pragma comment (lib, "gltools.lib")

// 定义一个，着色管理器
GLShaderManager shaderManager;
// 简单的批次容器，用于将顶点数据提交给着色器使用
GLBatch triangleBatch;

void RenderScene(void) {
	// 1.清除一个或者一组特定的缓存区，如果后面需要用到这些缓冲区，就需要清空，不然会出现之前使用的脏数据（如深度缓冲区，颜色缓冲区，模板缓冲区等）
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// 2.设置一个颜色用来填充三角形
	GLfloat vRed[] = { 1.0, 0.0, 0.0, 1.0f };

	// 3. 使用单元着色器，来对图形进行着色，即GLT_SHADER_IDENTITY着色器，这个着色器只是使用指定颜色以默认笛卡尔坐标第在屏幕上渲染几何图形
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);

	// 4. 提交顶点数据到着色器，进行绘制
	triangleBatch.Draw();

	// 在开始的设置openGL 窗口的时候，我们指定要一个双缓冲区的渲染环境。这就意味着将在后台缓冲区进行渲染，渲染结束后交换给前台。
	glutSwapBuffers();
}


void setupRC() {
	// 设置清屏颜色（背景颜色，白色）
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// 没有着色器，在OpenGL 核心框架中是无法进行任何渲染的。这里初始化一个渲染管理器，在renderSence会用到。这里使用固定管线着色器
	shaderManager.InitializeStockShaders();

	// 三角形顶点
	GLfloat vVerts[] = {
		-0.5f,0.0f,0.0f,
		0.5f,0.0f,0.0f,
		0.0f,0.5f,0.0f
	};

	// 将顶点数据传递到三角形批次类中
	triangleBatch.Begin(GL_TRIANGLES, 3);
	triangleBatch.CopyVertexData3f(vVerts);
	triangleBatch.End();
}

void changeSize(int w, int h) {
	// x,y 参数代表窗口中视图的左下角坐标，而宽度、高度是像素为表示，通常x,y 都是为0
	glViewport(0, 0, w, h);
}

int main_2(int argc, char *argv[]) {
	//初始化GLUT库,这个函数只是传说命令参数并且初始化glut库
	glutInit(&argc, argv);
	/*
	 初始化双缓冲窗口，其中标志GLUT_DOUBLE、GLUT_RGBA、GLUT_DEPTH、GLUT_STENCIL分别指
	 双缓冲窗口、RGBA颜色模式、深度测试、模板缓冲区

	 --GLUT_DOUBLE`：双缓存窗口，是指绘图命令实际上是离屏缓存区执行的，然后迅速转换成窗口视图，这种方式，经常用来生成动画效果；
	 --GLUT_DEPTH`：标志将一个深度缓存区分配为显示的一部分，因此我们能够执行深度测试；
	 --GLUT_STENCIL`：确保我们也会有一个可用的模板缓存区。
	 深度、模板测试后面会细致讲到
	 */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);

	//GLUT窗口大小、窗口标题
	glutInitWindowSize(800, 600);
	glutCreateWindow("Triangle");

	// 注册窗口改变事件
	glutReshapeFunc(changeSize);
	// 注册显示函数，当需要重新绘制的时候，会调用
	glutDisplayFunc(RenderScene);

	// 初始化一个GLEW库，测试是否报错，确保OpenGL API对程序完全可用。
	GLenum status = glewInit();
	if (GLEW_OK != status) {
		printf("GLEW Error:%s\n", glewGetErrorString(status));
		return 1;
	}

	// 准备我们需要渲染的数据
	setupRC();

	// 开启事件循环，相当于iOS的runloop
	glutMainLoop();
	return  0;
}
