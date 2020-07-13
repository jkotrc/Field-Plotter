#include "Camera.h"


#define min(a,b) !(b<a)?a:b

Camera::Camera(int window_width, int window_height, GLfloat roll_speed, bool x_axis, bool y_axis) {
    this->windowWidth = window_width;
    this->windowHeight = window_height;

    this->rollSpeed = roll_speed;
    this->angle = 0.0f;
    this->camAxis = glm::vec3(0.0f, 1.0f, 0.0f);

    this->xAxis = x_axis;
    this->yAxis = y_axis;

    this->currentPos = vec3(0, 0, 0);
    this->prevPos = currentPos;
}


vec3 Camera::toScreenCoord(double x, double y) {
    vec3 coord(0.0f);
    if (xAxis) {
        coord.x = (2 * x - windowWidth) / windowWidth;
        
    }
    if (yAxis) {
        coord.y = -(2 * y - windowHeight) / windowHeight;
        
    }

    /* Clamp it to border of the windows, comment these codes to allow rotation when cursor is not over window */
    coord.x = glm::clamp(coord.x, -1.0f, 1.0f);
    coord.y = glm::clamp(coord.y, -1.0f, 1.0f);


    float length_squared = coord.x * coord.x + coord.y * coord.y;
    if (length_squared <= 1.0)
        coord.z = sqrt(1.0 - length_squared);
    else
        coord = glm::normalize(coord);

    return coord;
}


#include <stdio.h>
void Camera::updateVars() {
    angle = acos(min(1.0f, glm::dot(prevPos, currentPos)));
    camAxis = glm::cross(prevPos, currentPos);
}

//
/**
 * Create rotation matrix within the camera coordinate,
 * multiply this matrix with view matrix to rotate the camera
 */
glm::mat4 Camera::createViewRotationMatrix() {
    updateVars();
    return glm::rotate(mat4(1.0f),glm::degrees(angle) * rollSpeed, camAxis);
}

/**
 * Create rotation matrix within the world coordinate,
 * multiply this matrix with model matrix to rotate the object
 */
glm::mat4 Camera::createModelRotationMatrix(glm::mat4& view_matrix) {
    updateVars();
    glm::vec3 axis = glm::inverse(glm::mat3(view_matrix)) * camAxis;
    return glm::rotate(mat4(1.0f),glm::degrees(angle) * rollSpeed, axis);
}

void Camera::setPrevPos(vec3 pos) {
    this->prevPos = pos;
}
void Camera::setCurrentPos(vec3 pos) {
    this->currentPos = pos;
}
vec3 Camera::getCurrentPos() { return this->currentPos; }