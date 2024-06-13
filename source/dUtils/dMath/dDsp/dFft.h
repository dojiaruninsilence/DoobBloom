#pragma once

#include "dUtils/dDiagnostics/dErrKit.h"

#include "dUtils/dMath/dGeneralMath/dMathDefines.h"
#include "dUtils/dMath/dGeneralMath/dVector.h"
#include "dUtils/dMath/dGeneralMath/dVectorComplex.h"

#include <cmath>

namespace doob {

    // @class dFft
    // @brief Utility class for performing FFT operations.
    // @tparam Type The type of elements for the FFT operations.
    template <typename Type>
    class dFft {
    public:
        // @brief Compute the forward FFT of a complex signal.
        // @param signal The input complex signal.
        // @return The FFT of the input signal.
        static dVectorComplex<std::complex<Type>> forward(
            const dVectorComplex<std::complex<Type>>& signal) {

            size_t N = signal.getSize();

            // base case of recursion: if the size of the signal is 1, return it as is 
            if (N == 1) {
                return signal;
            }

            // Ensure N is a power of 2
            if ((N & (N - 1)) != 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "FFT input size is not a power of 2.", __FILE__, __LINE__);
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

        // @brief Compute the inverse FFT of a complex signal.
        // @param spectrum The input frequency domain spectrum.
        // @return The inverse FFT of the input spectrum.
        static dVectorComplex<std::complex<Type>> inverse(
            const dVectorComplex<std::complex<Type>>& spectrum) {

            // get the size of the spectrum
            size_t N = spectrum.getSize();

            // Ensure N is a power of 2
            if ((N & (N - 1)) != 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "FFT input size is not a power of 2.", __FILE__, __LINE__);
            }

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

        // @brief Compute the forward FFT of a real signal.
        // @param signal The input real signal.
        // @return The FFT of the input signal.
        static dVectorComplex<std::complex<Type>> forwardReal(const dVector<Type>& signal) {

            size_t N = signal.getSize();

            // Ensure N is a power of 2
            if ((N & (N - 1)) != 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "FFT input size is not a power of 2.", __FILE__, __LINE__);
            }

            dVectorComplex<std::complex<Type>> spectrum(N);

            dVectorComplex<std::complex<Type>> complexSignal(N);
            for (size_t i = 0; i < N; ++i) {
                complexSignal[i] = std::complex<Type>(signal[i], 0);
            }

            spectrum = forward(complexSignal);

            return spectrum;
        }

        // @brief Perform complex multiplication in the frequency domain.
        // @param spectrum1 The first input spectrum.
        // @param spectrum2 The second input spectrum.
        // @return The result of the complex multiplication.
        static dVectorComplex<std::complex<Type>> complexMultiply(
            const dVectorComplex<std::complex<Type>>& spectrum1,
            const dVectorComplex<std::complex<Type>>& spectrum2) {

            size_t N = spectrum1.getSize();

            if (N != spectrum2.getSize()) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Spectra sizes do not match for complex multiplication.", __FILE__, __LINE__);
            }

            dVectorComplex<std::complex<Type>> result(N);
            for (size_t i = 0; i < N; ++i) {
                result[i] = spectrum1[i] * spectrum2[i];
            }

            return result;
        }
    };
}