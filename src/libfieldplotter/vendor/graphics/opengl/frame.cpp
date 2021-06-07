#include "frame.h"
using namespace rendering;

OpenGLFrame::OpenGLFrame(Frame::Size viewportsize) {
    if(glewInit() != GLEW_OK) {
        m_available=false;
    } else {
        this->resizeViewport(viewportsize);
    }
}
OpenGLFrame::~OpenGLFrame() {

}
void OpenGLFrame::resizeViewport(Frame::Size newsize) {
    m_viewportdim = newsize;
    glViewport(0,0, m_viewportdim[0], m_viewportdim[1]);
}
void OpenGLFrame::destroy() {

}
