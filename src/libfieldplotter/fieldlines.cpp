#include "fieldlines.h"
#include "computation.h"
#include "graphics.h"

#include "Shaders.h"

#define PI 3.1415926

#include <stdlib.h>
using namespace std;


FieldLines::FieldLines(FieldLinesConfig cfg) : m_configuration(cfg)
{}
FieldLines::~FieldLines() {
    //Do nothing because vectors delete themselves when they go out of scope anyway
}

bool FieldLines::initGraphics() {
    if (m_graphicsInitialized) return;
    
    m_buffers.resize(1);
    glGenBuffers(1,&m_buffers[0]);
    glBindBuffer(GL_ARRAY_BUFFER,m_buffers[0]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,false,0,nullptr);
    assert(m_buffers.size()==1);

    m_programID=loadShadersFromSource(Shaders::LINES_VERTEXSHADER,Shaders::LINES_FRAGMENTSHADER);

    glUniformBlockBinding(m_programID, glGetUniformBlockIndex(m_programID, "Matrices"), 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_parent->getSceneMatrices());
    glUniformMatrix4fv(glGetUniformLocation(m_programID, "modelMat"), 1, false, glm::value_ptr(m_modelMatrix));
    glUseProgram(m_programID);

    m_graphicsInitialized = true;
    
}
void FieldLines::staticDraw() {
    glUseProgram(m_programID);
	glUniformBlockBinding(m_programID, glGetUniformBlockIndex(m_programID, "Matrices"), 0);
	glUniformMatrix4fv(glGetUniformLocation(m_programID, "modelMat"),1,false,glm::value_ptr(m_modelMatrix));
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
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
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
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

std::vector<Point>& FieldLines::getVertices() {
    return m_vertices;
}
std::vector<int>& FieldLines::getIndices() {
    return m_indices;
}
