#include <fieldplotter/fieldplotter.h>
#include "../Debug.h"


using namespace glm;
Camera::Camera(GLfloat roll_speed)
    :
    cameraPosition(vec3(1, 0, 0)),
    sphericalCoord(vec2(0,0)),
    origin(vec3(0,0,0)),
    angle(0.0f),
    phi(0.0f),
    up(vec3(0,1,0)),
    viewMat(lookAt(cameraPosition+origin, origin, vec3(0,1,0)))
{}

vec3 Camera::getPos() {
    return this->cameraPosition;
}

void Camera::moveCamera(float dtheta, float dphi) {
    angle+=dtheta;
    phi+=dphi;
    cameraPosition=rotateY(cameraPosition, dtheta);
    vec3 axis_of_rotation = vec3(sin(angle),0,cos(angle));
    up = vec3(0,cos(phi),0);
    cameraPosition = glm::rotate(cameraPosition,dphi,axis_of_rotation);
    viewMat=lookAt(cameraPosition+origin,origin,up);
}

mat4 Camera::getViewMatrix() {
    return viewMat;
}

void Camera::moveLinear(float x, float y, float z) {
    origin.x+=x;
    origin.y+=y;
    origin.z+=z;
    viewMat=lookAt(cameraPosition+origin,origin,up);
}
