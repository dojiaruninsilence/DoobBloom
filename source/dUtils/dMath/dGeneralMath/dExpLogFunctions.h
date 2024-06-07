#pragma once

#include <cmath>

namespace doob {
	template <typename Type>
	class dExpLogFunctions {
        dExpLogFuntions() {}
        ~dExpLogFuntions() {}

        // exponetial function
        Type exp(Type x) {
            return std::exp(x);
        }

        // natural logarithm
        Type log(Type x) {
            return std::log(x);
        }

        // base 10 logarithm
        Type log10(Type x) {
            return std::log10(x);
        }

        // base 2 logarithm
        Type log2(Type x) {
            return std::log2(x);
        }

        // power function
        Type pow(Type base, Type exponent) {
            return std::pow(x, y);
        }
	};
}