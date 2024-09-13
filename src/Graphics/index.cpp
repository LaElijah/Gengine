#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../external/imgui/imgui.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "GLCanvas.h"
#include "Renderer.h"

void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);  
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

Graphics::Renderer renderer;
Graphics::ResourceManager* ResourceManager = renderer.getResourceManager();
Graphics::Camera* Camera = renderer.getCamera();
Graphics::GLCanvas* Canvas = renderer.getCanvas();    
Graphics::GUI* GUI = renderer.getGUI();


int main()
{
    GLFWwindow* window = Canvas->getWindow();  

    glfwSetCursorPosCallback(window,  mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback); 

    GUI->initialize(window);
    ResourceManager->initialize(); 
    
    renderer.run();
    return 0;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    ImGuiIO& io = GUI->getIO();

    // If not fullscreen, drag and orient function
    // TODO: FIX error by specifiying the scene content window is focused?
    // else do nothing 
    //ImGuiWindow* currentWindow = ImGui::GetCurrentWindow();
 
   // TODO: Fix scene selection bug maybe by 
   // getting content region of scene window
   // but what if theres things on top of it? 
   // maybe i should see what the currently selected window
   // is?  
    if (GUI->isWindowed() 
		    && button == GLFW_MOUSE_BUTTON_LEFT 
		    && action == GLFW_PRESS 
		    && io.WantCaptureMouse)
    {
	Canvas->captureMouse(); 
        GUI->disable();	
        Camera->enableCamera();
    }

    // If fullscreen, move like camera follow mouse
   
    else if (!GUI->isWindowed() 
		    && !io.WantCaptureMouse
		    && button == GLFW_MOUSE_BUTTON_LEFT 
		    && action == GLFW_PRESS)
    {
        Canvas->captureMouse(); 
        GUI->disable();	
        Camera->enableCamera();

    } 

}



void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{     
    if (Camera->isFirstMouse())
    {
        Canvas->setLastX(xpos);
        Canvas->setLastY(ypos);
  	
	Camera->startMouse(); 
   
    }
      
    if (Camera->getCameraStatus())
    {
          Camera->processMousePosition(xpos - Canvas->getLastX(), Canvas->getLastY() - ypos); 
          Canvas->setLastX(xpos);
          Canvas->setLastY(ypos);
    }
    else 
    {
        glfwSetCursorPos(Canvas->getWindow(), Canvas->getLastX(), Canvas->getLastY()); 
    }    
}


void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    Camera->processMouseScroll(yoffset);
}



