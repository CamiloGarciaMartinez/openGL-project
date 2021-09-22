#include "EBO.h"

EBO::EBO(GLuint* vertices, GLsizeiptr size) {
  glGenBuffers(1, &ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

EBO::Bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

EBO::Unbind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

EBO::Delete() {
  glDeleteBuffers(1, &ID);
}