#ifndef GLGRAPHICS_H_
#define GLGRAPHICS_H_

#define GLEW_STATIC
#include <GL/glew.h>

#include "graphics.h"
#include "shaders.h"
#include <extern/imgui/imgui.h>
#include <extern/imgui/backends/imgui_impl_opengl3.h>
#include "extern/imgui/backends/imgui_impl_glfw.h"
#include <string>
#include <utility>

namespace fieldplotter {
constexpr float FOV = 90;
class Program {
public:
  Program(std::string const &vert_source, std::string const &frag_source);
  ~Program();
  void bind();
  GLint getUniform(std::string const& name);
  virtual void render() = 0;

  protected:
  GLuint programID;
  GLuint vao;
private:
  std::string compile(GLuint id, const char *src);
};

using GLLineSegment = std::pair<glm::vec3,glm::vec3>;

class SolidPrimitives : public Program {
    public:
        enum primitives {
          POINTS=0,
          LINES,
          STRIPS,
          N_PRIMITIVES
          //TRIANGLES
          //SQUARES
          //MESHES???
      };
      SolidPrimitives();
      void addPoints(std::vector<glm::vec3> const& points);
      void addLines(std::vector<GLLineSegment> const& segments);
      void addStrip(std::vector<glm::vec3> const& pieces);
      void render() override;
    private:
    GLuint number_of[N_PRIMITIVES] = {0,0,0};
    GLuint buffer[N_PRIMITIVES];
    //GLuint number_of[N_PRIMITIVES];

};

class OpenGLGraphics : public Graphics {
public:
  OpenGLGraphics();
  ~OpenGLGraphics();
  void drawArrow(glm::vec3 &position, glm::vec3 &val) override;
  void drawLines(std::vector<GLLineSegment> const &segments) override;
  void drawCurve(std::vector<glm::vec3> const &pieces) override;
  void drawPoint(std::vector<glm::vec3> const &pieces) override;
  void update() override;

  void setLineWidth(GLuint width) override;
  void setLineColor(glm::vec4 const &col) override;

private:
  std::vector<Program> programs;
    SolidPrimitives primitives;

  // Program simpleProgram;
  glm::mat4 perspMatrix;
  glm::mat4 orthoMatrix;
  // Program meshProgram;
};

  template <typename T>
  void bufSubData(GLenum type, GLint offset, unsigned int count, T* data);

  //FIXME duplication
  template <>
  inline void bufSubData<glm::vec4>(GLenum type, GLint offset, unsigned int count, glm::vec4* data)
  {
        glBufferSubData(GL_ARRAY_BUFFER, offset*sizeof(glm::vec4), count*sizeof(glm::vec4), &data);
        glVertexAttribPointer(0, //index
                            4, //3d vector (idea: make time displacement in relativity = transparency 4d vector)
                            GL_FLOAT,
                            GL_FALSE, //no normalizing
                            0, //no stride
                            nullptr //no offset
        );
  }
  template <>
  inline void bufSubData<glm::vec3>(GLenum type, GLint offset, unsigned int count, glm::vec3* data)
  {
        glBufferSubData(GL_ARRAY_BUFFER, offset*sizeof(glm::vec3), count*sizeof(glm::vec3), &data);
        glVertexAttribPointer(0, //index
                            3, //3d vector (idea: make time displacement in relativity = transparency 4d vector)
                            GL_FLOAT,
                            GL_FALSE, //no normalizing
                            0, //no stride
                            nullptr //no offset
        );
  }

} // namespace fieldplotter

#endif // GLGRAPHICS_H_
