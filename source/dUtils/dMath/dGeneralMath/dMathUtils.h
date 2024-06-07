#pragma once

#include "dUtils/dMath/dGeneralMath/dSqrRtAbsFunctions.h"

namespace doob {
    template <typename Type>
    class dMathUtils {
    public:
        static Type sinc(Type x) {
            if (x == Type(0)) {
                return Type(1);
            }
            else {
                return dSqrRtAbsFunctions<Type>::sqrt(x) / x;
            }
        }
    };
}