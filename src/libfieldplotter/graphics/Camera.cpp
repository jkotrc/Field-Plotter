//#include "Camera.h"

#include "../fieldplotter.h"
#include "../Debug.h"


using namespace glm;
Camera::Camera(GLfloat roll_speed)
    :
    currentPos(vec3(1, 0, 0)),
    prevPos(vec3(1, 0, 0)),
    sphericalCoord(vec2(0,0)),
    origin(vec3(0,0,0)),
    angle(0.0f),
    rotAxis(vec2(1.0f,0.0f)),
    viewMat(lookAt(currentPos, origin, vec3(0,1,0)))
{}

vec3 Camera::getPos() {
    return this->currentPos;
}

void Camera::grabCamera(int x, int y) {
    this->screenCoord = vec2(x, y);
}


#include <iostream>
#define SENSITIVITY 0.001f
using namespace std;
void Camera::moveCamera(int newX, int newY) {

    float deltaX = SENSITIVITY*(newX - screenCoord.x);
    float deltaY = SENSITIVITY*(newY - screenCoord.y);


    angle = prevAngle + deltaX;
    rotAxis[0] = cos(angle);
    rotAxis[1] = sin(angle);
    currentPos = rotateY(prevPos, deltaX);
    const vec4 rotation =glm::rotate(deltaY, vec3(rotAxis[0], 0, rotAxis[1]))*vec4(currentPos.x,currentPos.y,currentPos.z,1);
    currentPos = vec3(rotation.x, rotation.y, rotation.z);
    //currentPos = vec3(prevPos.x + changeX, prevPos.y + changeY, prevPos.z + changeZ);
    viewMat = lookAt(currentPos, origin, vec3(0, 1, 0));
}

void Camera::releaseCamera() {
    prevPos = currentPos;
    prevAngle = angle;

}

mat4 Camera::getViewMatrix() {
    return viewMat;
}

void Camera::moveLinear(float x, float y, float z) {
    viewMat=translate(viewMat,vec3(x,y,z));
}
void Camera::rotate(float x, float y, float z) {
    //vec3 axis = vec3(x,y,z);
    //axis=glm::normalize(axis);
    //viewMat=rotate(viewMat, 1,axis);
}

