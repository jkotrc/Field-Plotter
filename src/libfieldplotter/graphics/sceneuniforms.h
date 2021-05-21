#pragma once

#include <GL/glew.h>
#include "../computation/plottermath.h"
#include <string>
/**
 * - id for the uniform buffer
 * - offsets for matrices
 * - bind(programID)
 */
enum Projections {
    FP_PERSPECTIVE,
    FP_ORTHOGRAPHIC
};
using glm::mat4;
using glm::vec3;

class SceneUniforms {
    public:
        SceneUniforms(mat4 proj, mat4 view, vec3 campos);
        SceneUniforms();
        SceneUniforms(int width, int height);
        //~SceneUniforms();
        void bind(GLuint programID, std::string name);
        void setModelMatrix(GLuint programID, glm::mat4* matrix);
        //void setProjectionType(Projections type);
        void resizeProjection(int x, int y);
        mat4& getViewMatrix();
        vec3& getCameraPosition();
        void update();
        GLuint getBufferID();
    private:
        void makeBuffer();
        GLuint m_bufferID;
        PerspectiveParams m_projectionparams;
        mat4 m_projection;
        mat4 m_view;
        vec3 m_camerapos;
};