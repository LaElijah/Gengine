#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../include/Graphics/GLCanvas.h"
#include "../../include/Graphics/Shader.h"
#include <math.h>
#include "../../include/Graphics/Mesh.h"
#include "../../include/Graphics/Renderer.h"
#include "../../include/Graphics/stb_image.h"
// settings

  void loadImageDara(const char* path);


int main()
{
    Graphics::GLCanvas canvas;    
    canvas.initializeCanvas();
    GLFWwindow *window = canvas.getWindow();

   
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

// ENDDDDDD

    Graphics::Mesh rectangle(Rectangle, sizeof(Rectangle), indices, sizeof(indices));
    Graphics::Shader shaderProgram(
        "/home/laelijah/Programming/Gengine/extras/vertex.vs",
        "/home/laelijah/Programming/Gengine/extras/fragment.fs"
    );

    Graphics::Renderer renderer;


 //   unsigned int VAO;
//std::cout << "CURRENTTYPE: " << VAO << std::endl;


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



  void loadImageDara(const char* path)
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);


    if (data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); 
      glGenerateMipmap(GL_TEXTURE_2D);
    }

    else 
    {
      std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
    
}
