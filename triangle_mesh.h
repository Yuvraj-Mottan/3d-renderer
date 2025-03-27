#pragma once
#include<vector>
#include<glad/glad.h>
class TriangleMesh {
public:
	TriangleMesh();
	void draw();
	~TriangleMesh();

private:
	unsigned int VAO, element_count,EBO;

	std::vector<unsigned int> VBOs;
};