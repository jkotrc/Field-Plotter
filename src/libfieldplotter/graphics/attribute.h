#pragma once

#include "graphics.h"
#include <fieldplotter_pch.h>

template <typename Type>
class VertexAttribute {
    public:
        VertexAttribute(bool instanced, int index) : m_rank(GLTypeOf<Type>::size), m_index(index), m_instanced(instanced) {
            glEnableVertexAttribArray(m_index);
            glGenBuffers(1, &m_id);
            this->bind();
        }
        ~VertexAttribute() {
            glDeleteBuffers(1, &m_id);
        }
        void bind() {
            glBindBuffer(GL_ARRAY_BUFFER, m_id);
            glVertexAttribPointer(m_index, m_rank, GLTypeOf<Type>::type, false, 0, nullptr);
            if(m_instanced) {
                glVertexAttribDivisor(m_index,1);
            }
        }
        void setData(std::vector<Type> data) {
            this->bind();
            m_size = data.size()*sizeof(Type);
            glBufferData(GL_ARRAY_BUFFER, m_size, &data[0],GL_STATIC_DRAW);
        }
        GLuint getIndex() { return m_id; }
        int getRank() { return m_rank; }
    private:
        GLuint m_id;
        size_t m_size;
        bool m_instanced;
        int m_rank;
        int m_index;
};