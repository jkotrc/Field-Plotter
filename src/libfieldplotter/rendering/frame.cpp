#include "frame.h"

namespace rendering {
    Frame::Size Frame::getViewportSize() const {
        return m_viewportdim;
    }
    bool Frame::isAvailable() const {
        return m_available;
    }
}
