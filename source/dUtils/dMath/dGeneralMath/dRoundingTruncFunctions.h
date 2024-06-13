#pragma once

#include "dUtils/dDiagnostics/dErrKit.h"

#include <cmath>
#include <stdexcept>

namespace doob {

    // Class for rounding and truncation functions
    template <typename Type>
    class dRoundingTruncFunctions {
    public:
        // constructor/destructor
        dRoundingTruncFunctions() {}
        ~dRoundingTruncFunctions() {}

        // round to the nearest integer
        Type round(Type x) {
            return std::round(x);
        }

        // round towards negative infinity
        Type floor(Type x) {
            return std::floor(x);
        }

        // round towards positive infinity
        Type ceil(Type x) {
            return std::ceil(x);
        }

        // truncate towards zero
        Type trunc(Type x) {
            if constexpr (std::is_integral<Type>::value) {
                // directly return the value if it is already integral type
                return x;
            }
            else if constexpr (std::is_floating_point<Type>::value) {
                int temp = static_cast<int>(x);
                if (x >= 0) {
                    return static_cast<Type>(temp);
                }
                else if (static_cast<Type>(temp) == x) {
                    return x;
                }
                else {
                    return static_cast<Type>(temp + 1);
                }
            }
            else {
                reportError(errorLevel::D_ERROR, errorCode::RUNTIME_ERROR,
                    "Unsupported type for truncation.", __FILE__, __LINE__);
            }
        }
    };
}