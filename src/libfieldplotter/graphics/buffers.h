#pragma once
#include "graphics.h"
#include <fieldplotter_pch.h>
#include <stdexcept>

template <GLenum type>
class Buffer {
	public:
		Buffer(GLenum mode) : m_mode(mode) {
			glGenBuffers(1, &m_ID);
		}
		Buffer() : Buffer(GL_STATIC_DRAW)  {		}
		~Buffer() {
			glDeleteBuffers(1, &m_ID);
		}
		void resize(size_t new_size) {
			bind();
			glBufferData(type, new_size, nullptr, m_mode);
			m_allocatedSize = new_size;
		}
		template<typename T>
		void setData(T* data, int count, size_t offset = 0) {
			bind();
			const size_t size = count * sizeof(T);
			if (size+offset > m_allocatedSize) {
				expandBuffer(1.5 * size);
			}
			glBufferSubData(type, offset, size, data);
		}
		template<typename T>
		void setAndAllocateData(T* data, int count, size_t offset=0) {
			bind();

			glBufferData(type, count*sizeof(T), data, m_mode);
			m_allocatedSize = count*sizeof(T);
		}
		void bind() {
			glBindBuffer(type, m_ID);
		}
		void unbind() {
			glBindBuffer(type, 0);
		}
	private:
		GLuint m_ID;
		GLenum m_mode;
		size_t m_allocatedSize = 0;
		void expandBuffer(size_t new_size) {
			if (new_size < m_allocatedSize) { return; }
			GLuint bigger_buffer;
			glGenBuffers(1, &bigger_buffer);
			glBindBuffer(GL_COPY_READ_BUFFER, m_ID);
			glBindBuffer(GL_COPY_WRITE_BUFFER, bigger_buffer);
			glBufferData(GL_COPY_WRITE_BUFFER, new_size, nullptr, m_mode);
			glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, m_allocatedSize);
			m_allocatedSize = new_size;
			glBindBuffer(GL_COPY_READ_BUFFER, 0);
			glDeleteBuffers(1, &m_ID);
			m_ID = bigger_buffer;
		}
};

using VertexBuffer = Buffer<GL_ARRAY_BUFFER>;
using IndexBuffer = Buffer<GL_ELEMENT_ARRAY_BUFFER>;