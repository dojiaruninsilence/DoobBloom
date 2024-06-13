#pragma once

#include "dUtils/dDiagnostics/dErrKit.h"

#include <cmath>

namespace doob {

    // class for square root and absolute value functions
    template <typename Type>
    class dSqrRtAbsFunctions {
    public:
        // calculate the square root of x
        static Type sqrt(Type x) {
            D_ASSERT(x >= 0, "Square root of negative value is not defined");

            if (x < 0) {
                reportError(errorLevel::D_ERROR, errorCode::RUNTIME_ERROR,
                    "Square root of negative value.", __FILE__, __LINE__);
            }

            return std::sqrt(x);
        }

        // calculate the absolute value of x
        static Type abs(Type x) {
            return std::abs(x);
        }
    };
}