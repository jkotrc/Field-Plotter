#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <GL/glew.h>
#include <string>

namespace fieldplotter {
    class Program {
        public:
            Program(std::string vert_source, std::string frag_source);
            void bind();
        private:
            std::string compile(GLuint id, const char* src);
            GLuint programID;
    };
}


#endif // PROGRAM_H_
