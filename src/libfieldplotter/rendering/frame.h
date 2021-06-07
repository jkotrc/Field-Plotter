#ifndef __FRAME_H_
#define __FRAME_H_

#include <array>
/*
** The class that defines the frame we render to.
** It calls to the lower-level API to retrieve a frame, making it known whether
** a frame is available to be drawn to
**
** Can it happen that a rendering frame stops being available after initialization?
** No. Ending a frame should detach the graphical components and make them undrawable.
** Drawing is done using the Renderer and there is one instance of Renderer per drawable frame
*/
namespace rendering {
    class Frame {
        public:
            using Size = std::array<int,2>;
            virtual ~Frame() = default;
            Size getViewportSize() const;
            virtual void resizeViewport(Frame::Size size)=0;
            virtual void destroy()=0;
            bool isAvailable() const;
        protected:
            bool m_available;
            Frame::Size m_viewportdim;
    };
}
#endif // __FRAME_H_
