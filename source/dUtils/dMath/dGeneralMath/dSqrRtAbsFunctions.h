#pragma once

#include <cmath>

namespace doob {
    template <typename Type>
    class dSqrRtAbsFunctions {
    public:
        // calculate the square root of x
        static Type sqrt(Type x) {
            return std::sqrt(x);
        }

        // calculate the absolute value of x
        static Type abs(Type x) {
            return std::abs(x);
        }
    };
}