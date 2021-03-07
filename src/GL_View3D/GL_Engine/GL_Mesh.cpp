#include "GL_Mesh.hpp"


void GL_Mesh::Init() {
    GETGL

    // material = GL_Material("res/GLShaders/Unlit.vert", "res/GLShaders/Unlit.frag", true);


    gl->glGenVertexArrays(1, &vertexArrayObject);
    gl->glGenBuffers(1, &vertexBuffer);
    gl->glGenBuffers(1, &elementBuffer);
    
    //Bind VAO
    gl->glBindVertexArray(vertexArrayObject);
    
    //bind buffers
    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    gl->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    //set vertex attributes
    gl->glEnableVertexAttribArray(0);
    gl->glEnableVertexAttribArray(1);
    gl->glEnableVertexAttribArray(2);
    gl->glEnableVertexAttribArray(3);
    gl->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)((uintptr_t)0));
    gl->glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)((uintptr_t)12));
    gl->glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)((uintptr_t)24));
    gl->glVertexAttribPointer(3, 4, GL_FLOAT, true, sizeof(Vertex), (void*)((uintptr_t)32));

    // //copy data to buffers
    gl->glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), (uint8_t*)&vertices[0], GL_STATIC_DRAW);
    gl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(unsigned int), (uint8_t*)&triangles[0], GL_STATIC_DRAW);

    gl->glBindBuffer(GL_ARRAY_BUFFER, 0);        //Unbind VAO
    gl->glBindVertexArray(0);
    //Unbind array and element buffers
    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);   
    
    transformChanged=true;
    inited=true;     
}


void GL_Mesh::Render(){
    if(material) {
        GETGL
        gl->glUseProgram(material->shader.programShaderObject);
        
        material->BindTexture();

        //bind VAO	
        gl->glBindVertexArray(vertexArrayObject);
        gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        gl->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        
        if (inited) {
            gl->glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT, (void*)0);
        }
        
        //unbind VAO
        gl->glBindVertexArray(0);    
        gl->glUseProgram(0);            
    }
}

void GL_Mesh::Destroy() {
    GETGL
    gl->glDeleteBuffers(1, &vertexBuffer);
    gl->glDeleteBuffers(1, &elementBuffer);
    gl->glDeleteVertexArrays(1, &vertexArrayObject);
    if(material!=nullptr){
        material.reset();
    }
}