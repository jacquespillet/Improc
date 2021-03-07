#pragma once

#include "CommonIncludes.hpp"
#include "GL_Object3D.hpp"

class GL_Scene : public GL_Object3D {
public:
    void Render() {
        for(const auto child : children) {
            child->Render();
        }
    }

    void Destroy() {
        for(int i=0; i<children.size(); i++) {
            children[i]->Destroy();
            delete children[i];
        }
        system("pause");
    }
};