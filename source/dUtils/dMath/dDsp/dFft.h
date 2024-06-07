#pragma once

#include "dUtils/dMath/dGeneralMath/dMathDefines.h"
#include "dUtils/dMath/dGeneralMath/dVector.h"
#include "dUtils/dMath/dGeneralMath/dVectorComplex.h"

#include <cmath>

namespace doob {
    template <typename Type>
    class dFft {
    public:
        // compute the forward fft of a complex signal
        static dVectorComplex<std::complex<Type>> forward(
            const dVectorComplex<std::complex<Type>>& signal) {

            size_t N = signal.getSize();

            // base case of recursion: if the size of the signal is 1, return it as is 
            if (N == 1) {
                return signal;
            }

            dVectorComplex<std::complex<Type>> even(N / 2), odd(N / 2);
            for (size_t i = 0; i < N / 2; ++i) {
                even[i] = signal[2 * i];
                odd[i] = signal[2 * i + 1];
            }

            // recursive fft computation for even and odd parts
            dVectorComplex<std::complex<Type>> even_fft = forward(even);
            dVectorComplex<std::complex<Type>> odd_fft = forward(odd);

            // combine the results
            dVectorComplex<std::complex<Type>> result(N);
            for (size_t k = 0; k < N / 2; ++k) {
                Type theta = -2.0 * D_PI * k / N;
                std::complex<Type> twiddle = std::polar((Type)1.0, theta) * odd_fft[k];
                result[k] = even_fft[k] + twiddle;
                result[k + N / 2] = even_fft[k] - twiddle;
            }

            return result;
        }

        // compute the inverse fft of a complex signal
        static dVectorComplex<std::complex<Type>> inverse(
            const dVectorComplex<std::complex<Type>>& spectrum) {

            // get the size of the spectrum
            size_t N = spectrum.getSize();

            // conjugate the spectrum
            dVectorComplex<std::complex<Type>> conjugate_spectrum = spectrum;
            for (size_t i = 0; i < N; ++i) {
                conjugate_spectrum[i] = std::conj(spectrum[i]);
            }

            // apply forward fft on the conjugated spectrum
            dVectorComplex<std::complex<Type>> time_domain_signal = forward(conjugate_spectrum);

            // conjugate the time domain signal and scale
            for (size_t i = 0; i < N; ++i) {
                time_domain_signal[i] = std::conj(time_domain_signal[i]) / static_cast<Type>(N);
            }

            return time_domain_signal;
        }

        // compute the forward fft of a real signal
        static dVectorComplex<std::complex<Type>> forwardReal(const dVector<Type>& signal) {

            size_t N = signal.getSize();

            dVectorComplex<std::complex<Type>> spectrum(N);

            dVectorComplex<std::complex<Type>> complexSignal(N);
            for (size_t i = 0; i < N; ++i) {
                complexSignal[i] = std::complex<Type>(signal[i], 0);
            }

            spectrum = forward(complexSignal);

            return spectrum;
        }

        // perform complex multiplication in the frequency domain
        static dVectorComplex<std::complex<Type>> complexMultiply(
            const dVectorComplex<std::complex<Type>>& spectrum1,
            const dVectorComplex<std::complex<Type>>& spectrum2) {

            size_t N = spectrum1.getSize();

            dVectorComplex<std::complex<Type>> result(N);
            for (size_t i = 0; i < N; ++i) {
                result[i] = spectrum1[i] * spectrum2[i];
            }

            return result;
        }
    };
}