#include"VAO.h"
VAO::VAO() {
	glGenVertexArrays(1, &ID);
}
void VAO::bind() {
	glBindVertexArray(ID);
}
void VAO::unbind() {
	glBindVertexArray(0);
}
void VAO::linkAttrib(VBO B, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	B.bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	B.unbind();
}
void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}