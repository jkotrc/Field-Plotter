#include "plottermath.h"
glm::mat4 makePerspective(PerspectiveParams parameters) {
    return glm::perspective(parameters.fov, parameters.aspect_ratio, parameters.zNear, parameters.zFar);
}

