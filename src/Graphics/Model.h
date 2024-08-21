#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <vector> 


namespace Graphics {

  class Model 
  {
    public:
      Model(std::string path, Graphics::ResourceManager* resourceManager);

      void Draw(Graphics::Shader& shader);
      glm::mat4 getModelMatrix();


      private:
      glm::vec3 Position = glm::vec3(0.0f, 0.0f, 1.0f);
      glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);
      Graphics::ResourceManager* resourceManager;
      
      std::vector<Graphics::Mesh> meshes;
      std::vector<Graphics::Texture> texturesLoaded;
      std::string directory;

      void loadModel(std::string path);

      void processNode(aiNode *node, const aiScene *scene, const glm::mat4& parentTransform);
      Graphics::Mesh processMesh(aiMesh *mesh, const aiScene *scene, const glm::mat4& transform);

      std::vector<Graphics::Texture> loadMaterialTextures(aiMaterial *mat, const aiScene* scene, aiTextureType type, std::string typeName);

      unsigned int TextureFromFile(std::string path, std::string directory);
  
      unsigned int TextureFromEmbedded(const aiScene* scene, int embeddedIndex);

  };
}

#endif