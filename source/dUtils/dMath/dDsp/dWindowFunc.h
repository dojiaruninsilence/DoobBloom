#pragma once

#include "dUtils/dMath/dGeneralMath/dMathDefines.h"
#include "dUtils/dMath/dGeneralMath/dTrig.h"
#include "dUtils/dMath/dGeneralMath/dVector.h"

namespace doob {
    template <typename Type>
    class dWindowFunc {
    public:
        // generate a rectangular window function
        static dVector<Type> rectangular(size_t size) {

            dVector<Type> window(size);
            for (size_t i = 0; i < size; ++i) {
                window[i] = Type(1);
            }
            return window;
        }

        // generate a hamming window function
        static dVector<Type> hamming(size_t size) {

            dVector<Type> window(size);
            const double alpha = 0.54;
            const double beta = 0.46;
            const double two_pi_over_N_minus_1 = 2.0 * D_PI / (size - 1);

            for (size_t i = 0; i < size; ++i) {
                window[i] = Type(alpha - beta * dTrig<Type>::cos(two_pi_over_N_minus_1 * i));
            }

            return window;
        }

        // generate a hanning window function
        static dVector<Type> hanning(size_t size) {

            dVector<Type> window(size);
            const double alpha = 0.5;
            const double beta = 0.5;
            const double two_pi_over_N_minus_1 = 2.0 * D_PI / (size - 1);

            for (size_t i = 0; i < size; ++i) {
                window[i] = Type(alpha - beta * dTrig<Type>::cos(two_pi_over_N_minus_1 * i));
            }

            return window;
        }

        // generate a blackman window function
        static dVector<Type> blackman(size_t size) {

            dVector<Type> window(size);
            const double alpha = 0.5 * (1.0 - 0.08);
            const double beta = 0.5;
            const double gamma = 0.08;
            const double two_pi_over_N_minus_1 = 2.0 * D_PI / (size - 1);
            const double four_pi_over_N_minus_1 = 4.0 * D_PI / (size - 1);

            for (size_t i = 0; i < size; ++i) {
                window[i] = Type(alpha - beta * dTrig<Type>::cos(two_pi_over_N_minus_1 * i) + gamma * dTrig<Type>::cos(four_pi_over_N_minus_1 * i));
            }

            return window;
        }
    };
}