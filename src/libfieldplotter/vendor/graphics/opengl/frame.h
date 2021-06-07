#ifndef __OPENGL_FRAME_H_
#define __OPENGL_FRAME_H_
#include <GL/glew.h>
#include "rendering/frame.h"

namespace rendering {
    class OpenGLFrame : public Frame {
        public:
            OpenGLFrame(Frame::Size viewportsize);
            ~OpenGLFrame();
            void resizeViewport(Frame::Size size) override;
            void destroy() override;
    };
}

#endif // __OPENGL_FRAME_H_
