#include "program.h"

using namespace fieldplotter;
#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>

std::string Program::compile(GLuint id, const char* src) {
    GLint result = GL_FALSE;
    int log_length = 0;
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);

    if ( log_length > 0 ){
        std::vector<char> errormsg(log_length+1);
        glGetShaderInfoLog(id, log_length, NULL, &errormsg[0]);
        std::ostringstream ss;
        ss << "Error Compiling shader. Status: " << result << "\n";
        for (char c : errormsg) {
            ss << c;
        }
        return ss.str();
    }
    return "";

}

Program::Program(std::string vert_source, std::string frag_source) {
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    const char* src = vert_source.c_str();
    std::string result;
    int log_length;
    GLint status = GL_FALSE;

    result = compile(vert, src);
    if (result.length() > 0) {
        std::cout << result << "\n";
    }
    src = frag_source.c_str();
    result = compile(frag, src);
    if (result.length() > 0) {
        std::cout << result << "\n";
    }

    programID = glCreateProgram();
    glAttachShader(programID, vert);
    glAttachShader(programID, frag);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &status);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &log_length);

    if ( log_length > 0 ){
        std::vector<char> errormsg(log_length+1);
        glGetShaderInfoLog(programID, log_length, NULL, &errormsg[0]);
        std::ostringstream ss;
        ss << "Error Linking shader. Status: " << status << "\n";
        for (char c : errormsg) {
            ss << c;
        }
        ss << "\n";
        std::cout << ss.str();
    }
    glDetachShader(programID, vert);
    glDetachShader(programID, frag);
    glDeleteShader(vert);
    glDeleteShader(frag);
}

void Program::bind() {
    glUseProgram(programID);
}
