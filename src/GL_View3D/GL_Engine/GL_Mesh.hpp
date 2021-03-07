#pragma once
#include "CommonIncludes.hpp"

#include "GL_Object3D.hpp"
#include "GL_Material.hpp"

class GL_Mesh : public GL_Object3D {
public:
    GL_Mesh(){}
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
        glm::vec4 tan;
    }; 

    GL_Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> triangles, bool shouldInit=false) : vertices(vertices), triangles(triangles), inited(false) {
        if(shouldInit) Init();
    }

    void Render();

    void Init();
    void Destroy();
    std::shared_ptr<GL_Material> material;
    
    bool inited;

private:
    //CPU buffers
    std::vector<Vertex> vertices;
    std::vector<unsigned int> triangles;
    
    //GPU buffers
    unsigned int vertexBuffer;
    unsigned int elementBuffer;
    unsigned int vertexArrayObject;
};