#include "GL_Object3D.hpp"

GL_Object3D::GL_Object3D() : position(glm::vec3(0)), rotation(glm::vec3(0)), scale(glm::vec3(1)), modelMatrix(glm::mat4(1)), invModelMatrix(glm::inverse(modelMatrix)){}
GL_Object3D::GL_Object3D(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) : position(pos), rotation(rot), scale(scale){
    RecalculateMatrices();
}

void GL_Object3D::Translate(glm::vec3 dPos) {
    position += dPos;
    RecalculateMatrices();
}

void GL_Object3D::Rotate(glm::vec3 dRot) {
    rotation += dRot;
    RecalculateMatrices();
}

void GL_Object3D::Scale(glm::vec3 dScale) {
    scale += dScale;
    RecalculateMatrices();
}


void GL_Object3D::SetPos(glm::vec3 pos) {
    position = pos;
    RecalculateMatrices();
}

void GL_Object3D::SetRot(glm::vec3 rot) {
    rotation = rot;
    RecalculateMatrices();
}

void GL_Object3D::SetScale(glm::vec3 scale) {
    scale = scale;
    RecalculateMatrices();
}

void GL_Object3D::RecalculateMatrices() {
    glm::mat4 t=  glm::translate(glm::mat4(1.0), position);

    glm::mat4 rx=  glm::rotate(glm::mat4(1.0), glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 ry=  glm::rotate(glm::mat4(1.0), glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 rz=  glm::rotate(glm::mat4(1.0), glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 r = rz * ry * rx;

    glm::mat4 s = glm::scale(glm::mat4(1.0), scale);

    modelMatrix = t * s * r;
    invModelMatrix = glm::inverse(modelMatrix);
    
    transformChanged=true;
}