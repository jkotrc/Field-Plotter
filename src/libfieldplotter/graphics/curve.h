#ifndef __CURVE_H_
#define __CURVE_H_

#include "drawable.h"
#include <vector>
#include <glm/glm.hpp>
/*
** A curve with intermediate points extrapolated
** using some method
*/

class Curve : public Drawable {
    public:
        Curve(std::vector<glm::vec2> const& points);
        ~Curve();
        void update(std::vector<glm::vec2> const& points);
        void draw() override;
    private:
};


#endif // __CURVE_H_
