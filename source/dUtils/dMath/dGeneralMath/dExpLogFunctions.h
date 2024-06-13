#pragma once

#include <cmath>

namespace doob {

    // class template for various exponential and logarithmic functions
	template <typename Type>
	class dExpLogFunctions {
        // constructor
        dExpLogFuntions() {}

        // destructor
        ~dExpLogFuntions() {}

        // exponential function
        // returns e^x, where e is the base of natural logarithms
        Type exp(Type x) {
            return std::exp(x);
        }

        // natural logarithm function
        // returns the natural logarithm (base e) of x
        Type log(Type x) {
            return std::log(x);
        }

        // base 10 logarithm function
        // returns the logarithm (base 10) of x
        Type log10(Type x) {
            return std::log10(x);
        }

        // base 2 logarithm function
        // returns the logarithm (base 2) of x
        Type log2(Type x) {
            return std::log2(x);
        }

        // power function
        // returns base raised to the power of exponent
        Type pow(Type base, Type exponent) {
            return std::pow(x, y);
        }
	};
} // namespace doob