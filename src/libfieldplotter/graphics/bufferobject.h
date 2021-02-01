#pragma once

#include "graphics.h"
#include "../computation/plottermath.h"

#include <typeinfo>
#include <stdexcept>
#include <vector>

enum VBInstancing {
    FP_INSTANCED,
    FP_SINGULAR
};


struct VectorBuffer {
    int dimension;
    size_t buffer_size;
    GLuint id;
    GLenum type;
    GLuint attrib;
    bool isInstanced;
    template<typename T>
    VectorBuffer(const VBInstancing instanced,
                GLuint attrib,int dimension) : dimension(dimension), attrib(attrib) {
        switch(typeid(T)) {
            case typeid(float):
                type=GL_FLOAT;
                break;
            case typeid(uint):
                type=GL_UNSIGNED_INT;
                break;
            default:
                throw std::runtime_error("VectorBuffer received unknown type!");
                break;
        }
        switch(instanced) {
            case FP_INSTANCED:
                isInstanced=true;
                break;
            case FP_SINGULAR:
                isInstanced=false;
                break;
            default:
                throw std::runtime_error("Enum error!");
                break;
        }
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glEnableVertexAttribArray(attrib);
        glVertexAttribPointer(attrib,dimension,type,false,0,nullptr);
        if(instanced)
            glVertexAttribDivisor(attrib,1);
    }

    template<typename T>
    VectorBuffer(const VBInstancing in,
                GLuint attrib,int dimension,T* data, int count) : VectorBuffer(in,attrib,dimension) {
        buffer_size=count*sizeof(T);
        glBufferData(id,buffer_size,data,GL_STATIC_DRAW);
    }

    ~VectorBuffer() {
        glDeleteBuffers(1,&id);
    }
    void bind() const {
        glBindBuffer(GL_ARRAY_BUFFER,id);
        glVertexAttribPointer(attrib,dimension,type,false,0,nullptr);
    }
};

class BufferObject {
    public:
        BufferObject();
        ~BufferObject();
        void bind() const;
        VectorBuffer* getBuffer(int index);
        VectorBuffer* getBufferByAttribute(int attrib);
        void addBuffer(VectorBuffer const& buf);
    private:
        std::vector<VectorBuffer> m_buffers;
};