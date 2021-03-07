#pragma once

#include "CommonIncludes.hpp"
class GL_Object3D {
public:
    GL_Object3D();
    GL_Object3D(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
    void Translate(glm::vec3 dPos);
    void Rotate(glm::vec3 dRot);
    void Scale(glm::vec3 dScale);

    void SetPos(glm::vec3 pos);
    void SetRot(glm::vec3 rot);
    void SetScale(glm::vec3 scale);

    virtual void Render(){}

    glm::mat4 modelMatrix;
    glm::mat4 invModelMatrix;

    GL_Object3D *GetAt(int inx) {
        return children[inx];
    }

    void Add(GL_Object3D *child) {
        child->SetParent(this);
        children.push_back(child);
    }
    void Add(std::vector<GL_Object3D *> children);
    
    void SetParent(GL_Object3D *parent) {this->parent = parent;}

    virtual void Destroy() {

    }

protected:
    std::vector<GL_Object3D*> children;
    GL_Object3D *parent;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    bool transformChanged;

    void RecalculateMatrices();
};