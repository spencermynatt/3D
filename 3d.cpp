
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
const char* vertex_shader =
"#version 430 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec2 texture_coordinates;\n"
"out vec2 new_texture_coordinates;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"new_texture_coordinates = texture_coordinates;\n"
"gl_Position = projection * view * model * vec4(position, 1);\n" 
//this always has to be in the order
	
"}\n";
const char* fragment_shader =
"#version 430 core\n"
"out vec4 filled_textured;\n"
"in vec2 new_texture_coordinates;\n"
"uniform sampler2D tex;\n"
"void main()\n"
"{\n"
"filled_textured = texture(tex, new_texture_coordinates);\n"
"}\n";
int main() {


	glfwInit();
	GLFWwindow* pointer_to_window = glfwCreateWindow(800, 600, "E", NULL, NULL);
	if (pointer_to_window == NULL)
	{
		cout << "terminate";
	}
	
	glfwMakeContextCurrent(pointer_to_window);
	glewInit();
	glViewport(0, 0, 800, 600);
	int vertex = glCreateShader(GL_VERTEX_SHADER);
	int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const char* pointer_to_strings[1];
	pointer_to_strings[0] = vertex_shader;
	glShaderSource(vertex, 1, pointer_to_strings, 0);
	pointer_to_strings[0] = fragment_shader;
	glShaderSource(fragment, 1, pointer_to_strings, 0);
	glCompileShader(vertex);
	glCompileShader(fragment);
	int program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	float vertices[]{
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f

	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * 4, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * 4, (void*)(3 * 4));


	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width,  height, nrchannels;
	unsigned char* data = SOIL_load_image("resources/bunny.jpg", &width, &height, &nrchannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	while(!glfwWindowShouldClose(pointer_to_window))
	{
		glClearColor(0.2f, 0.7f, 0.5f, 2.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, texture);

		// create transformations
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
				//[ 1, 0, 0, TX,        
				//  0, 1, 0, TY,   all of these start of as this matrix
				//  0, 0, 1, TZ,       
                              //    0, 0, 0, 1 ]        
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		//model gets set equal to a rotation matrix, and this is repsonsible for rotating everything single vertice on the cubee
		//and eventually this matrix will get multiplied
		//angle to rotate on
		//axis we want to rotate on
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		//this will move cube slighlty when multiplied by all matrices
		projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
		//projection gets set equal to perspective matrix
		//field of view is first aspect, 45,
		//aspect ratio is 800/600, width and height
		//near clipping plane, how near does screen just clip something
		//far clipping, how far does screen clip
	
		
		
		glUseProgram(program);
		unsigned int modelLoc = glGetUniformLocation(program, "model");
		unsigned int viewLoc = glGetUniformLocation(program, "view");
		unsigned int projectionLoc = glGetUniformLocation(program, "projection");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE,  glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(VAO);
		glfwPollEvents();
		glfwSwapBuffers(pointer_to_window);
	};
	glfwTerminate();
	return 0;

}
