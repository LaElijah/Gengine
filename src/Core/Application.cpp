#include "../Graphics/Camera.h"
#include "../Graphics/ResourceManager.h"
#include "../Graphics/GLFWCanvas.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/RenderAPI.h"
#include "Application.h"




void Core::GLFWApplication::startImpl()
{
    Graphics::OpenGLRenderAPI api = Graphics::OpenGLRenderAPI(); 
    std::shared_ptr<Graphics::Camera> Camera = std::shared_ptr<Graphics::Camera>(new Graphics::Camera(1920, 1080));
    std::shared_ptr<Graphics::GUI> GUI = std::shared_ptr<Graphics::GUI>(new Graphics::GUI());
    std::shared_ptr<Graphics::GLFWCanvas> Canvas = std::shared_ptr<Graphics::GLFWCanvas>(
		new Graphics::GLFWCanvas
		            (
				std::make_pair(1920, 1080),
				Camera, 
				GUI
		            )
		);

    // Starts renderer on construction
    Graphics::Renderer renderer = Graphics::Renderer(
		                Canvas,
		                Camera,
		                GUI,
			        std::shared_ptr<Graphics::ResourceManager>(new Graphics::ResourceManager()),
				api
		);
}
