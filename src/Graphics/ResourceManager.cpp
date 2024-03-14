#include "../../include/Graphics/ResourceManager.h"
#include <unordered_map>
#include <memory>
#include <iostream>


// Make an absract class that can be overridden with derived classes like
// textures, VBOs and VAOs
// VAOs will most likelwy have only one in its map
// but i should probably let them all contain an ordered map 
class Resource
{
  public:
  Resource();
  ~Resource();

  virtual void loadResource() = 0;
  virtual void unloadResource() = 0;
  virtual void reloadResource() = 0;
};


class Texture : public Resource
{
  public:
  unsigned int textureId;
  Texture()
  {

  }

  ~Texture()
  {

  }

  void loadResource() 
  {

  }
  void unloadResource()
  {

  }
  void reloadResource()
  {

  }

};



class VAO : public Resource
{
  public:
  unsigned ID;
  VAO()
  {

  }

  ~VAO()
  {

  }

  void loadResource() 
  {
    std::cout << "h" << std::endl;
  }
  void unloadResource()
  {

  }
  void reloadResource()
  {

  }

};



class ResourceManager 
{
  public:
  std::unordered_map<std::string, std::shared_ptr<Resource>> cache;

};



int main()
{

  Resource *bptr;
  Texture texture{};
  VAO vao{};

  bptr = &texture;

  bptr->loadResource();

  bptr = &vao;

  bptr->loadResource();
 
  ResourceManager resourceManager;

  resourceManager.cache.insert({"h", std::make_shared<Resource>(bptr)});
}

namespace Graphics {


  
}
