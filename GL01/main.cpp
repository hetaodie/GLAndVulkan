//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"

#include <SOIL/SOIL.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Camera.h"
GLuint VBO,VAO,EBO, texture,texture2;


float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,  1.0f,  0.0f
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

GLuint indices[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};

Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));


void createTexture() {


	int width, height;
	unsigned char* image = SOIL_load_image("container2.png", &width, &height, 0, SOIL_LOAD_RGB);

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

	image = SOIL_load_image("container2_specular.png", &width, &height, 0, SOIL_LOAD_RGB);
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

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	return VAO;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//当用户按下ESC键，我们设置window窗口的WindowShouldClose 属性为true
	//关闭应用程序
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);

	}

}

void draw(int x, int y, int width, int height,Shader *shader, float *color) {

	glViewport(x, y, width , height );
	glEnable(GL_DEPTH_TEST);
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClearColor(color[0], color[1], color[2], color[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader->Program, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(shader->Program, "material.specular"), 1);


	//glUseProgram(program);
	shader->Use();

	//glm::mat4 model;
	////model = glm::rotate(model, -20.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//model = glm::rotate(model, (GLfloat)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
	//GLuint transformLoc = glGetUniformLocation(shader->Program, "model");
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));

	/*glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));*/

	//GLuint lightColorLoc = glGetUniformLocation(shader->Program, "lightColor");
	//glUniform3f(lightColorLoc, 1.0, 1.0, 1.0);

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	GLuint lightPosLoc = glGetUniformLocation(shader->Program, "linearLight.position");
	glUniform3f(lightPosLoc, 0.0f, 0.0f, 2.0f);

	GLint lightAmbientLoc = glGetUniformLocation(shader->Program, "linearLight.ambient");
	GLint lightDiffuseLoc = glGetUniformLocation(shader->Program, "linearLight.diffuse");
	GLint lightSpecularLoc = glGetUniformLocation(shader->Program, "linearLight.specular");

	glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
	glUniform3f(lightDiffuseLoc, 0.5f, 0.5f, 0.5f);// 让我们把这个光调暗一点，这样会看起来更自然
	glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);

	glUniform1f(glGetUniformLocation(shader->Program, "linearLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader->Program, "linearLight.linear"), 0.09);
	glUniform1f(glGetUniformLocation(shader->Program, "linearLight.quadratic"), 0.032);


	GLint spotlightPosLoc = glGetUniformLocation(shader->Program, "spotLight.position");
	GLint spotlightSpotdirLoc = glGetUniformLocation(shader->Program, "spotLight.direction");
	GLint spotlightSpotCutOffLoc = glGetUniformLocation(shader->Program, "spotLight.cutOff");
	GLint spotviewPosLoc = glGetUniformLocation(shader->Program, "viewPos");
	glUniform3f(spotlightPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
	glUniform3f(spotlightSpotdirLoc, camera.Front.x, camera.Front.y, camera.Front.z);
	glUniform1f(spotlightSpotCutOffLoc, glm::cos(glm::radians(12.5f)));
	glUniform3f(spotviewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
	// Set lights properties
	glUniform3f(glGetUniformLocation(shader->Program, "spotLight.ambient"), 0.1f, 0.1f, 0.1f);
	// We set the diffuse intensity a bit higher; note that the right lighting conditions differ with each lighting method and environment.
	// Each environment and lighting type requires some tweaking of these variables to get the best out of your environment.
	glUniform3f(glGetUniformLocation(shader->Program, "spotLight.diffuse"), 0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(shader->Program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(shader->Program, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader->Program, "spotLight.linear"), 0.09);
	glUniform1f(glGetUniformLocation(shader->Program, "spotLight.quadratic"), 0.032);

	GLfloat camX = 0.0f;
	GLfloat camZ = 3.0f;
	GLfloat radius = 10.0f;
	//camX = sin(glfwGetTime()) * radius;
	//camZ = cos(glfwGetTime()) * radius;
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

	GLuint viewLoc = glGetUniformLocation(shader->Program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	GLuint viewPosLoc = glGetUniformLocation(shader->Program, "viewPos");
	glUniform3f(viewPosLoc, camX, 0.0, camZ);

	glm::mat4 projection;
	projection = glm::perspective(45.0f, width / height * 1.0f, 0.1f, 100.0f);
	GLuint projectionLoc = glGetUniformLocation(shader->Program, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAO);

	for (GLuint i = 0; i < 10; i++)
	{
		glm::mat4 model;
		model = glm::translate(model, cubePositions[i]);
		GLfloat angle = (i + 1.0) * glfwGetTime()/10.0f;

		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
		GLuint modelLoc = glGetUniformLocation(shader->Program, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	//glDrawArrays(GL_TRIANGLES, 0, 36);

	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDisable(GL_DEPTH_TEST);
}

int main() {

	// 下面的代码是使用glfw 的方法
	
	//1.初始化glfw
	glfwInit();
	
	//2.接下来三个函数为配置glfw

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 设置主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //设置次版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 使用核心模式，不允许用户调整窗口大小
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //当使用macox时需要添加词句函数
	

	//创建一个窗口对象，这个窗口对象存放所有和窗口相关的数据，而且会被GLFW的其他函数频繁用到
	//第一二个参数为宽高，第三个为窗口的名称，
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	//注册回调函数
	glfwSetKeyCallback(window, key_callback);

	////GLEW 是用来管理opengl的函数指针的，所以在调用任何opengl的函数之前需要初始化GLEW

	glewExperimental = GL_TRUE; //使GLEW管理opengl的函数指针时，更多的使用现代化的技术

	if (glewInit() != GLEW_OK) 
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);//从glfw中获取宽高
	


	//createProgram();
	Shader* shader = new Shader("./shader.vs", "./shader.fg");
	createTexture();

		// Load and create a texture 
	//GLuint texture;



	createVAO();
	int num = 0;
	while(!glfwWindowShouldClose(window))
	{
		
		glfwPollEvents();//检查有没有触发事件
		float color[4] = { 1.0, 1.0, 1.0, 1.0 };
		draw(0, 0, width, height, shader, color);


		glfwSwapBuffers(window);//交换颜色缓冲
	}
	glfwTerminate(); //释放分配的资源

	return 0;
}



