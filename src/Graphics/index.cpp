#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLCanvas.h"
#include "Shader.h"
#include <glm/ext/matrix_transform.hpp>
#include <math.h>
#include "../../external/imgui/imgui.h"
#include "../../external/imgui/imgui_impl_opengl3.h"
#include "../../external/imgui/imgui_impl_glfw.h"
//#include "../../external/STB_IMAGE/stb_image.h"
#include "../../external/STB_IMAGE/stb_image.h"
//#include "../../include/Graphics/Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Globals.cpp"
#include "Model.h"
#include "ResourceManager.h"
#include <iostream>
#include "FileReader.h"
#include "Renderer.h"

//Graphics::FileReader fileReader(".");

// settings
float deltaTime;
float lastFrame = 0.0f;

bool cameraDisabled = true;
    bool drawGui = true; 
float SCREEN_WIDTH = 1920;
float SCREEN_HEIGHT = 1080;
float currentFrame;

void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);  

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow *window);

Graphics::Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT);
Graphics::GLCanvas canvas(SCREEN_WIDTH, SCREEN_HEIGHT);;    

Graphics::ResourceManager resourceManager;

Graphics::Renderer renderer;

Graphics::Shader simpleShader(
        "/home/laelijah/Gengine/data/Shaders/simpleModel.vs",
        "/home/laelijah/Gengine/data/Shaders/simpleModel.fs");


Graphics::Shader simpleShader2(
        "/home/laelijah/Gengine/data/Shaders/simpleModel.vs",
        "/home/laelijah/Gengine/data/Shaders/simpleModel.fs");




    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 model2 = glm::mat4(1.0f);
    glm::mat4 model3 = glm::mat4(1.0f);


    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);




int main()
{
	resourceManager.loadModelPaths();
 //fileReader.getFolders();
    //Graphics::Model simpleModel3("/home/laelijah/Gengine/data/Models/adamHead/adamHead.gltf", resourceManager);
    //Graphics::Model simpleModel4("/home/laelijah/Gengine/data/Models/swat/scene.gltf", resourceManager);
    Graphics::Model simpleModel2("/home/laelijah/Gengine/data/Models/wolverine/scene.gltf", resourceManager);
    Graphics::Model simpleModel("/home/laelijah/Gengine/data/Models/mic/scene.gltf", resourceManager);
    GLFWwindow *window = canvas.getWindow();

     
    glEnable(GL_DEPTH_TEST);
    glfwSetCursorPosCallback(window,  mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
 
    renderer.initializeGUI(window); 
    ImGuiIO& io = ImGui::GetIO();
    while (!glfwWindowShouldClose(window)) 
    {  
      
	    
     
      currentFrame = glfwGetTime();
      deltaTime = currentFrame - lastFrame; 
      lastFrame = currentFrame;

      glm::vec3 cameraFront = camera.getDirection();
	 
      if (!io.WantCaptureKeyboard)
      {
          processInput(window);
      }


      glClearColor(0, 0, 0, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      projection = glm::perspective(glm::radians(camera.Zoom), SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f); 
      view = camera.getViewMatrix();

     
      model = glm::mat4(1.0f);
      model2 = glm::mat4(1.0f);



      simpleShader.use();
      simpleShader.setMat4("view", view);
      simpleShader.setMat4("projection", projection);


      model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
      model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));

      simpleShader.setMat4("model", model);
     
      simpleModel.Draw(simpleShader, resourceManager);






      model2 = glm::translate(model2, glm::vec3(2.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
      model2 = glm::scale(model2, glm::vec3(10.0f, 10.0f, 10.0f));

      simpleShader.setMat4("model", model2);
      


      simpleModel2.Draw(simpleShader, resourceManager);
           // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
      // -------------------------------------------------------------------------------
      glfwPollEvents();
      renderer.drawGUI();
      glfwSwapBuffers(window);
    }
    renderer.end(); 
   glfwTerminate();
    return 0;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

    ImGuiIO& io = ImGui::GetIO();
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !io.WantCaptureMouse)
    {
        canvas.captureMouse(); 
        renderer.disableGUI();	
        camera.enableCamera(); 
    }
}


void processInput(GLFWwindow *window)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        canvas.releaseMouse(); 
	renderer.enableGUI();
        camera.disableCamera(); 
    } 

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) 
        camera.resetPosition(); 

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) 
      glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
      camera.processKeyboard(Graphics::Direction::FORWARDS, deltaTime);
   
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      camera.processKeyboard(Graphics::Direction::LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)   
      camera.processKeyboard(Graphics::Direction::BACKWARDS, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      camera.processKeyboard(Graphics::Direction::RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
      camera.processKeyboard(Graphics::Direction::UP, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
      camera.processKeyboard(Graphics::Direction::DOWN, deltaTime);    
}




void mouse_callback(GLFWwindow *window, double xpos, double ypos)
    {
      
    ImGuiIO& io = ImGui::GetIO();
    
    if (!io.WantCaptureMouse)
    {
	  if (camera.isFirstMouse())
          {
            camera.setLastX(xpos);
            camera.setLastY(ypos);
            camera.startMouse(); 
          }
          
	  if (camera.getCameraStatus())
	  {
              camera.processMousePosition(xpos - camera.getLastX(), camera.getLastY() - ypos); 

              camera.setLastX(xpos);
              camera.setLastY(ypos);
	  }    

    }

    }


void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{

    ImGuiIO& io = ImGui::GetIO();
    if (!io.WantCaptureMouse)
        camera.processMouseScroll(yoffset);
}

