#include "../../include/Graphics/Mesh.h"
#include <glad/glad.h>
#include <iostream>
#include <system_error>
#include "../../include/Graphics/stb_image.h"



void loadImageDara(const char *path);

// Refractor functions to resource manager 
unsigned int generateVAO();
void assignVertexAttributes();


namespace Graphics {
 

  Graphics::Mesh::Mesh(float *verticiess, unsigned int *indicess)
    {
   
    float verticies[] = {
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);


    glGenBuffers(1, &EBO); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);







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

    loadImageDara("/home/laelijah/Programming/Gengine/extras/gate.jpg");
     


    // SECOND TEXTURE
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    
    loadImageDara("/home/laelijah/Programming/Gengine/extras/logo.jpeg");


    



 // VERTEX ATTRUBUTE SETUP
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
   
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));	// Vertex attributes stay the same
    glEnableVertexAttribArray(1);

    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(6 * sizeof(float)));	// Vertex attributes stay the same
    glEnableVertexAttribArray(2);

  
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(8 * sizeof(float)));	// Vertex attributes stay the same
    glEnableVertexAttribArray(3);



    std::cout << "TYPE: " << VAO << "     - BINDED: " << VAOs[0] << std::endl;
    VAO = VAOs[0];
    std::cout << "TYPE: " << VAO << "     - BINDED: " << VAOs[0] << std::endl;

    }



  unsigned int Graphics::Mesh::getVAO(unsigned int &vao)
  {
    std::cout << "GETTYPE: " << VAO << "     - BINDED: " << vao << std::endl; 
    vao = VAO;

    std::cout << "GETTYPE: " << VAO << "     - BINDED: " << vao << std::endl;
    return vao;
  }

  void Graphics::Mesh::setVAO(unsigned int vao)
  {
    VAO = vao;
  
  }
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
