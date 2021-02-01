#pragma once

#include "graphics.h"
#include <istream>
#include <string>

class Shader {
    public:
        Shader(istream const& inputstream);
        Shader(std::string const& inputstr);
        GLuint getID();
        GLuint getUniformBlockIndex(std::string name);
        GLuint getUniformIndex(std::string name);
        ~Shader();
    private:
        GLuint m_id;
};