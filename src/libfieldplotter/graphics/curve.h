#ifndef __CURVE_H_
#define __CURVE_H_

#include "drawable.h"
#include <vector>
#include <glm/glm.hpp>
/*
** A curve with intermediate points extrapolated
** using some method
*/

//TODO Make Line a subclass of this
//TODO Refactor for this to use the data types instead of vec3
class Curve : public Drawable {
    public:
        Curve(std::vector<glm::vec3> const& points);
        ~Curve();
        void update(std::vector<glm::vec3> const& points);
        void select(std::vector<bool> const& selection);
        void draw() override;
        std::vector<glm::vec3> getPoints() const;
        std::vector<bool> getSelection() const;
    private:
        std::vector<glm::vec3> m_points;
        std::vector<bool> m_selection;
};


#endif // __CURVE_H_
