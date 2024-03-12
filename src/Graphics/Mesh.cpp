#include "../../include/Graphics/Mesh.h"
#include <glad/glad.h>
#include <iostream>
#include <system_error>
#include "../../include/Graphics/stb_image.h"



void loadImageData(const char *path);

// Refractor functions to resource manager 
unsigned int generateVAO();
void assignVertexAttributes();


namespace Graphics {
 

  Graphics::Mesh::Mesh(float verticies[], int dataSize, unsigned int indices[], int indexSize)
    {

    loadVAO();
    unsigned int VBOs[1], EBO; 
   

    glGenBuffers(1, &VBOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, dataSize, verticies, GL_STATIC_DRAW);


    glGenBuffers(1, &EBO); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);


    loadTextures();

    // TODO: Create a modular version of this to assign specifically defined attributes for a given VAO
    assignVertexAttributes();
    
  }




  // A temporary solution, should request texture loading from resource manager 
  // TODO: Update this to work with a single texture at a time 
  void Graphics::Mesh::loadTextures()
  {
    unsigned int textures[2];
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
  }



  // A temporary solution that does not include resource manager ability to correctly assign VAO for vertex format
  void Graphics::Mesh::loadVAO()
  { 
    // TODO: Replace this with Resource manager implementation  
    VAO = generateVAO();
  }

  // VAO Getter
  unsigned int Graphics::Mesh::getVAO()
  {
    return VAO;
  }

  void Graphics::Mesh::setVAO(unsigned int vao)
  {
    VAO = vao;
  }


}


unsigned int generateVAO()
{
  unsigned int vao;
 

  bool exists = false;
  // Incomplete if statement, meant to be apart of greater resource manager for vaos
  if (!exists)
  {
    std::cout << "Generating and binding VBO" << std::endl;
    // Generating a NEW vertex array object 
    glGenVertexArrays(1, &vao); 
    glBindVertexArray(vao);

    std::cout << vao << std::endl;
    return vao;
  }
  else 
  {
    return vao;
  }
}


// Modularize this back into the generateVAO function 
void assignVertexAttributes()
{
    // VERTEX ATTRUBUTE SETUP
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);	
    glEnableVertexAttribArray(0);
   
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));	
    glEnableVertexAttribArray(1);

    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

  
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

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
