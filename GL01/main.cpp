//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>
#include <iostream>

GLuint VBO,VAO,EBO;
GLfloat vertices[] = {
	0.5f, 0.5f, 0.0f,   // ���Ͻ�
	0.5f, -0.5f, 0.0f,  // ���½�
	-0.5f, -0.5f, 0.0f, // ���½�
	-0.5f, 0.5f, 0.0f   // ���Ͻ�
};

GLuint indices[] = { // ע��������0��ʼ! 
	0, 1, 3, // ��һ��������
	1, 2, 3  // �ڶ���������
};

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"out vec3 inputColor;\n"
"void main()\n"
"{\n"
"inputColor = position;\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"in vec3 inputColor;\n"
"void main()\n"
"{\n"
"color = vec4(inputColor.x, inputColor.y, inputColor.z, 1.0);\n"
"//color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

GLuint program = 0;
GLuint createShader(GLenum type, const GLchar* source) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

void createProgram() {
	if (program != 0)
	{
		return;
	}
	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}


GLuint createVAO() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	return VAO;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//���û�����ESC������������window���ڵ�WindowShouldClose ����Ϊtrue
	//�ر�Ӧ�ó���
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);

	}

}

int main() {

	// ����Ĵ�����ʹ��glfw �ķ���
	
	//1.��ʼ��glfw
	glfwInit();
	
	//2.��������������Ϊ����glfw

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // �������汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //���ôΰ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // ʹ�ú���ģʽ���������û��������ڴ�С
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //��ʹ��macoxʱ��Ҫ��Ӵʾ亯��
	

	//����һ�����ڶ���������ڶ��������кʹ�����ص����ݣ����һᱻGLFW����������Ƶ���õ�
	//��һ��������Ϊ��ߣ�������Ϊ���ڵ����ƣ�
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	//ע��ص�����
	glfwSetKeyCallback(window, key_callback);

	////GLEW ����������opengl�ĺ���ָ��ģ������ڵ����κ�opengl�ĺ���֮ǰ��Ҫ��ʼ��GLEW

	glewExperimental = GL_TRUE; //ʹGLEW����opengl�ĺ���ָ��ʱ�������ʹ���ִ����ļ���

	if (glewInit() != GLEW_OK) 
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);//��glfw�л�ȡ���
	glViewport(0, 0, width, height);


	createProgram();
	createVAO();

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();//�����û�д����¼�

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);//������ɫ����
	}
	glfwTerminate(); //�ͷŷ������Դ

	return 0;
}

