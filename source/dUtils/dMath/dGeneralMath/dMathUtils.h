#pragma once

#include "dUtils/dDiagnostics/dErrKit.h"

#include "dUtils/dMath/dGeneralMath/dSqrRtAbsFunctions.h"

namespace doob {

    // utility class for mathematical functions
    template <typename Type>
    class dMathUtils {
    public:
        // calculate the sinc function
        // x: the input value for which to calculate the sinc function
        static Type sinc(Type x) {
            // handle the special case when x is zero
            if (x == Type(0)) {
                DB_INFO("sinc({}) = 1 (special case for x=0)", x);
                return Type(1);
            }
            else {
                // check if x is within valid range if applicable
                if (x < Type(0)) {
                    DB_WARN("sinc({}) received a negative value, proceeding with calculation", x);
                }

                // calculate sinc using dSqrRtAbsFunctions
                Type result = dSqrRtAbsFunctions<Type>::sqrt(x) / x;

                // log the calculated result
                DB_INFO("sinc({}) = {}", x, result);

                return result;
            }
        }
    };
}