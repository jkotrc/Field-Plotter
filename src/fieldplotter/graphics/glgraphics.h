#ifndef GLGRAPHICS_H_
#define GLGRAPHICS_H_

#define GLEW_STATIC
#include <GL/glew.h>

#include "extern/imgui/backends/imgui_impl_glfw.h"
#include "graphics.h"
#include "shaders.h"
#include <extern/imgui/backends/imgui_impl_opengl3.h>
#include <extern/imgui/imgui.h>
#include <string>
#include <utility>

namespace fieldplotter {
constexpr float FOV = 90;
class Program {
public:
  Program(std::string const &vert_source, std::string const &frag_source);
  ~Program();
  void bind();
  GLint getUniform(std::string const &name);
  virtual void render() = 0;

protected:
  GLuint programID;
  GLuint vao;

private:
  std::string compile(GLuint id, const char *src);
};

using GLLineSegment = std::pair<glm::vec3, glm::vec3>;

class SolidPrimitives : public Program {
public:
  enum primitives {
    POINTS = 0,
    LINES,
    STRIPS,
    N_PRIMITIVES
    // TRIANGLES
    // SQUARES
    // MESHES???
  };
  SolidPrimitives();
  void addPoints(std::vector<glm::vec3> const &points);
  void addLines(std::vector<glm::vec3> const &segments);
  void addStrip(std::vector<glm::vec3> const &pieces);
  void render() override;

private:
  GLuint number_of[N_PRIMITIVES] = {0, 0, 0};
  GLuint buffer[N_PRIMITIVES];
};

class OpenGLGraphics : public Graphics {
public:
  OpenGLGraphics();
  ~OpenGLGraphics();
  void drawArrow(glm::vec3 &position, glm::vec3 &val) override;
  void drawLines(std::vector<glm::vec3> const &segments) override;
  void drawCurve(std::vector<glm::vec3> const &pieces) override;
  void drawPoint(std::vector<glm::vec3> const &pieces) override;
  void update() override;

  void setLineWidth(GLuint width) override;
  void setLineColor(glm::vec4 const &col) override;

private:
  SolidPrimitives primitives;
  glm::mat4 perspMatrix;
  glm::mat4 orthoMatrix;
};

} // namespace fieldplotter

#endif
