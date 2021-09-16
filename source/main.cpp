#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main(int argc, char* argv[]) {
  // Init GLFW and register openGL version/profile
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

  // Change background color
  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window);


  // This while loop prevents the program to terminate before requested
  while(!glfwWindowShouldClose(window)) {
    // Handle incomming events
    glfwPollEvents();
  }

  // Terminate program
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}