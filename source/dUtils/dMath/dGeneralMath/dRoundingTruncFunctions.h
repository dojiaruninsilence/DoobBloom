#pragma once

#include <cmath>

namespace doob {
    template <typename Type>
    class dRoundingTruncFunctions {
    public:
        dRoundingTruncFunctions() {}
        ~dRoundingTruncFunctions() {}

        // round to the nearest integer
        Type round(Type x) {
            return std::round(x);
        }

        // Round towards negative infinity
        Type floor(Type x) {
            return std::floor(x);
        }

        // Round towards positive infinity
        Type ceil(Type x) {
            return std::ceil(x);
        }

        // Truncate towards zero
        Type trunc(Type x) {
            int temp = static_cast<int>(x);
            if (x >= 0) {
                return static_cast<Type>(temp);
            }
            else if (temp == x) {
                return x;
            }
            else {
                return static_cast<Type>(temp + 1);
            }
        }
    };
}