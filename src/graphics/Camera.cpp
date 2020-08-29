#include "Camera.h"

#include "../Debug.h"

#define min(a,b) !(b<a)?a:b

using namespace glm;
Camera::Camera(int window_width, int window_height, GLfloat roll_speed)
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

/*vec3 toScreenCoord(double x, double y, int windowWidth, int windowHeight) {
    vec3 coord(0.0f);
    coord.x = (2 * x - windowWidth) / windowWidth;
    coord.y = -(2 * y - windowHeight) / windowHeight;

    //coord.x = glm::clamp(coord.x, -1.0f, 1.0f);
    //coord.y = glm::clamp(coord.y, -1.0f, 1.0f);

    float length_squared = coord.x * coord.x + coord.y * coord.y;
    if (length_squared <= 1.0)
        coord.z = sqrt(1.0 - length_squared);
    else
        coord = glm::normalize(coord);
    return coord;
}*/


void Camera::updateVars() {
    //angle = acos(min(1.0f, glm::dot(prevPos, currentPos)));
    //camAxis = glm::cross(prevPos, currentPos);
}


void Camera::grabCamera(int x, int y) {
    this->screenCoord = vec2(x, y);
}


float clock = 0.0f;
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
    
    

    const vec4 rotation =rotate(deltaY, vec3(rotAxis[0], 0, rotAxis[1]))*vec4(currentPos.x,currentPos.y,currentPos.z,1);

    currentPos = vec3(rotation.x, rotation.y, rotation.z);
    

    //currentPos = vec3(prevPos.x + changeX, prevPos.y + changeY, prevPos.z + changeZ);
    viewMat = lookAt(currentPos, origin, vec3(0, 1, 0));

    clock += 0.01f;
}

void Camera::releaseCamera() {
    prevPos = currentPos;
    prevAngle = angle;

}

mat4 Camera::getViewMatrix() {
    return viewMat;
}


