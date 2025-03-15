#include<iostream>
#include<glad/glad.h>
#include<vector>
#include<GLFW/glfw3.h>
#include"stb_image.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
using namespace std;

struct vector3 {
	float x, y, z;
};
struct triangle {
	vector3 vert[3];
};
struct mesh {
	vector<triangle> m;
};

struct matrix4 {
	float mat[4][4] = { 0 };
};

struct vector3 matrixMultiply(struct vector3 i, struct matrix4 m) {
	struct vector3 o;
	float w = m.mat[0][3] * i.x + m.mat[1][3] * i.y + m.mat[2][3] * i.z + m.mat[3][3];
	o.x = (m.mat[0][0] * i.x + m.mat[1][0] * i.y + m.mat[2][0] * i.z + m.mat[3][0]);
	o.y = (m.mat[0][1] * i.x + m.mat[1][1] * i.y + m.mat[2][1] * i.z + m.mat[3][1]);
	o.z = (m.mat[0][2] * i.x + m.mat[1][2] * i.y + m.mat[2][2] * i.z + m.mat[3][2]);

	if (w != 0) {
		o.x /= w;
		o.y /= w;
		o.z /= w;
	}
	return o;
}

mesh transform(mesh input_mesh, matrix4 proj_matrix) {
	triangle out_triangle;
	mesh output_mesh;
	for (auto tri : input_mesh.m) {
		out_triangle.vert[0] = matrixMultiply(tri.vert[0], proj_matrix);
		out_triangle.vert[1] = matrixMultiply(tri.vert[1], proj_matrix);
		out_triangle.vert[2] = matrixMultiply(tri.vert[2], proj_matrix);
		output_mesh.m.push_back(out_triangle);
	}
	return output_mesh;
}

GLfloat* tovertexArray(mesh input_mesh) {
	int number_triangles = input_mesh.m.size();
	int number_vector = 3 * number_triangles;
	int number_vertex = 3 * number_vector;
	GLfloat *out_vertices=new GLfloat[number_vertex];
	int count = 0;
	for (auto tri : input_mesh.m) {
		for (auto v : tri.vert) {
			out_vertices[count++]=v.x;
			out_vertices[count++] = v.y;
			out_vertices[count++] = v.z;
		}
	}
	return out_vertices;
}

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
	struct mesh cube,cube_projected;
	cube.m = {
		// SOUTH
		{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		// EAST                                                      
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

		// NORTH                                                     
		{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

		// WEST                                                      
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

		// TOP                                                       
		{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

		// BOTTOM                                                    
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
	};

	struct matrix4 proj_matrix;
	int h = 800, w = 1000;
	float a = (float)h / w;
	float fov = 90.0f;
	float Zn = 1.0f, Zf = 1000.0f;
	float q = Zf / (Zf - Zn);
	float f = 1.0f / tanf(fov * (3.14159f / 180.0f) / 2.0f);
	proj_matrix.mat[0][0] = a * f;
	proj_matrix.mat[1][1] = f;
	proj_matrix.mat[2][2] = q;
	proj_matrix.mat[3][2] = -Zn * q;
	proj_matrix.mat[2][3] = 1.0f;
	proj_matrix.mat[3][3] = 0.0f;

	GLfloat vertices[] = {
	0.0f,0.0f,0.0f ,1.0f,1.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,0.0f ,1.0f,1.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,
	0.0f,1.0f,1.0f ,1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,
	1.0f,0.0f,1.0f ,1.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f, 1.0f,1.0f,1.0f,
	};

	mesh cube_transformed=transform(cube, proj_matrix);
	GLfloat *vert_transformed = tovertexArray(cube_transformed);
	GLuint indices[] = {
	0,3,2,
	0,2,1,
	1,2,5,
	1,2,6,
	0,3,4,
	0,4,7,
	3,4,5,
	3,5,2,
	0,7,6,
	0,1,6,
	7,4,5,
	7,5,6
	};
	int ind_size = sizeof(indices) / sizeof(indices[0]);
	VAO VAO1;
	VAO1.bind();
	VBO VBO1(vert_transformed, sizeof(vert_transformed));
	EBO EBO1(indices, sizeof(indices));
	VBO1.bind();
	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	VAO1.unbind();
	EBO1.bind();
	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();

	glfwSwapBuffers(window);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderPrg.activate();
		VAO1.bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_LINES, ind_size, GL_UNSIGNED_INT, 0);
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
