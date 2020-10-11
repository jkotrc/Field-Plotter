#include <fieldplotter/fieldlines.h>
#include <fieldplotter/computation.h>
#include "Shaders.h"


#define BUFFER_STEP 100
#define PI 3.1415926

#include <exception>
#include <iostream>
using namespace std;


FieldLines::FieldLines(float range, float ds, int line_density)
: range(range),ds(ds),line_density(line_density)
{
    modelMatrix=glm::mat4(1.0f);    
}

void FieldLines::initGraphics() {
    //assert(vertices.size()>1);//TODO: remove this assertion
    buffers.resize(1);
    glGenBuffers(1,&buffers[0]);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,false,0,nullptr);
    
    //glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(Point),&vertices[0],GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER,2,nullptr,GL_STATIC_DRAW);

    assert(buffers.size()==1);
    programID=loadShadersFromSource(Shaders::LINES_VERTEXSHADER,Shaders::LINES_FRAGMENTSHADER);
    glUseProgram(programID);
    glUniformBlockBinding(programID, glGetUniformBlockIndex(programID, "Matrices"), 0);
	glUniformMatrix4fv(glGetUniformLocation(programID, "modelMat"),1,false,glm::value_ptr(modelMatrix));
}
void FieldLines::draw() {
    glUseProgram(programID);
	glUniformBlockBinding(programID, glGetUniformBlockIndex(programID, "Matrices"), 0);
	glUniformMatrix4fv(glGetUniformLocation(programID, "modelMat"),1,false,glm::value_ptr(modelMatrix));
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
    glDrawArrays(GL_LINES,0,vertices.size());
}
void FieldLines::updateBuffer() {

    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glVertexAttribPointer(0,3,GL_FLOAT,false,0,nullptr);

    size_t vert_size = vertices.size();//call once because this keeps changing
    if (vert_size > thread_buffersize) {
        thread_buffersize=vert_size*2;
        glBufferData(
        GL_ARRAY_BUFFER,
        thread_buffersize*sizeof(Point),
        nullptr,
        GL_STATIC_DRAW    
        );
        thread_bufferoffset=0;//reallocating the buffer makes us lose everything
    }
    
    glBufferSubData(GL_ARRAY_BUFFER,
    thread_bufferoffset*sizeof(Point),
    (vert_size-thread_bufferoffset)*sizeof(Point),
    &vertices[thread_bufferoffset]
    );
    thread_bufferoffset=vert_size;  
}


float FieldLines::getRange() {
    return range;
}
float FieldLines::getLineStep() {
    return ds;
}
int FieldLines::getLineDensity() {
    return line_density;
}
std::vector<Point>& FieldLines::getVertices() {
    return vertices;
}