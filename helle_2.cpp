#include <gl/glew.h>
#include <gl/glfw3.h>
#include <gl/glut.h>
#include <iostream>

#pragma comment (lib, "glew32s.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

using namespace std;

#define numVAOs 1 

GLuint renderingProgram;
GLuint vao[numVAOs];


void printShaderLof(GLuint shader)
{
	int len = 0;
	int chWrittn = 0;
	char *log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		cout << "shader info log: " << log << endl;
		free(log);
	}
}

void printProgramLog(int prog)
{
	int len = 0;
	int chWrittn = 0;
	char *log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		cout << " program info log: " << log << endl;
		free(log);
	}
}

bool checkOpenGlError()
{
	bool founderror = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		cout << " gl_error: " << glErr << endl;
		founderror = true;
		glErr = glGetError();
	}
	return founderror;
}



GLuint createShaderProgram()
{
	const char *vshaderSource =
		"#version 330 \n"
		"void main() {\n"
		"gl_Position = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";

	const char *fshaderSource =
		"#version 330 \n"
		"out vec4 color; \n"
		"void main(void) \n"
		"{ color = vec4(1.0, 0.0, 0.0, 1.0); }";
	
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;

	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glShaderSource(fShader, 1, &fshaderSource, NULL);
	//vert shader编译
	glCompileShader(vShader);					
	checkOpenGlError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1)
	{
		cout << " vert shader compile error" << endl;
		printShaderLof(vShader);
	}
	//frag shader 编译
	glCompileShader(fShader);
	checkOpenGlError();
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1)
	{
		cout << " frag shader compile error" << endl;
		printShaderLof(fShader);
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	
	//着色器链接
	glLinkProgram(program);
	checkOpenGlError();
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (linked != 1)
	{
		cout << " program linked error" << endl;
		printProgramLog(program);
	}

	return program;
}


void init(GLFWwindow* window) 
{
	renderingProgram = createShaderProgram();
	GLint location = glGetAttribLocation(renderingProgram, "position");
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(0);
}


void display(GLFWwindow *window, double currentTime)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glUseProgram(renderingProgram);
	glPointSize(10.0f);
	glDrawArrays(GL_POINTS, 0, 10);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(void)
{
	if (!glfwInit()) 
	{ 
		exit(EXIT_FAILURE); 
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	//主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	//次版本号
	GLFWwindow* window = glfwCreateWindow(600, 600, "chapter2 - programl", NULL, NULL); //window标题
	glfwMakeContextCurrent(window);					//make context
	if (glewInit() != GLEW_OK)						//init glew
	{
		exit(EXIT_FAILURE);
	}
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glfwSwapInterval(1);
	init(window);
	glClear(GL_COLOR_BUFFER_BIT);
	while (!glfwWindowShouldClose(window))
	{
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

