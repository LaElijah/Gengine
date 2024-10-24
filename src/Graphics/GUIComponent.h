#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#include <set>
#include "../../external/imgui/imgui.h"
#include "../../external/imgui/imgui_impl_opengl3.h"
#include "../../external/imgui/imgui_impl_glfw.h"
#include <functional>
#include <string>
#include "FrameBuffer.h"
// abstract class

namespace Graphics {
    class GUIComponent {
    	public: 

	    GUIComponent(std::string name);
	    std::string getName();
    		//virtual ~GUIComponent();	
    	    virtual void draw() = 0;
    	    virtual void handleInput() = 0;

        protected:
	    std::string Name; 

    };
    
    class TestWindow : public GUIComponent {
        public: 
            TestWindow(std::string name);
	    void draw();
	    void handleInput();

	
    };

    class SceneWindow : public GUIComponent {
   
	public: 
            SceneWindow( 
                std::string name,
    	        Graphics::FrameBuffer* sceneBuffer,
                std::function<void(float, float)>& resizeFunction,
		std::vector<std::function<void()>>& functionStorage);
            
            void draw();
            void handleInput();
    
        private:
            Graphics::FrameBuffer* SceneBuffer;
	    std::function<void(float, float)>& resizeWindow; 
	    std::vector<std::function<void()>>& postRenderFunctions;
    };
}

#endif
