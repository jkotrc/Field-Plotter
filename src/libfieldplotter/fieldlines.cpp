#include "fieldlines.h"
#include "computation.h"
#include "graphics.h"

#include "Shaders.h"

#define PI 3.1415926

#include <iostream>
#include <stdlib.h>
using namespace std;


FieldLines::FieldLines(float range, float visible_step, float ds, int line_density)
: range(range),visible_step(visible_step),ds(ds),line_density(line_density),vert_size(size_t(0)),lineindex_size(size_t(0))
{
    modelMatrix=glm::mat4(1.0f);    
}
FieldLines::~FieldLines() {
    //Do nothing because vectors delete themselves when they go out of scope anyway
}

void FieldLines::clearComputation() {
    this->computed = false;
    thread_bufferoffset = 0;
    vertices.erase(vertices.begin(), vertices.end());
    assert(vertices.size() == 0);
    lines_index.erase(lines_index.begin(), lines_index.end());
    assert(lines_index.size() == 0);
}

void FieldLines::initGraphics() {
    if (graphicsInitialized) return;
    buffers.resize(1);
    glGenBuffers(1,&buffers[0]);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,false,0,nullptr);
    assert(buffers.size()==1);

    programID=loadShadersFromSource(Shaders::LINES_VERTEXSHADER,Shaders::LINES_FRAGMENTSHADER);

    glUniformBlockBinding(programID, glGetUniformBlockIndex(programID, "Matrices"), 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, parent->getSceneMatrices());
    glUniformMatrix4fv(glGetUniformLocation(programID, "modelMat"), 1, false, glm::value_ptr(modelMatrix));
    glUseProgram(programID);

    graphicsInitialized = true;
    
}
void FieldLines::staticDraw() {
    glUseProgram(programID);
	glUniformBlockBinding(programID, glGetUniformBlockIndex(programID, "Matrices"), 0);
	glUniformMatrix4fv(glGetUniformLocation(programID, "modelMat"),1,false,glm::value_ptr(modelMatrix));
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);

    for (int i = 0; i < lineindex_size-1; i++) {
        const int size = lines_index[i+1]-lines_index[i];
        glDrawArrays(GL_LINE_STRIP, lines_index[i], size);
    }
    //glDrawArrays(GL_LINE_STRIP, lines_index[lineindex_size-1], vert_size-lines_index[lineindex_size-1]);
}

void FieldLines::updateBuffers() {
    vert_size = vertices.size();
    if (vert_size == thread_bufferoffset) { return; }
    lineindex_size=lines_index.size();
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
    if (vert_size > thread_buffersize) {
        thread_buffersize=vert_size*2;
        glBufferData(
        GL_ARRAY_BUFFER,
        thread_buffersize*sizeof(Point),
        nullptr,
        GL_STATIC_DRAW    
        );
        thread_bufferoffset=0;
    }    
    glBufferSubData(GL_ARRAY_BUFFER,
    thread_bufferoffset*sizeof(Point),
    (vert_size-thread_bufferoffset)*sizeof(Point),
    &vertices[thread_bufferoffset]
    );
    thread_bufferoffset=vert_size;
}

void FieldLines::finalizeBuffers() {
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Point), &vertices[0], GL_STATIC_DRAW);
    thread_buffersize = vertices.size();
}

float FieldLines::getRange() {
    return range;
}
float FieldLines::getLineStep() {
    return ds;
}
float FieldLines::getVisibleStep() {
    return visible_step;
}
int FieldLines::getLineDensity() {
    return line_density;
}
std::vector<Point>& FieldLines::getVertices() {
    return vertices;
}
std::vector<int>& FieldLines::getLinesIndex() {
    return lines_index;
}
