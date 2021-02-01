#include "bufferobject.h"


BufferObject::BufferObject() {}
BufferObject::~BufferObject() {}

void BufferObject::bind() const {
    for(const auto& buf : m_buffers) {
        //buf.bind();
    }
}
VectorBuffer* BufferObject::getBuffer(int index) {
    return &m_buffers[index];
}
VectorBuffer* BufferObject::getBufferByAttribute(int attrib) {
    for(auto& buf : m_buffers) {
        if (buf.attrib == attrib) {
            return &buf;
        }
    }
    throw std::runtime_error("No buffer with the given attribute found!");
    return nullptr;
}
void BufferObject::addBuffer(VectorBuffer const& buf) {
    m_buffers.push_back(buf);
}