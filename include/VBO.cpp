#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
  glGenBuffers(1, &ID);  // generate Vertex Buffer Object
  
  glBindBuffer(GL_ARRAY_BUFFER, ID);  // bind to the current context
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // load data to the buffer
}

void VBO::Bind() {
  glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
  glDeleteBuffers(1, &ID);
}