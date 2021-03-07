#include "GL_Util.hpp"

GL_Mesh *GetQuad() {
    std::vector<GL_Mesh::Vertex> vertices(4);
    std::vector<unsigned int> triangles(6);
    vertices[0] = {
        glm::vec3(-1.0, -1.0, 0),
        glm::vec3(0.0, 0.0, 1.0),
        glm::vec2(0.0,0.0),
        glm::vec4(1.0, 0.0, 0.0, 0.0)
    };
    vertices[1] = {
        glm::vec3(-1.0, 1.0, 0),
        glm::vec3(0.0, 0.0, 1.0),
        glm::vec2(0.0, 1.0),  
        glm::vec4(1.0, 0.0, 0.0, 0.0)
    };
    vertices[2] = {
        glm::vec3(1.0, 1.0, 0),
        glm::vec3(0.0, 0.0, 1.0),
        glm::vec2(1.0, 1.0),
        glm::vec4(1.0, 0.0, 0.0, 0.0)
    };
    vertices[3] = {
        glm::vec3(1.0, -1.0, 0),
        glm::vec3(0.0, 0.0, 1.0),
        glm::vec2(1.0, 0.0),
        glm::vec4(1.0, 0.0, 0.0, 0.0)
    };

    triangles[0] = 0;
    triangles[1] = 2;
    triangles[2] = 1;
    triangles[3] = 3;
    triangles[4] = 2;
    triangles[5] = 0;

    GL_Mesh *mesh = new GL_Mesh(vertices, triangles, true);
    GL_Material *gl_material = new GL_Material("res/GLShaders/RenderQuad.vert", "res/GLShaders/RenderQuad.frag", true);
    mesh->material = std::shared_ptr<GL_Material>(gl_material);

    return mesh;
}