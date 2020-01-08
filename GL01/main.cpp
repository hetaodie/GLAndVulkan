//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"

#include <SOIL/SOIL.h>

GLuint VBO,VAO,EBO, texture,texture2;


GLfloat vertices[] = {
	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
};

GLuint indices[] = { // ע��������0��ʼ! 
	0, 1, 3, // ��һ��������
	1, 2, 3  // �ڶ���������
};

void createTexture() {

	int width, height;
	unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image = SOIL_load_image("awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

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


	//createProgram();
	Shader* shader = new Shader("./shader.vs", "./shader.fg");
	createTexture();

		// Load and create a texture 
	//GLuint texture;



	createVAO();

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();//�����û�д����¼�

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shader->Program, "ourTexture1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shader->Program, "ourTexture2"), 1);


		//glUseProgram(program);
		shader->Use();
		//GLint location = glGetUniformLocation(program, "ourColor");
		//if (location == -1)
		//{
		//	exit(0);
		//}

		//GLfloat timeValue = glfwGetTime();
		//GLfloat greenValue = (sin(timeValue) / 2) + 0.5;

		//glUniform4f(location, 0.0, greenValue, 0.0, 1.0);

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);//������ɫ����
	}
	glfwTerminate(); //�ͷŷ������Դ

	return 0;
}

