#include "fieldlines.h"

#include <graphics/graphics.h>
#include <graphics/shaders.h>

#define PI 3.1415926
constexpr int DYNAMICDRAW_MAX = 1000;

using namespace std;


FieldLines::FieldLines(Configuration cfg) : m_config(cfg),m_vertexbuffer({true,0})
{
    m_programID=loadShadersFromSource(Shaders::LINES_VERTEXSHADER,Shaders::LINES_FRAGMENTSHADER);
    m_parent->getUniforms().setModelMatrix(m_programID,&m_modelMatrix);
}
FieldLines::~FieldLines() {
}


void FieldLines::staticDraw() {
    glUseProgram(m_programID);
	m_parent->getUniforms().bind(m_programID,"Matrices");
    m_parent->getUniforms().setModelMatrix(m_programID,&m_modelMatrix);
    //glUniformBlockBinding(m_programID, glGetUniformBlockIndex(m_programID, "Matrices"), 0);
	//glUniformMatrix4fv(glGetUniformLocation(m_programID, "modelMat"),1,false,glm::value_ptr(m_modelMatrix));	
    m_vertexbuffer.bind();
    //glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);

    for (int i = 0; i < m_compqueue.size_approx()-1; i++) {
        const int size = m_indices[i+1]-m_indices[i];
        glDrawArrays(GL_LINE_STRIP, m_indices[i], size);
    }
    //glDrawArrays(GL_LINE_STRIP, lines_index[lineindex_size-1], vert_size-lines_index[lineindex_size-1]);
}

void FieldLines::dynamicDraw() {    
    
    size_t vert_size = m_vertices.size();
    int _index;
    Point _vertex;
    for(int i = 0; i < DYNAMICDRAW_MAX; i++) {
        bool available;
        if (available = m_compqueue.try_dequeue(_vertex)) {
            m_vertices.push_back(_vertex);
        } 
        if (m_indexqueue.try_dequeue(_index)) {
            m_indices.push_back(_index);
        } else if(!available) {
            break;
        }
    }
    size_t existing_vertices = m_vertices.size() - vert_size;

//bufferoffset = how many new vertices there already were
//vert_size = what was supposed to be the thread safe version of vertices.size()
    if (vert_size == existing_vertices) { staticDraw();return; }
    const size_t lineindex_size=m_indices.size();

    m_vertexbuffer.bind();
//    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
//    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
    if (vert_size > m_buffersize) {
        m_buffersize=vert_size*2;
        glBufferData(
        GL_ARRAY_BUFFER,
        m_buffersize*sizeof(Point),
        nullptr,
        GL_STATIC_DRAW    
        );
        existing_vertices=0;
    }    
    glBufferSubData(GL_ARRAY_BUFFER,
    existing_vertices*sizeof(Point),
    (vert_size-existing_vertices)*sizeof(Point),
    &m_vertices[existing_vertices]
    );
    existing_vertices=vert_size;
    staticDraw();
}

std::vector<Point>& FieldLines::getVertices() {
    return m_vertices;
}
std::vector<int>& FieldLines::getIndices() {
    return m_indices;
}

FieldLines::Configuration FieldLines::getConfiguration() {
    return m_config;
}

void FieldLines::configure(const Configuration& newconfig) {
    
}

//bool FieldLines::initGraphics() {
    //if (m_graphicsInitialized) return true;
    
/*
    glGenBuffers(1,&m_buffers[0]);
    glBindBuffer(GL_ARRAY_BUFFER,m_buffers[0]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,false,0,nullptr);
    assert(m_buffers.size()==1);
*/
    
/*
    glUniformBlockBinding(m_programID, glGetUniformBlockIndex(m_programID, "Matrices"), 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_parent->getSceneMatrices());
*/
//    glUniformMatrix4fv(glGetUniformLocation(m_programID, "modelMat"), 1, false, glm::value_ptr(m_modelMatrix));

   // return true;    
//}