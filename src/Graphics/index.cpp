#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../include/Graphics/GLCanvas.h"
#include "../../include/Graphics/Shader.h"
#include <math.h>
#include "../../include/Graphics/Mesh.h"
#include "../../include/Graphics/Renderer.h"
#include "../../include/Graphics/stb_image.h"
#include <assimp/Importer.hpp>





    float Rectangle[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,  // top left 
    };

    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    float visibility = 0.5f;



int main()
{
    Graphics::GLCanvas canvas;    
    canvas.initializeCanvas();
    GLFWwindow *window = canvas.getWindow();


    Graphics::Mesh rectangle(Rectangle, sizeof(Rectangle), indices, sizeof(indices));
    Graphics::Shader shaderProgram(
        "/home/laelijah/Programming/Gengine/extras/vertex.vs",
        "/home/laelijah/Programming/Gengine/extras/fragment.fs"
    );

    Graphics::Renderer renderer;

    // Rendering in window 
    while (!glfwWindowShouldClose(window)) 
    {
      Graphics::processInput(window, visibility);
      
      renderer.draw(shaderProgram, visibility, rectangle.getVAO(), window);
    }


    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    // glDeleteVertexArrays(1, &VAOs[0]);
    //glDeleteBuffers(1, &VBOs[0]);
    // glDeleteBuffers(1, &EBO);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}



