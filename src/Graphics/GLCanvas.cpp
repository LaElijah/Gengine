#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
#include "../../include/Graphics/GLCanvas.h"

namespace Graphics {


void processInput(GLFWwindow *window, float &visibility)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
  
    if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) && visibility < 1.0f)
      visibility = visibility + 0.01f;

    if ((glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) && visibility > 0.0f)
      visibility = visibility - 0.01f;


        
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}


}

namespace Graphics {

    GLCanvas::GLCanvas(
        unsigned int width,
        unsigned int height, 
        unsigned int version) // TODO: Set an enum up for all available versions
    {
      ScreenWidth = width;
      ScreenHeight = height;
      VERSION = version;
    }


    void GLCanvas::initializeCanvas()
    {
      GLCanvas::startWindow();
      glfwMakeContextCurrent(Window);
      glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback); 
      GLCanvas::loadGlad(); 
    }

    GLFWwindow *GLCanvas::getWindow() 
    {
      return Window;
    }


    int ScreenWidth = 800;
    int ScreenHeight = 600;
    const char *WindowName = "Test";
    int VERSION = 3;
    GLFWwindow* Window;

    
    void GLCanvas::startWindow() 
    {
      glfwInit();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // glfw window creation
    // --------------------
      Window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Test", NULL, NULL);
      if (Window == NULL)
      {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Window creation error");
      }
    }



    void GLCanvas::loadGlad() 
    {
    // glad: load all OpenGL function pointers
    // ---------------------------------------
      if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
      {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw std::runtime_error("GLAD ERROR");
      }
    }
};


