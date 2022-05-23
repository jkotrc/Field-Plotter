#ifndef VECTORS_H_
#define VECTORS_H_

#include <cmath>

namespace fp {

    template<int dim>
    struct Vec {
        double coords[dim];
        double magnitude() const {
            double result = 0;
            for (int i = 0; i < dim; i++) {
                result+= coords[i]*coords[i];
            }
            return sqrt(result);
        }
    };

}


#endif // VECTORS_H_
