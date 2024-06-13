#pragma once

#include "dUtils/dDiagnostics/dErrKit.h"

#include "dUtils/dMath/dDsp/dFft.h"

#include "dUtils/dMath/dGeneralMath/dVector.h"
#include "dUtils/dMath/dGeneralMath/dVectorComplex.h"

namespace doob {

    // @class dConvolution
    // @brief Provides static methods for performing various types of convolutions on signals.
    // @tparam Type The type of elements in the signal and kernel.
    template <typename Type>
    class dConvolution {
    public:
        // @brief Perform linear convolution between two signals.
        // @param signal The input signal vector.
        // @param kernel The kernel vector.
        // @return The result of the linear convolution.
        static dVector<Type> linearConvolution(
            const dVector<Type>& signal,
            const dVector<Type>& kernel) {

            size_t signalSize = signal.getSize();
            size_t kernelSize = kernel.getSize();

            if (signalSize == 0 || kernelSize == 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Signal or kernel size is zero.", __FILE__, __LINE__);
            }

            size_t convSize = signalSize + kernelSize - 1;

            dVector<Type> result(convSize, Type(0));

            for (size_t n = 0; n < convSize; ++n) {
                for (size_t k = 0; k < kernelSize; ++k) {
                    if (n >= k && n - k < signalSize) {
                        result[n] += signal[n - k] * kernel[k];
                    }
                }
            }

            return result;
        }

        // @brief Perform overlap-add convolution between two signals.
        // @param signal The input signal vector.
        // @param kernel The kernel vector.
        // @return The result of the overlap - add convolution.
        static dVector<Type> overlapAddConvolution(
            const dVector<Type>& signal,
            const dVector<Type>& kernel) {

            size_t signalSize = signal.getSize();
            size_t kernelSize = kernel.getSize();

            if (signalSize == 0 || kernelSize == 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Signal or kernel size is zero.", __FILE__, __LINE__);
            }

            // compute the segment size (usually chosen as a power of 2 for fft efficiency)
            size_t segmentSize = 64; // choose an appropriate segment size

            // compute the hop size (overlap)
            size_t hopSize = segmentSize - kernelSize + 1;

            // compute the number of segments needed to cover the entire signal
            size_t numSegments = (signalSize + hopSize - 1) / hopSize;

            // initialize the convolved signal with zeros
            dVector<Type> convolvedSignal(signalSize + kernelSize - 1, Type(0));

            // iterate over each segment
            for (size_t i = 0; i < numSegments; ++i) {
                // compute the start and end indices for the current segment
                size_t startIdx = i * hopSize;
                size_t endIdx = std::min(startIdx + segmentSize, signalSize);

                // extract the current segment of the signal
                dVector<Type> segment = signal.subVector(startIdx, endIdx);

                // pad the segment with zeros to match the kernel size
                if (segment.getSize() < kernelSize) {
                    segment.resize(kernelSize, Type(0));
                }

                // perform linear convolution on the segment with the kernel
                dVector<Type> convSegment = linearConvolution(segment, kernel);

                // add the convolution result to the appropriate location in the convolved signal
                size_t convStartIdx = startIdx;
                size_t convEndIdx = std::min(startIdx + kernelSize - 1, convolvedSignal.getSize());
                for (size_t j = 0; j < convSegment.getSize(); ++j) {
                    convolvedSignal[convStartIdx + j] += convSegment[j];
                }
            }

            return convolvedSignal;
        }

        // @brief Perform overlap-add convolution using FFT.
        // @param signal The input signal vector.
        // @param kernel The kernel vector.
        // @return The result of the FFT - based convolution.
        static dVector<Type> fftConvolution(
            const dVector<Type>& signal,
            const dVector<Type>& kernel) {

            size_t signalSize = signal.getSize();
            size_t kernelSize = kernel.getSize();

            if (signalSize == 0 || kernelSize == 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Signal or kernel size is zero.", __FILE__, __LINE__);
            }

            // compute the size of the fft (next power of two for efficiency)
            size_t fftSize = 1;
            while (fftSize < (signalSize + kernelSize - 1)) {
                fftSize *= 2;
            }

            // pad the signal and kernal with zeros to match the fft size
            dVector<Type> paddedSignal(fftSize, Type(0));
            dVector<Type> paddedKernel(fftSize, Type(0));
            paddedSignal.setSubVector(0, signal);
            paddedKernel.setSubVector(0, kernel);

            // compute the fft of the padded signal and kernel
            dVectorComplex<std::complex<Type>> fftSignal = dFft<Type>::forwardReal(paddedSignal);
            dVectorComplex<std::complex<Type>> fftKernel = dFft<Type>::forwardReal(paddedKernel);

            // perform element wise complex multiplication
            dVectorComplex<std::complex<Type>> fftResult = dFft<Type>::complexMultiply(fftSignal, fftKernel);

            // compute the inverse fft of the result
            dVector<Type> convolvedSignal = DFft<Type>::inverse(fftResult);

            // Extract the valid part of the convolution result
            convolvedSignal.resize(signalSize + kernelSize - 1);

            return convolvedSignal;
        }
    };
}