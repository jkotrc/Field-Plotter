#pragma once

#include "graphics.h"
#include "buffers.h"
#include <fieldplotter_pch.h>
#include <map>

class VertexAttribute {
    public:
        VertexAttribute(){}
        template<typename T>
        static VertexAttribute create(int index, size_t offset, size_t stride, bool instanced=false) {
            return {index, instanced, GLTypeOf<T>::type, GLTypeOf<T>::size,offset,stride};
        }
        void makePointer() {
            glEnableVertexAttribArray(m_id);
            glVertexAttribPointer(m_id, m_rank, m_type, false, m_stride,(void*)m_offset);
            if (m_instanced) {
                glVertexAttribDivisor(m_id, 1);
            }
        }
        GLuint getIndex() const { return m_id; }
        int getRank() const { return m_rank; }
    private:
        VertexAttribute(int index, bool instanced, GLenum type, int rank, size_t offset, size_t stride) : m_id(index), m_instanced(instanced), m_type(type), m_rank(rank), m_offset(offset), m_stride(stride) {
            
        }
        int m_id;
        bool m_instanced;
        GLenum m_type;
        int m_rank;
        size_t m_offset;
        size_t m_stride;
};


//Vertex Array: add or remove vertex attributes.
//Vertex Attribute: (size,type), index, offset
//template<typename Type> add(size_t offset)

class VertexArray {
    public:
        VertexArray() {
            glGenVertexArrays(1, &m_vao);
        }
        ~VertexArray() {
            glDeleteVertexArrays(1, &m_vao);
        }
        void bind() {
            glBindVertexArray(m_vao);
        }
        void addAttribute(VertexAttribute const& attribute) {
            bind();
            m_attributes[attribute.getIndex()] = attribute;
            //m_attributes.push_back(attribute);
        }
    private:
        GLuint m_vao;
        std::map<int, VertexAttribute> m_attributes;
        //std::vector<VertexAttribute> m_attributes;
};