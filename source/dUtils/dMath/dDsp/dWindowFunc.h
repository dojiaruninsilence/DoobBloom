#pragma once

#include "dUtils/dMath/dGeneralMath/dMathDefines.h"
#include "dUtils/dMath/dGeneralMath/dTrig.h"
#include "dUtils/dMath/dGeneralMath/dVector.h"

namespace doob {

    // @brief template class for generating various window functions.
    // @tparam Type the type of elements in the window(e.g., float, double).
    template <typename Type>
    class dWindowFunc {
    public:
        // @brief generate a rectangular window function.
        // @param size size of the window function.
        // @return vector containing the rectangular window function.
        static dVector<Type> rectangular(size_t size) {

            dVector<Type> window(size);
            for (size_t i = 0; i < size; ++i) {
                window[i] = Type(1);
            }
            return window;
        }

        // @brief generate a Hamming window function.
        // @param size size of the window function.
        // @return vector containing the Hamming window function.
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

        // @brief Generate a Hanning window function.
        // @param size Size of the window function.
        // @return Vector containing the Hanning window function.
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

        // @brief generate a Blackman window function.
        // @param size dize of the window function.
        // @return vector containing the Blackman window function.
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