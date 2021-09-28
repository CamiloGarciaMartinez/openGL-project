#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "shader.h"

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"



int main(int argc, char* argv[]) {
  // Init GLFW and register openGL version/profile
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


  // Vertices of the figuere we want to render
  GLfloat vertices[] = {
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,      0.8f, 0.3f, 0.02f,  // bottom left vertice
     0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,      0.8f, 0.3f, 0.02f,  // bottom right vertice
     0.5f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,   1.0f, 0.6f, 0.32f,  // upper right vertice
    -0.5f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,   0.9f, 0.45f, 0.17f, // upper left vertice

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

  std::string vertexShaderPath = "../resources/shaders/default.vert";
  std::string fragmentShaderPath = "../resources/shaders/default.frag";

  Shader shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
  


  // Create and initilize Vertex Arrays Object ande Vertex Buffer Object (the order is important)
  VAO VAO01;
  VAO01.Bind();

  VBO VBO01(vertices, sizeof(vertices));
  EBO EBO01(squareIndices, sizeof(squareIndices));

  VAO01.LinkAttrib(VBO01, 0, 4, GL_FLOAT, 6 * sizeof(float), (void*)0);
  VAO01.LinkAttrib(VBO01, 1, 4, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

  VBO01.Unbind();
  VAO01.Unbind(); 
  EBO01.Unbind();


  // Change background color
  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window);


  // This while loop prevents the program to terminate before requested
  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader.Activate();
    VAO01.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    glfwSwapBuffers(window);  // swap screen buffers  to  refresh the window
    // Handle incomming events
    glfwPollEvents();
  }


  VAO01.Delete();
  VBO01.Delete();
  EBO01.Delete();
  shader.Delete();


  // Terminate program
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}