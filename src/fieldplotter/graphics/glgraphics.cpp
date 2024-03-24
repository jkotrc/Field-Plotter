#include "glgraphics.h"
#include "glm/ext/matrix_transform.hpp"
#include "graphics/shaders.h"

//idea: build program from class template based on suitable elementary vertex and fragment shaders
#include <sstream>
#include <iterator>
#include <iostream>
#include <stdio.h>
using namespace fieldplotter;

void glError_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::cout << "[GL Error, severity " << severity << "] " << message << "\n";
}

OpenGLGraphics::OpenGLGraphics() {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_LINE_SMOOTH);
    glPointSize(3.0f);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    //TODO must regenerate based on screen dimensions
    perspMatrix = glm::perspective(
        glm::radians(FOV), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
        4.0f / 3.0f,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar?
        0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
        100.0f             // Far clipping plane. Keep as little as possible.
    );
    orthoMatrix = glm::ortho(-(800.0f / 2.0f), 800.0f / 2.0f,
        600.0f / 2.0f, -(600.0f / 2.0f),
      -1000.0f, 1000.0f);
}

OpenGLGraphics::~OpenGLGraphics() {

}

void OpenGLGraphics::drawArrow(glm::vec3 &position, glm::vec3 &val) {

}

void OpenGLGraphics::drawLines(std::vector<glm::vec3> const &segments) {
    if (segments.size() <= 1) return;
    primitives.addLines(segments);
}

void OpenGLGraphics::drawCurve(std::vector<glm::vec3> const &pieces) {
    primitives.addStrip(pieces);
}

void OpenGLGraphics::drawPoint(std::vector<glm::vec3> const &pieces) {
    primitives.addPoints(pieces);
}
float tmpval = 0.0f;
void OpenGLGraphics::update() {
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 vp = perspMatrix * camera.getViewMatrix();
    glUniformMatrix4fv(primitives.getUniform("VP"), 1, false, glm::value_ptr(vp));
    primitives.render();
    tmpval += 0.01f;
}

void OpenGLGraphics::setLineWidth(GLuint width) {

}
void OpenGLGraphics::setLineColor(glm::vec4 const &col) {

}

//TODO set to void
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

Program::Program(std::string const& vert_source, std::string const& frag_source) {
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
    glGenVertexArrays(1, &vao);

}

Program::~Program() {
    glDeleteVertexArrays(1, &vao);

}

void Program::bind() {
    glBindVertexArray(vao);
    glUseProgram(programID);
}

GLint Program::getUniform(std::string const& name) {
    return glGetUniformLocation(programID, name.c_str());
}
SolidPrimitives::SolidPrimitives() : Program(shaders::VERT_SIMPLE, shaders::FRAG_SOLID) {
    glGenBuffers(N_PRIMITIVES,buffer);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    for (GLuint buf : buffer) {
        printf("Initializing buffer %u\n", buf);
        glBindBuffer(GL_ARRAY_BUFFER, buf);
        glBufferData(GL_ARRAY_BUFFER, 50*sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW); //FIXME 50 max number of elements
        glVertexAttribPointer(0, //index
                            3, //3d vector (idea: make time displacement in relativity = transparency 4d vector)
                            GL_FLOAT,
                            GL_FALSE, //no normalizing
                            0, //no stride
                            nullptr //no offset
        );
    }
}

void SolidPrimitives::addPoints(std::vector<glm::vec3> const& points) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer[POINTS]);
    printf("subdata: offset %lu, size %lu, first point %f %f %f\n",number_of[POINTS]*sizeof(glm::vec3), points.size()*sizeof(glm::vec3), points[0][0], points[0][1], points[0][2]);
    glBufferSubData(GL_ARRAY_BUFFER, number_of[POINTS]*sizeof(glm::vec3), points.size()*sizeof(glm::vec3), points.data());
     number_of[POINTS]+=points.size();
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
void SolidPrimitives::addLines(std::vector<glm::vec3> const& segments) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer[LINES]);
    glBufferSubData(GL_ARRAY_BUFFER, number_of[LINES]*sizeof(glm::vec3), segments.size()*sizeof(glm::vec3), segments.data());
    number_of[LINES]+=segments.size();
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
void SolidPrimitives::addStrip(std::vector<glm::vec3> const& pieces) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer[STRIPS]);
    glBufferSubData(GL_ARRAY_BUFFER, number_of[STRIPS]*sizeof(glm::vec3), pieces.size()*sizeof(glm::vec3), pieces.data());
    number_of[STRIPS]+=pieces.size();
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
void SolidPrimitives::render() {
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, buffer[POINTS]);
        glVertexAttribPointer(0, //index
                            3, //3d vector (idea: make time displacement in relativity = transparency 4d vector)
                            GL_FLOAT,
                            GL_FALSE, //no normalizing
                            0, //no stride
                            nullptr //no offset
        );
    glDrawArrays(GL_POINTS, 0, number_of[POINTS]);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[LINES]);
        glVertexAttribPointer(0, //index
                            3, //3d vector (idea: make time displacement in relativity = transparency 4d vector)
                            GL_FLOAT,
                            GL_FALSE, //no normalizing
                            0, //no stride
                            nullptr //no offset
        );
    glDrawArrays(GL_LINES, 0, number_of[LINES]);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[STRIPS]);
        glVertexAttribPointer(0, //index
                            3, //3d vector (idea: make time displacement in relativity = transparency 4d vector)
                            GL_FLOAT,
                            GL_FALSE, //no normalizing
                            0, //no stride
                            nullptr //no offset
        );
    glDrawArrays(GL_LINE_STRIP, 0, number_of[STRIPS]);
}
