#ifndef MESH_H
#define MESH_H




namespace Graphics {
  class Mesh {
    unsigned int VBO;
    unsigned int EBO;
    unsigned int VAO;
    unsigned int Textures[2];

    const char *Name;


    public: 
    Mesh(float verticies[], int dataSize, unsigned int *indices, int indexSize);
    unsigned int getVAO();
    
    void setVAO(unsigned int vao);
 
    private:
    void loadVBO(float *verticies);
    void loadEBO(unsigned int *indices);    
    void loadTexture(unsigned int activeTexture, unsigned int texture, const char *path);
    void loadTextures();

    void loadVAO();
    void loadVertexAttributes();
  };
}





#endif
