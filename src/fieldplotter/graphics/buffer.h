#ifndef BUFFER_H_
#define BUFFER_H_

#include <GL/glew.h>
#include <util/macro.h>


/*
**
** void glBufferData( 	GLenum target,
  	GLsizeiptr size,
  	const void * data,
  	GLenum usage);

  usage:
  GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY

*/
namespace fieldplotter {

    class Buffer {
        public:
            Buffer(size_t size, GLenum type, GLenum usage);
            ~Buffer();

            void bind();

            template <typename T>
            void push(T* data, int count);

            template <typename T>
            void write(int offset, T* data, int count);

            void resize(size_t new_size);

            size_t getSize() const;
        private:
            size_t size;
            GLenum type;
            GLenum usage;

            GLuint buffer;
    };
}

#endif // BUFFER_H_
