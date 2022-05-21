#ifndef SPACE_H_
#define SPACE_H_

#include <linalg.h>
#include "fieldlines.h"

namespace fieldplotter {

    using namespace linalg::aliases;

    class Space2D {
        public:
            Space2D(float2 x_range, float2 y_range);

            ~Space2D();

            void addCharge(Charge const& charge);

            void toggleLines();

        private:
            FieldLines lines;
    };
}


#endif // SPACE_H_
