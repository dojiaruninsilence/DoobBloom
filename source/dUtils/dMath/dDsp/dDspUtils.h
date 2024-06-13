#pragma once

#include "dUtils/dDiagnostics/dErrKit.h"

#include "dUtils/dMath/dGeneralMath/dSqrRtAbsFunctions.h"
#include "dUtils/dMath/dGeneralMath/dVector.h"
#include "dUtils/dMath/dGeneralMath/dVectorComplex.h"

#include <complex>

namespace doob {

    // @class dDspUtils
    // @brief Utility class for various DSP operations.
    // @tparam Type The type of elements for the DSP operations.
    template <typename Type>
    class dDspUtils {
    public:
        // constructor/destructor
        dDspUtils() {}
        ~dDspUtils() {}

        // @brief Calculate the magnitude of a complex number.
        // @param value The complex number.
        // @return The magnitude of the complex number.
        static Type complexMagnitude(const std::complex<Type>& value) {

            return dSqrRtAbsFunctions<Type>::sqrt(value.real() * value.real() + value.imag() * value.imag());
        }

        // @brief Convert a vector of complex numbers to their magnitudes.
        // @param spectrum The vector of complex numbers.
        // @return A vector of magnitudes.
        static dVectorComplex<Type> complexVectorMagnitude(
            const dVectorComplex<std::complex<Type>>& spectrum) {

            dVectorComplex<Type> magnitudes;

            for (size_t i = 0; i < complexVector.getSize(); ++i) {
                magnitudes.push_back(complexMagnitude(complexVector[i]));
            }

            return magnitudes;
        }

        // @brief Normalize a signal to a specified range.
        // @param signal The input signal vector.
        // @param minRange The minimum range value.
        // @param maxRange The maximum range value.
        // @return The normalized signal vector.
        static dVector<Type> normalizeSignal(
            const dVector<Type>& signal, Type minRange, Type maxRange) {

            Type minSignal = signal.min();
            Type maxSignal = signal.max();

            if (minSignal == maxSignal) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Signal min and max values are equal, normalization is not possible.", __FILE__, __LINE__);
            }

            Type scale = (maxRange - minRange) / (maxSignal - minSignal);

            dVector<Type> normalizedSignal(signal.getSize());
            for (size_t i = 0; i < signal.getSize(); ++i) {
                normalizedSignal[i] = minRange + (signal[i] - minSignal) * scale;
            }

            return normalizedSignal;
        }

        // @brief Trim leading zeros from a signal.
        // @param signal The input signal vector.
        // @return The signal vector with leading zeros trimmed.
        static dVector<Type> trimLeadingZeros(const dVector<Type>& signal) {

            size_t start = 0;
            while (start < signal.getSize() && signal[start] == 0) {
                ++start;
            }

            return signal.subVector(start);
        }

        // @brief Trim trailing zeros from a signal.
        // @param signal The input signal vector.
        // @return The signal vector with trailing zeros trimmed.
        static dVector<Type> trimTrailingZeros(const dVector<Type>& signal) {

            size_t end = signal.getSize();
            while (end > 0 && signal[end - 1] == 0) {
                --end;
            }

            return signal.subVector(0, end);
        }

        // @brief Trim signal between start and end indices.
        // @param signal The input signal vector.
        // @param start The starting index.
        // @param end The ending index.
        // @return The trimmed signal vector.
        static dVector<Type> trimSignal(
            const dVector<Type>& signal, size_t start, size_t end) {

            start = std::min(start, signal.getSize());
            end = std::min(end, signal.getSize());

            return signal.subVector(start, end);
        }

        // @brief Zero pad a signal to a specified length.
        // @param signal The input signal vector.
        // @param paddedLength The desired length after padding.
        // @return The zero - padded signal vector.
        static dVector<Type> zeroPadSignal(
            const dVector<Type>& signal, size_t paddedLength) {

            if (paddedLength < signal.getSize()) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Padded length is less than the signal size.", __FILE__, __LINE__);
            }

            size_t paddingSize = std::max<size_t>(paddedLength - signal.getSize(), 0);

            dVector<Type> paddedSignal(paddedLength);

            for (size_t i = 0; i < signal.getSize(); ++i) {
                paddedSignal[i] = signal[i];
            }

            for (size_t i = signal.getSize(); i < paddedLength; ++i) {
                paddedSignal[i] = Type(0);
            }

            return paddedSignal;
        }

        // @brief Compute moving average of a vector.
        // @param input The input signal vector.
        // @param windowSize The size of the moving average window.
        // @return The signal vector with moving average applied.
        static dVector<Type> movingAverage(
            const dVector<Type>& input, size_t windowSize) {

            if (windowSize == 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Window size for moving average is zero.", __FILE__, __LINE__);
            }

            dVector<Type> result(input.getSize());

            for (size_t i = 0; i < input.getSize(); ++i) {
                // compute the average of the values within the window
                size_t start = (i < windowSize / 2) ? 0 : i - windowSize / 2;
                size_t end = (i + windowSize / 2 >= input.getSize()) ? input.getSize() - 1 : i + windowSize / 2;

                Type sum = Type(0);
                for (size_t j = start; j <= end; ++j) {
                    sum += input[j];
                }
                result[i] = sum / static_cast<Type>(end - start + 1);
            }

            return result;
        }
    };
}