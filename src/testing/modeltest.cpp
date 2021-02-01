#include <gtest/gtest.h>
#include <graphics/sceneuniforms.h>
#include <graphics/model.h>
#include <graphics/shaders.h>
#include <graphics/graphics.h>
#include <fieldplotter_pch.h>
using namespace glm;
struct MatricesBlock {
    mat4 projection;
    mat4 view;
    vec3 campos;
};

class SceneUniformsTest : public ::testing::Test {
    protected:
        SceneUniformsTest() : uniforms(SceneUniforms(mat4(13.3f),mat4(1.3f),{1.1f,2.2f,3.3f})) {
            sampleShader = loadShadersFromSource(Shaders::CHARGE_VERTEXSHADER,Shaders::CHARGE_FRAGMENTSHADER);
        }    
    SceneUniforms uniforms;
    GLuint sampleShader;
};

TEST_F(SceneUniformsTest, BindErrorWhenNameWrong) {
    uniforms.bind(sampleShader, "JohnCena");
}

TEST_F(SceneUniformsTest, DataIsInBuffer) {
    uniforms.bind(sampleShader, "Matrices");
    MatricesBlock* raw_buffer = (MatricesBlock*) glMapBuffer(GL_UNIFORM_BUFFER, GL_READ_WRITE);

    MatricesBlock* data = new MatricesBlock[1];
    std::copy(raw_buffer,raw_buffer+1,data);
    
    ASSERT_FLOAT_EQ(glm::value_ptr(data->projection)[0], 13.3f);
    ASSERT_FLOAT_EQ(glm::value_ptr(data->view)[0], 1.3f);
    ASSERT_FLOAT_EQ(data->campos[2], 3.3f);
    delete[] data;
}