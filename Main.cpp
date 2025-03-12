#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"stb_image.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
using namespace std;

class vector3
{
public:
	int x, y, z;
	vector3(int x,int y,int z){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	vector3 operator*(float const& a) {
		return vector3(this->x * a, this->y * a, this->z * a);
	}
	vector3 operator+(vector3 const& v2) {
		return vector3(this->x + v2.x, this->y + v2.y, this->z + v2.z);
	}
	~vector3();
};
class matrix4 {
public:
	int a, b, c, d;

};
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "3D renderer window", NULL, NULL);
	if (!window) {
		cout << "Window cannot be opened" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 1000, 1000);
	Shader shaderPrg("default.vert", "default.frag");
	
	GLfloat vertices[] = {
	-0.5f,0.5f,0.0f , 1.0f,0.0f,0.0f,
	0.5f,0.5f,0.0f ,  0.0f,1.0f,0.0f,
	0.5f,-0.5f,0.0f,  0.0f,0.0f,1.0f,
	-0.5f,-0.5f,0.0f, 1.0f,1.0f,1.0f
	};
	GLuint indices[] = {
		0,1,2,
		0,2,3
	};
	VAO VAO1;
	VAO1.bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	VBO1.bind();
	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));

	VAO1.unbind();
	EBO1.bind();
	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();
	GLuint uniID = glGetUniformLocation(shaderPrg.ID, "scale");
	glfwSwapBuffers(window);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.3f, 0.0f, 0.13f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderPrg.activate();
		glUniform1f(uniID, 0.3f);
		VAO1.bind();
		glDrawElements(GL_TRIANGLES,6 , GL_UNSIGNED_INT,0);
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	shaderPrg.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
