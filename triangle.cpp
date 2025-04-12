#include "triangle_mesh.h"
#include <vector>
#include <glad/glad.h>

TriangleMesh::TriangleMesh() {
    std::vector<float> positions = {
        -1.0f, -1.0f, 0.0f, //bottom left
         1.0f, -1.0f, 0.0f, //bottom right
        -1.0f,  1.0f, 0.0f, //top left
         1.0f,  1.0f, 0.0f  //top right

    };
    std::vector<int> colorIndices = {
         0, 1, 2, 3
    };
    std::vector<int> elementIndices = {
         0, 1, 2, 2, 1, 3
    };
    element_count = 6;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    VBOs.resize(2);
    glGenBuffers(2, VBOs.data());
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(),
        GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT,
        GL_FALSE, 12, (void*)0);
    glEnableVertexAttribArray(0);

    //color
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, colorIndices.size() * sizeof(float), colorIndices.data(),
        GL_STATIC_DRAW);


    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementIndices.size() * sizeof(int), elementIndices.data(),
        GL_STATIC_DRAW);

}

void TriangleMesh::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, element_count, GL_UNSIGNED_INT, 0);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBOs.data());
    glDeleteBuffers(1, &EBO);

}