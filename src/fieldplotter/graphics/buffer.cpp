#include "buffer.h"
#include <iostream>

using namespace fieldplotter;

Buffer::Buffer(size_t size, GLenum type, GLenum usage) : size(size), type(type), usage(usage) {
    glGenBuffers(1, &buffer);
    this->size = 0;

    if (size > 0) {
        this->bind();
        glBufferData(type, size, nullptr, usage);
        this->size = size;
    }
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &buffer);
}

void Buffer::bind() {
    glBindBuffer(type, buffer);
}


template <typename T>
void Buffer::push(T* data, int count) {
    static_assert(false);
}

template <>
void Buffer::push<float>(float* data, int count) {
    bind();
    glBufferData(type, count*sizeof(float), data, usage);
}

template <typename T>
void Buffer::write(T* offset, T* data, int count) {
    static_assert(false)
}

template <>
void Buffer::write<float>(int offset, float* data, int count) {
    bind();
    if (count*sizeof(float) + offset >= size) {
        throw "Too much data for this buffer!";
    }

    glBufferSubData(type, offset, count*sizeof(float), data);
}

void Buffer::resize(size_t new_size) {
    glBindBuffer(GL_COPY_READ_BUFFER, buffer);

    GLuint new_buf;
    glGenBuffers(1, &new_buf);
    glBindBuffer(GL_COPY_WRITE_BUFFER, new_buf);
    glBufferData(GL_COPY_WRITE_BUFFER, new_size, nullptr, usage);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, new_size);

    glDeleteBuffers(1, &buffer);
    size = new_size;
    buffer = new_buf;
}

size_t Buffer::getSize() const {return size;}
