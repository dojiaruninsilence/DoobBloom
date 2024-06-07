#pragma once

#include "dUtils/dMath/dDsp/dDspUtils.h"
#include "dUtils/dMath/dDsp/dFft.h"
#include "dUtils/dMath/dDsp/dWindowFunc.h"

#include "dUtils/dMath/dGeneralMath/dVector.h"
#include "dUtils/dMath/dGeneralMath/dVectorComplex.h"

namespace doob {
    template <typename Type>
    class dSpectralAnalysis {
    public:
        // constructor/destructor
        dSpectralAnalysis()
            : fftSize(1024), frameSize(512), hopSize(256), samplingRate(44100), windowFunctionType(0) {

            // Initialize FFT object
            fft = DFft<Type>();

            // Default values for FFT window and other parameters
            fftWindow.clear();
        }

        ~dSpectralAnalysis() {
            // destructor implementation
        }

        // function to perform spectral analysis on input signal
        dVector<Type> analyze(const dVector<Type>& inputSignal) {

            // validate input signal
            validateInputSignal(inputSignal);

            // preprocess input signal (normalize and zero-pad)
            dVector<Type> processedSignal = inputSignal;
            preprocessSignal(processedSignal);

            // split input signal into frames
            dVector<dVector<Type>> frames = splitIntoFrames(processedSignal);

            // initialize vector to store resulting spectral data
           dVector<dVector<Type>> spectralData(frames.getSize());

            // process each frame
            for (size_t i = 0; i < frames.getSize(); ++i) {
                // apply window function
                applyWindowFunction(frames[i]);

                // compute FFT
                dVectorComplex<std::complex<Type>> spectrum = fft.forwardReal(frames[i]);

                // compute magnitude spectrum
                dVector<Type> magnitude = computeMagnitude(spectrum);

                // store magnitude spectrum
                spectralData[i] = magnitude;
            }

            // optionally, you can do further processing on spectralData
            // for example, you can apply spectral smoothing, peak detection, etc.

            return spectralData; // return the resulting spectral data
        }

        // Function to compute the magnitude spectrum from the complex spectrum
        dVector<Type> computeMagnitude(const dVectorComplex<std::complex<Type>>& spectrum) {

            // initialize vector to store magnitudes
            dVector<Type> magnitudes(spectrum.getSize());

            // compute magnitude for each complex value in the spectrum
            for (size_t i = 0; i < spectrum.getSize(); ++i) {
                magnitudes[i] = dDspUtils<Type>::complexMagnitude(spectrum[i]);
            }

            return magnitudes;
        }

        // Function to generate a spectrogram from the input signal
        // This function returns a 2D array representing the spectrogram
        dVector<dVector<Type>> generateSpectrogram(
            const dVector<Type>& inputSignal, size_t frameSize, size_t hopSize) {
            // validate input signal
            validateInputSignal(inputSignal);

            // preprocess input signal (normalize and zero-pad)
            dVector<Type> processedSignal = inputSignal;
            preprocessSignal(processedSignal);

            // split input signal into frames
            dVector<dVector<Type>> frames = splitIntoFrames(processedSignal);

            // initialize vector of vectors to store spectrogram
            dVector<dVector<Type>> spectrogram(frames.getSize());

            // process each frame
            for (size_t i = 0; i < frames.getSize(); ++i) {
                // apply window function
                applyWindowFunction(frames[i]);

                // compute FFT
                dVectorComplex<std::complex<Type>> spectrum = fft.forwardReal(frames[i]);

                // compute magnitude spectrum
                dVector<Type> magnitude = computeMagnitude(spectrum);

                // store magnitude spectrum in spectrogram
                spectrogram[i] = magnitude;
            }

            return spectrogram;
        }

        // Function to plot the frequency spectrum of the input signal
        void plotFrequencySpectrum(const dVector<Type>& inputSignal) {

            // Validate input signal
            validateInputSignal(inputSignal);

            // Apply window function to the entire signal
            dVector<Type> windowedSignal = inputSignal;
            applyWindowFunction(windowedSignal);

            // Compute FFT
            dVectorComplex<std::complex<Type>> spectrum = fft.forwardReal(windowedSignal);

            // Compute magnitude spectrum
            dVector<Type> magnitude = computeMagnitude(spectrum);

            // Plot the magnitude spectrum using your preferred plotting library
            // Example: You can print the magnitude values to the console for now
            for (size_t i = 0; i < magnitude.getSize(); ++i) {
                std::cout << "Frequency bin " << i << ": " << magnitude[i] << std::endl;
            }

            // After obtaining the magnitude spectrum, you can use your preferred plotting library
            // to visualize it (e.g., Matplotlib in Python, or plotting libraries in C++)
        }

    private:
        int fftSize; // size of the fft window
        dVector<Type> fftWindow; // fft window function
        dFft<Type> fft; // fft object for computing fft
        dWindowFunc<Type> windowFunc; // window function object
        size_t frameSize; // size of each analysis frame
        size_t hopSize;   // hop size between consecutive frames
        double samplingRate; // sampling rate of the input signal
        int windowFunctionType; // type of window function (e.g., hamming, hann, etc.)

        // private helper functions
        void initializeFFT(size_t fftSize) {
            this->fftSize = fftSize;

            // initialize FFT object
            fft = DFft<Type>();

            // generate FFT window function
            generateWindow(fftSize);
        }

        void applyWindowFunction(dVector<Type>& signal) {

            // check if the signal size matches the window size
            if (signal.getSize() != fftSize) {
                throw std::invalid_argument("Signal size does not match FFT window size.");
            }

            // apply the window function to the signal
            for (size_t i = 0; i < fftSize; ++i) {
                signal[i] *= fftWindow[i];
            }
        }

        dVector<dVector<Type>> splitIntoFrames(const dVector<Type>& inputSignal) {

            // Check if input signal size is less than or equal to frame size
            if (inputSignal.getSize() <= frameSize) {
                throw std::invalid_argument("Input signal size is less than or equal to frame size.");
            }

            // Calculate number of frames
            size_t numFrames = 1 + (inputSignal.getSize() - frameSize) / hopSize;

            // Initialize vector of vectors to store frames
            dVector<dVector<Type>> frames(numFrames);

            // Populate frames
            for (size_t i = 0; i < numFrames; ++i) {
                size_t startIdx = i * hopSize;
                size_t endIdx = startIdx + frameSize;

                // Extract frame from input signal
                frames[i] = inputSignal.subVector(startIdx, endIdx);
            }

            return frames;
        }

        void validateInputSignal(const dVector<Type>& inputSignal) {

            // check if the input signal is empty
            if (inputSignal.getSize() == 0) {
                throw std::invalid_argument("Input signal is empty.");
            }

            // check if the size of the input signal is less than or equal to the FFT size
            if (inputSignal.getSize() <= fftSize) {
                throw std::invalid_argument("Input signal size is less than or equal to FFT size.");
            }
        }

        void preprocessSignal(dVector<Type>& inputSignal) {

            // normalize the input signal to the range [0, 1]
            inputSignal = dDspUtils<Type>::normalizeSignal(inputSignal, Type(0), Type(1));

            // zero-pad the input signal to match the FFT window size
            size_t originalSize = inputSignal.getSize();
            if (originalSize < fftSize) {
                inputSignal.resize(fftSize, Type(0));
            }
            else if (originalSize > fftSize) {
                // trim the input signal to match the FFT window size
                inputSignal.resize(fftSize);
            }
        }

        //------------------need to add a switch case for multiple window function types--------------
        void generateWindow(size_t size) {

            // generate the FFT window function
            fftWindow = DWindowFunc<Type>::hamming(size);
        }

        void processSpectralData(dVector<dVectorComplex<std::complex<Type>>>& frames) {

            // perform spectral processing on each frame
            for (size_t i = 0; i < frames.getSize(); ++i) {
                // apply FFT on the frame
                dVectorComplex<std::complex<Type>> spectrum = fft.forwardReal(frames[i]);

                // you can add additional processing steps here based on your requirements
                // example: Apply filtering, feature extraction, etc.

                // compute magnitude spectrum from the complex spectrum
                dVector<Type> magnitude = computeMagnitude(spectrum);

                // example additional processing: Smoothing (moving average)
                // you may replace this with a more sophisticated filter
                magnitude = dDspUtils<Type>::movingAverage(magnitude, 5); // smooth with a window size of 5

                // store the processed magnitude spectrum or do further processing as needed
                frames[i] = magnitude;
            }
        }
    };
}