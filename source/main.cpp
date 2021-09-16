#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

// Shaders sources

// Vertex  shader source
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position =  vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0"; 

// Fragment shader source
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor =  vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0"; 



int main(int argc, char* argv[]) {
  // Init GLFW and register openGL version/profile
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


  // Vertices of the figuere we want to render
  GLfloat vertices[] = {
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
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


  // Creates a vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Creates a reference to a GL_VERTEX_SHADER
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Link the shader to the shader source
  glCompileShader(vertexShader);  // Compile the shader for use in the GL context

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  GLuint shaderProgram = glCreateProgram(); // Creates a shader program, it bundles the shaders
  glAttachShader(shaderProgram, vertexShader);  
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram); // Link the shader program to the GL context

  // Delete shaders, the functionality of  these is safe in the shader program
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);



  // Create and initilize Vertex Arrays Object ande Vertex Buffer Object (the order is important)
  GLuint VAO, VBO;  // create references to the VAO and VBO

  glGenVertexArrays(1, &VAO); // generate the VAO
  glGenBuffers(1, &VBO); // generate the VBO

  glBindVertexArray(VAO); // bind the VAO to the current context

  glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind the VBO to the current context
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // load the vertex data to the VBO

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //  configure the VAO, this funtion help to  communicate with the shaders
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind the VBO
  glBindVertexArray(0); // unbind the VAO



  // Change background color
  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window);


  // This while loop prevents the program to terminate before requested
  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3); // draw to the back screen buffer


    glfwSwapBuffers(window);  // swap screen buffers  to  refresh the window
    // Handle incomming events
    glfwPollEvents();
  }


  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);


  // Terminate program
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}