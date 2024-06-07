#pragma once

#include "dUtils/dMath/dGeneralMath/dSqrRtAbsFunctions.h"
#include "dUtils/dMath/dGeneralMath/dVector.h"
#include "dUtils/dMath/dGeneralMath/dVectorComplex.h"

#include <complex>

namespace doob {
    template <typename Type>
    class dDspUtils {
    public:
        // constructor/destructor
        dDspUtils() {}
        ~dDspUtils() {}

        // function to calculate the magnitude of a complex number
        static Type complexMagnitude(const std::complex<Type>& value) {

            return dSqrRtAbsFunctions<Type>::sqrt(value.real() * value.real() + value.imag() * value.imag());
        }

        // function to convert a vector of complex numbers to their magnitudes
        static dVectorComplex<Type> complexVectorMagnitude(
            const dVectorComplex<std::complex<Type>>& spectrum) {

            dVectorComplex<Type> magnitudes;

            for (size_t i = 0; i < complexVector.getSize(); ++i) {
                magnitudes.push_back(complexMagnitude(complexVector[i]));
            }

            return magnitudes;
        }

        // function to normalize a signal to a specified range
        static dVector<Type> normalizeSignal(
            const dVector<Type>& signal, Type minRange, Type maxRange) {

            Type minSignal = signal.min();
            Type maxSignal = signal.max();

            Type scale = (maxRange - minRange) / (maxSignal - minSignal);

            dVector<Type> normalizedSignal(signal.getSize());
            for (size_t i = 0; i < signal.getSize(); ++i) {
                normalizedSignal[i] = minRange + (signal[i] - minSignal) * scale;
            }

            return normalizedSignal;
        }

        // function to trim leading zeros from a signal
        static dVector<Type> trimLeadingZeros(const dVector<Type>& signal) {

            size_t start = 0;
            while (start < signal.getSize() && signal[start] == 0) {
                ++start;
            }

            return signal.subVector(start);
        }

        // function to trim trailing zeros from a signal
        static dVector<Type> trimTrailingZeros(const dVector<Type>& signal) {

            size_t end = signal.getSize();
            while (end > 0 && signal[end - 1] == 0) {
                --end;
            }

            return signal.subVector(0, end);
        }

        // function to trim signal between start and end indices
        static dVector<Type> trimSignal(
            const dVector<Type>& signal, size_t start, size_t end) {

            start = std::min(start, signal.getSize());
            end = std::min(end, signal.getSize());

            return signal.subVector(start, end);
        }

        // function to zero pad a signal to a specified length
        static dVector<Type> zeroPadSignal(
            const dVector<Type>& signal, size_t paddedLength) {

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

        // function to compute moving average of a vector
        static dVector<Type> movingAverage(
            const dVector<Type>& input, size_t windowSize) {
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