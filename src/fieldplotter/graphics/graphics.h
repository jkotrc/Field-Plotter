#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <util/math.h>
#include <vector>

namespace fieldplotter {

enum class CameraMode {
    PERSPECTIVE,
    ORTHOGRAPHIC,
    PLANE
};

class Camera {
	private:
		float angle;
		float phi;
		float radius;
		glm::vec3 up;
		glm::vec3 cameraPosition;
		glm::vec3 origin;
		glm::mat4 viewMat;
	public:
	Camera();
	glm::mat4 getViewMatrix();
	glm::vec3 getPos();
	void moveLinear(float x, float y, float z);
	void scroll(float amount);
	void moveCamera(float dtheta, float dphi);
};
/**
 * Draw calls modify buffers until update() is called for effect on screen
 */
class Graphics {
public:
  // set camera orientation
  virtual ~Graphics(){}
  virtual void drawArrow(glm::vec3 &position, glm::vec3 &val) = 0;

  virtual void drawLines(std::vector<std::pair<glm::vec3,glm::vec3>> const &segments) = 0;
  virtual void drawCurve(std::vector<glm::vec3> const &pieces) = 0;
  virtual void drawPoint(std::vector<glm::vec3> const &pieces) = 0;
  virtual void update() = 0;

  virtual void setLineWidth(unsigned int width) = 0;
  virtual void setLineColor(glm::vec4 const &col) = 0;
    Camera camera;
};

//initialize imgui in OpenGLGraphics


}
#endif // GRAPHICS_H_
