#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include "MeshTypes.h"


namespace Graphics{


    class Mesh 
    {
        public: 
            Mesh(std::vector<Graphics::Vertex> vertices, 
            std::vector<unsigned int> indices, 
            std::vector<Texture> textures);

            std::vector<Vertex>& getVertices();
            std::vector<unsigned int>& getIndices();
            std::vector<Texture>& getTextures();

	    std::string& getShaderName();
	    void setShaderName(std::string);
    
    	private:
            std::vector<Vertex> Vertices;   
            std::vector<unsigned int> Indices;
            std::vector<Texture> Textures;
            std::string ShaderName;
    };

}

#endif // !MESH_H
