
#include "Renderer.h"



#include "../../external/imgui/imgui.h"
#include "../../external/imgui/imgui_impl_opengl3.h"
#include "../../external/imgui/imgui_impl_glfw.h"

void Graphics::Renderer::initializeGUI(GLFWwindow* window)
{
IMGUI_CHECKVERSION();
    ImGui::CreateContext();

   
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(); 
   
}


Graphics::Renderer::Renderer()
{}


void Graphics::Renderer::drawGUI()
{
    
      if (GUI_ENABLED)
      { 
          ImGui_ImplOpenGL3_NewFrame();
          ImGui_ImplGlfw_NewFrame();
          ImGui::NewFrame();
          ImGui::ShowDemoWindow();

          ImGui::Render();
          ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      } 

}

void Graphics::Renderer::end()
{
   ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  
}

void Graphics::Renderer::enableGUI()
{
    GUI_ENABLED = true;
}


void Graphics::Renderer::disableGUI()
{
    GUI_ENABLED = false;
}
