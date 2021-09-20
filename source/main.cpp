#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "shader.h"





int main(int argc, char* argv[]) {
  // Init GLFW and register openGL version/profile
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


  // Vertices of the figuere we want to render
  GLfloat vertices[] = {
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // bottom left vertice
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // bottom right vertice
    0.5f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // upper right vertice
    -0.5f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // upper left vertice

    /*
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner left vertice
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  // inner right vertice
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f      // inner down vertice
    */
  };

  GLuint indices[] = {
    0, 3, 5,  // lower left triangle
    3, 2, 4,  // lower right triangle
    5, 4, 1   // upper triangle
  };

  GLuint squareIndices[] = {
    0, 1, 2,
    0, 2, 3
  };

  // Create window, if failed terminate program
  GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
  if ( window == NULL )  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }
  // Set current conxtext to window
  glfwMakeContextCurrent(window);

  // Init glad
  gladLoadGL();

  // Set viewport
  glViewport(0, 0, 800, 800);

  char* vertexShaderPath = "../resources/shaders/default.vert";
  char* fragmentShaderPath = "../resources/shaders/default.frag";

  Shader shader(vertexShaderPath, fragmentShaderPath);
  


  // Create and initilize Vertex Arrays Object ande Vertex Buffer Object (the order is important)
  GLuint VAO, VBO, EBO;  // create references to the VAO and VBO

  glGenVertexArrays(1, &VAO); // generate the VAO
  glGenBuffers(1, &VBO); // generate the VBO
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO); // bind the VAO to the current context

  glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind the VBO to the current context
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // load the vertex data to the VBO

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //  configure the VAO, this funtion help to  communicate with the shaders
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind the VBO
  glBindVertexArray(0); // unbind the VAO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


  // Change background color
  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window);


  // This while loop prevents the program to terminate before requested
  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader.Activate();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    glfwSwapBuffers(window);  // swap screen buffers  to  refresh the window
    // Handle incomming events
    glfwPollEvents();
  }


  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  shader.Delete();


  // Terminate program
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}