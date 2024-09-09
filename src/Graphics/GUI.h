#ifndef GUI_H
#define GUI_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../external/imgui/imgui.h"
#include "../../external/imgui/imgui_impl_opengl3.h"
#include "../../external/imgui/imgui_impl_glfw.h"

#include "ResourceManager.h"
#include "GLCanvas.h"
#include "FrameBuffer.h"
#include "Camera.h"
#include "GUIComponent.h"

namespace Graphics {




    class GUI 
    {
	public:
	    GUI();
            GUI(GLFWwindow* window);
        
	    void drawGUI();
            
	    void disable();
            void enable();
     
	    ImGuiIO& getIO();
     
	    void shutdown();
	    
	    bool isWindowed();
	    void toggleWindow();
	    bool isEnabled();

	    void initialize(GLFWwindow* window);
	    void addComponent(Graphics::GUIComponent*);
	    void addEditorComponent(Graphics::GUIComponent*);
            	
	private:	   
	    bool WINDOWED = false; 
	    bool GUI_ENABLED = false;
	    std::vector<Graphics::GUIComponent*> Components;
	    std::vector<Graphics::GUIComponent*> EditorComponents;


    };
}


#endif
