#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../include/Graphics/GLCanvas.h"
#include "../../include/Graphics/Shader.h"
#include <glm/ext/matrix_transform.hpp>
#include <math.h>
#include "../../include/Graphics/stb_image.h"
#include "../../include/Graphics/Mesh.h"
#include "../../include/Graphics/Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "./Camera.cpp"

// settings

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

    float fov = 45.0f;


void loadImageData(const char *path);



     void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);    

    Graphics::Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT);


int main()
{
    Graphics::GLCanvas canvas;    
    canvas.initializeCanvas();
    GLFWwindow *window = canvas.getWindow();
 
    
      glfwSetCursorPosCallback(window,  mouse_callback);
      glfwSetScrollCallback(window, scroll_callback);


   float Triangle[] = {
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


    float vertices[] = {
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

    float visibility = 0.5f;


    glm::vec3 cubePositions[] = {
      glm::vec3( 0.0f, 0.0f, 0.0f),
glm::vec3( 2.0f, 5.0f, -15.0f),
glm::vec3(-1.5f, -2.2f, -2.5f),
glm::vec3(-3.8f, -2.0f, -12.3f),
glm::vec3( 2.4f, -0.4f, -3.5f),
glm::vec3(-1.7f, 3.0f, -7.5f),
glm::vec3( 1.3f, -2.0f, -2.5f),
glm::vec3( 1.5f, 2.0f, -2.5f),
glm::vec3( 1.5f, 0.2f, -1.5f),
glm::vec3(-1.3f, 1.0f, -1.5f)

    };








    // START
    // Graphics::Mesh Rectangle(Triangle, indices);

     // render
        // ------

        



    // ASSIGNMENT ORDER 
    // GENERATE VERTEX ARRAY 
    // BIND IT 
    // SET VERTEX BUFFER OBJECT 
    // BIND BUFFER DATA 
    // IF APPLICABLE DO THE SAME FOR ELEMENT BUFFER OBJECT
    // APPLY TEXTURES
    //
    // APPLY VERTEX ATTRIBUTES AFTER ALL DATA IS FIRST MOUNTED 

    unsigned int VBOs[1], VAOs[1], EBO, textures[2];
   

    glGenVertexArrays(1, &VAOs[0]); // we can also generate multiple VAOs or buffers at the same time

    // first triangle setup
    // --------------------
 


    glBindVertexArray(VAOs[0]);


    glGenBuffers(1, &VBOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //glGenBuffers(1, &EBO); 
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);







    glGenTextures(2, textures); 

    // TEXTURE APPLICATIONS
    //
    //
    // FIRST TEXTURE
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
 
    float borderColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);   

    loadImageData("/home/laelijah/Programming/Gengine/extras/gate.jpg");
    


    // SECOND TEXTURE
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    
    loadImageData("/home/laelijah/Programming/Gengine/extras/logo.jpeg");


    

  



    // VERTEX ATTRUBUTE SETUP
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
   
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));	// Vertex attributes stay the same
    //glEnableVertexAttribArray(1);

    
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(6 * sizeof(float)));	// Vertex attributes stay the same
    //glEnableVertexAttribArray(2);

  
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));	// Vertex attributes stay the same
    glEnableVertexAttribArray(1);



 










// ENDDDDDD


    glm::mat4 model = glm::mat4(1.0f);


    glm::mat4 view = glm::mat4(1.0f);
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));



    glm::mat4 projection = glm::mat4(1.0f);

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);




    Graphics::Shader shaderProgram(
        "/home/laelijah/Programming/Gengine/extras/vertex.vs",
        "/home/laelijah/Programming/Gengine/extras/fragment.fs"
    );


    Graphics::Renderer renderer;
    glEnable(GL_DEPTH_TEST);


      // Rendering in window 
    while (!glfwWindowShouldClose(window)) 
    {

    projection = glm::perspective(glm::radians(fov), 800.f / 600.0f, 0.1f, 100.0f);

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  float currentFrame = glfwGetTime();
  deltaTime = currentFrame = lastFrame;
  lastFrame = currentFrame;
    


    glm::vec3 cameraFront = camera.getDirection();
      Graphics::processInput(window, 
          visibility, cameraPos, cameraFront, cameraUp, deltaTime);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      

     
    unsigned int modelLocation = glGetUniformLocation(shaderProgram.ID, "model");
   
    unsigned int viewLocation = glGetUniformLocation(shaderProgram.ID, "view");
    unsigned int projectionLocation = glGetUniformLocation(shaderProgram.ID, "projection");
    

    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
   

    shaderProgram.use();
     shaderProgram.setInt("texture1", 0);
    shaderProgram.setInt("texture2", 1);
    shaderProgram.setFloat("visibility", visibility);
 


    glBindVertexArray(VAOs[0]);

for(unsigned int i = 0; i < 10; i++)
{
  glm::mat4 model = glm::mat4(1.0f);

  
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    model = glm::translate(model, cubePositions[i]);


    if (i != 2 && i != 5 && i != 8)
    {
    float angle = 20.0f * i;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    }
    else 
    {
      model = glm::rotate(model, ((float) glfwGetTime()) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    }

    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model)); 

    glDrawArrays(GL_TRIANGLES, 0, 36);
}




   


// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
// -------------------------------------------------------------------------------
glfwSwapBuffers(window);
glfwPollEvents();
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

void loadImageData(const char* path)
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


void mouse_callback(GLFWwindow *window, double xpos, double ypos)
    {

      std::cout << "XPOS::" << xpos << "::  YPOS::" << ypos << std::endl;

      if (camera.isFirstMouse())
      {
        std::cout << "FIRSTMOUSE" << std::endl;
        camera.setLastX(xpos);
        camera.setLastY(ypos);
        camera.startMouse(); 
      }

      camera.processMousePosition(xpos, ypos); 
      camera.updateDirection();     
    }
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
  fov -= (float) yoffset;
  if (fov < 1.0f)
    fov = 1.0f;
  if (fov > 45.0f)
    fov = 45.0f;

}


