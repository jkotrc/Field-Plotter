#ifndef VAO_H_
#define VAO_H_

#include <GL/glew.h>
#include <vector>

namespace fieldplotter {


    class VAO {
        public:
            VAO() {
                glGenVertexArrays(1, &id);
            }
            virtual ~VAO() {
                glDeleteVertexArrays(1, &id);
            }
            virtual void bind() {
                glBindVertexArray(id);
            }
        private:
            GLuint id;
    };
}

#endif // VAO_H_
