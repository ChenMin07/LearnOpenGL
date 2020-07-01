//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <thread>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <chrono>
//#include "shader.h"
//#include "stb_image.h"
//#include <iostream>
//#include "AStar.h"
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 800;
////unsigned int EBO;
//
//unsigned int indices[] = {
//	2, 3, 0, // first triangle
//	3, 1, 0  // second triangle
//};
//
//glm::mat4 transform[9];
//
//void loadAndCreateTexture(const char* image, unsigned int& texture)
//{
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	// set the texture wrapping parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	// set texture filtering parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	// load image, create texture and generate mipmaps
//	int width, height, nrChannels;
//	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//	unsigned char *data = stbi_load(image, &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	stbi_image_free(data);
//}
//
//void setVBO(unsigned int& VBO, float vertices[], unsigned int& EBO)
//{
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*20, vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*6, indices, GL_STATIC_DRAW);
//
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// texture coord attribute
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//}
//
//int getLocation(int state)
//{
//	char statement[10];
//	if (state / 100000000 == 0)
//	{
//		itoa(state, statement + 1, 10);  //当只有8位数时补0
//		statement[0] = '0';
//	}
//	else
//		itoa(state, statement, 10);  //把para的数字转换为字符串
//
//	int ind;
//	for (int i = 0; i < 10; i++)
//		if (statement[i] == '0')
//		{
//			ind = i; break;
//		}
//	return ind;
//}
//
//int getChar(int ind, int state)
//{
//	char statement[10];
//	if (state / 100000000 == 0)
//	{
//		itoa(state, statement + 1, 10);  //当只有8位数时补0
//		statement[0] = '0';
//	}
//	else
//		itoa(state, statement, 10);  //把para的数字转换为字符串
//	return statement[ind] - 48;
//}
//int main()
//{
//	// glfw: initialize and configure
//	// ------------------------------
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//
//	// glfw window creation
//	// --------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	glewInit();
//
//
//	// build and compile our shader program
//	// ------------------------------------
//	Shader ourShader("vertexShader.vs", "fragmentShader.fs"); 
//
//	float vertices0[] = {
//		// positions          // texture coords
//		- 1.0f,   1.0f, 0.0f,   0.0f, 1.0f, // top left
//		- 1.0f,  0.33f, 0.0f,   0.0f, 0.0f, // bottom left
//		-0.33f,	  1.0f, 0.0f,   1.0f, 1.0f, // top right
//		-0.33f,  0.33f, 0.0f,   1.0f, 0.0f  // bottom right 
//	};
//	float vertices1[] = {
//		// positions          // texture coords
//		-0.33f,   1.0f, 0.0f,   0.0f, 1.0f, // top left
//		-0.33f,  0.33f, 0.0f,   0.0f, 0.0f, // bottom left 
//		 0.33f,	  1.0f, 0.0f,   1.0f, 1.0f, // top right
//		 0.33f,  0.33f, 0.0f,   1.0f, 0.0f  // bottom right 
//	};
//	float vertices2[] = {
//		// positions          // texture coords
//		0.33f,   1.0f, 0.0f,   0.0f, 1.0f, // top left
//		0.33f,  0.33f, 0.0f,   0.0f, 0.0f, // bottom left   
//		 1.0f,	 1.0f, 0.0f,   1.0f, 1.0f, // top right  
//		 1.0f,  0.33f, 0.0f,   1.0f, 0.0f  // bottom right 
//	};
//	float vertices3[] = {
//		// positions          // texture coords
//		 -1.0f,  0.33f, 0.0f,   0.0f, 1.0f, // top left
//		 -1.0f, -0.33f, 0.0f,   0.0f, 0.0f, // bottom left  
//		-0.33f,	 0.33f, 0.0f,   1.0f, 1.0f, // top right 
//		-0.33f, -0.33f, 0.0f,   1.0f, 0.0f  // bottom right 
//	};
//	float vertices4[] = {
//		// positions          // texture coords
//		-0.33f,  0.33f, 0.0f,   0.0f, 1.0f, // top left
//		-0.33f, -0.33f, 0.0f,   0.0f, 0.0f, // bottom left
//		 0.33f,	 0.33f, 0.0f,   1.0f, 1.0f, // top right 
//		 0.33f, -0.33f, 0.0f,   1.0f, 0.0f  // bottom right  
//	};
//
//	float vertices5[] = {
//		// positions          // texture coords
//		0.33f,  0.33f, 0.0f,   0.0f, 1.0f, // top left
//		0.33f, -0.33f, 0.0f,   0.0f, 0.0f, // bottom left
//		 1.0f,	0.33f, 0.0f,   1.0f, 1.0f, // top right
//		 1.0f, -0.33f, 0.0f,   1.0f, 0.0f  // bottom right 
//	};
//	float vertices6[] = {
//		// positions          // texture coords
//		 -1.0f,  -0.33f, 0.0f,   0.0f, 1.0f, // top left
//		 -1.0f,   -1.0f, 0.0f,   0.0f, 0.0f, // bottom left
//		-0.33f,	 -0.33f, 0.0f,   1.0f, 1.0f, // top right
//		-0.33f,   -1.0f, 0.0f,   1.0f, 0.0f  // bottom right  
//	};
//	float vertices7[] = {
//		// positions          // texture coords
//		-0.33f, -0.33f, 0.0f,   0.0f, 1.0f, // top left
//		-0.33f, - 1.0f, 0.0f,   0.0f, 0.0f, // bottom left
//		 0.33f, -0.33f, 0.0f,   1.0f, 1.0f, // top right
//		 0.33f, - 1.0f, 0.0f,   1.0f, 0.0f  // bottom right 
//	};
//	float vertices8[] = {
//		// positions          // texture coords
//		0.33f, -0.33f, 0.0f,   0.0f, 1.0f, // top left
//		0.33f, - 1.0f, 0.0f,   0.0f, 0.0f, // bottom left
//		 1.0f, -0.33f, 0.0f,   1.0f, 1.0f, // top right
//		 1.0f, - 1.0f, 0.0f,   1.0f, 0.0f  // bottom right 
//	};
//	float* vertices[9] = { vertices0, vertices1, vertices2, vertices3, vertices4, vertices5, vertices6, vertices7, vertices8 };
//	unsigned int VBO[9], VAO[9],EBO;
//	glGenVertexArrays(9, VAO);
//	glGenBuffers(9, VBO);
//	glGenBuffers(1, &EBO);
//
//	unsigned int texture[9];
//
//	for (int i = 0; i < 9; i++)
//	{
//		glBindVertexArray(VAO[i]);
//		setVBO(VBO[i], vertices[i], EBO);
//		glBindVertexArray(0);
//	}
//
//
//	AStar astar;
//	std::stack<int> s;
//	astar.getPath(s);
//
//	float delta = 0.005f;
//	int tag = 1;
//	int cnt = 0;
//	int move = s.size();
//	int dir;
//	int number;
//	int pre = s.top();
//	cout << s.size() << endl;
//
//
//	while (!glfwWindowShouldClose(window))
//	{
//		//控制移动方向
//		if (!s.empty() && tag == 1)
//		{
//			int now = s.top();
// 
//			int pInd = getLocation(pre);
//			int nInd = getLocation(now);
//			number = getChar(nInd, pre);
//
//			if (nInd - pInd == -3) { dir = 0; tag = 0; }
//			else if (nInd - pInd == 1)  { dir = 1; tag = 0;}
//			else if (nInd - pInd == 3)  { dir = 2; tag = 0;}
//			else if (nInd - pInd == -1) { dir = 3; tag = 0;}
//			else dir = 5;
//
//			pre = now;
//			s.pop();
//		}
//
//		if (tag == 0)
//		{
//			if (dir == 0)
//			{	
//				transform[0] = glm::translate(transform[0], glm::vec3(0, delta, 0.0f));
//				transform[number] = glm::translate(transform[number], glm::vec3(0, -delta, 0.0f));
//			}
//			if (dir == 1)
//			{
//				transform[0] = glm::translate(transform[0], glm::vec3(delta, 0, 0.0f));
//				transform[number] = glm::translate(transform[number], glm::vec3(-delta, -0.0f, 0.0f));
//			}
//			if (dir == 2)
//			{
//				transform[0] = glm::translate(transform[0], glm::vec3(0, -delta, 0.0f));
//				transform[number] = glm::translate(transform[number], glm::vec3(0, delta, 0.0f));
//			}
//			if (dir == 3)
//			{
//				transform[0] = glm::translate(transform[0], glm::vec3(-delta, 0, 0.0f));
//				transform[number] = glm::translate(transform[number], glm::vec3(delta, -0.0f, 0.0f));
//			}
//		}
//		cnt++;
//		if (cnt == 132)
//		{
//			cnt = 0;
//			tag = 1;
//			move--;
//		}
//		if (move == 1)
//			tag = 2;
//
//		processInput(window);
//
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//
//		for (int i = 0; i < 9; i++)
//		{
//			ourShader.use();
//			unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
//			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform[i]));
//
//			glBindVertexArray(VAO[i]);
//			if(i == 0)	loadAndCreateTexture("0.jpg", texture[i]);
//			else if (i == 1) loadAndCreateTexture("1.jpg", texture[i]);
//			else if (i == 2) loadAndCreateTexture("2.jpg", texture[i]);
//			else if (i == 3) loadAndCreateTexture("3.jpg", texture[i]);
//			else if (i == 4) loadAndCreateTexture("4.jpg", texture[i]);
//			else if (i == 5) loadAndCreateTexture("5.jpg", texture[i]);
//			else if (i == 6) loadAndCreateTexture("6.jpg", texture[i]);
//			else if (i == 7) loadAndCreateTexture("7.jpg", texture[i]);
//			else if (i == 8) loadAndCreateTexture("8.jpg", texture[i]);
//
//			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//			glBindTexture(GL_TEXTURE_2D, 0);
//			glBindVertexArray(0);
//		}
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//
//	//glDeleteVertexArrays(1, &VAO);
//	//glDeleteBuffers(1, &VBO);
//
//	glfwTerminate();
//	return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}