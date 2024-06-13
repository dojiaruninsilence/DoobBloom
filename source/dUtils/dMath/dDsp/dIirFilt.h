#pragma once

#include "dUtils/dMath/dGeneralMath/dExpLogFunctions.h"
#include "dUtils/dMath/dGeneralMath/dMathDefines.h"
#include "dUtils/dMath/dGeneralMath/dTrig.h"
#include "dUtils/dMath/dGeneralMath/dVector.h"
#include "dUtils/dMath/dGeneralMath/dVectorComplex.h"

namespace doob {
    
    // @enum filterType
    // @brief enum to define different types of filters.
    enum class FilterType {
        LOW_PASS,
        HIGH_PASS,
        BAND_PASS,
        BAND_STOP
    };

    template <typename Type>
    class dIirFilt {
    public:
        // @brief constructor to initialize the filter with given type, cutoff frequency, and resonance.
        // @param type the type of the filter.
        // @param cutoffFreq the cutoff frequency of the filter.
        // @param resonance the resonance of the filter.
        dIirFilt(FilterType type, Type cutoffFreq, Type resonance) : filterType(type) {

            // initialize filter coefficients and state variables
            calculateCoefficients(type, cutoffFreq, resonance);
            xHistory.resize(bCoefficients.size() - 1, Type(0)); // resize xHistory to match the filter order
            yHistory.resize(aCoefficients.size() - 1, Type(0)); // resize yHistory to match the filter order
        }

        // @brief Destructor
        ~dIirFilt() {}

        // @brief method to set filter coefficients based on type, cutoff frequency, and resonance.
        // @param type the type of the filter.
        // @param cutoffFreq the cutoff frequency of the filter.
        // @param resonance the resonance of the filter.
        void setFilterCoefficients(FilterType type, Type cutoffFreq, Type resonance) {

            filterType = type;
            calculateCoefficients(type, cutoffFreq, resonance);
            // resize the history vectors to match the filter order
            xHistory.resize(bCoefficients.size() - 1, Type(0));
            yHistory.resize(aCoefficients.size() - 1, Type(0));
        }

        // @brief method to process a single sample through the filter.
        // @param input the input sample.
        // @return the filtered output sample.
        Type processSample(Type input) {

            // update the filter state with the new input sample
            updateFilterState(input);
            // calculate the output sample based on the updated filter state
            Type output = calculateOutputSample(input);
            // return the calculated output sample
            return output;
        }

        // @brief method to process a block of samples through the filter.
        // @param input the vector of input samples.
        // @return a vector of filtered output samples.
        dVector<Type> processBlock(const dVector<Type>& input) {
            // create a vector to store the output samples
            dVector<Type> outputBlock(input.size());

            // process each sample in the input block
            for (size_t i = 0; i < input.size(); ++i) {
                // process the current input sample through the filter
                Type outputSample = processSample(input[i]);
                // store the output sample in the output block
                outputBlock[i] = outputSample;
            }

            // return the vector containing the output samples
            return outputBlock;
        }

        //------------------------------------------------------------------------------------------------------
        // method to analyze the filter's frequency response -- come back to when we start workin on all this
        void analyzeFreqResponse();

    private:
        // @brief calculate the output sample using the difference equation.
        // @param input the input sample.
        // @return the output sample.
        Type calculateOutputSample(Type input) {

            // calculate the output sample using the difference equation
            Type output = static_cast<Type>(0.0);
            for (size_t i = 0; i < bCoefficients.size(); ++i) {
                output += bCoefficients[i] * xHistory[i];
            }
            for (size_t i = 1; i < aCoefficients.size(); ++i) {
                output -= aCoefficients[i] * yHistory[i];
            }

            return output;
        }

        // @brief update the filter state with the new input sample.
        // @param input the input sample.
        void updateFilterState(Type input) {

            // shift the input history
            for (size_t i = xHistory.size() - 1; i > 0; --i) {
                xHistory[i] = xHistory[i - 1];
            }
            xHistory[0] = input;

            // calculate the output sample
            Type output = calculateOutputSample(input);

            // shift the output history
            for (size_t i = yHistory.size() - 1; i > 0; --i) {
                yHistory[i] = yHistory[i - 1];
            }
            yHistory[0] = output;
        }

        // @brief Calculate the filter coefficients based on filter type, cutoff frequency, and resonance.
        // @param type The type of the filter.
        // @param cutoffFreq The cutoff frequency of the filter.
        // @param resonance The resonance of the filter.
        void calculateCoefficients(FilterType type, Type cutoffFreq, Type resonance) {
            // calc coefficients based on filter type, cutoff freq, and resonance
            switch (type) {
            case DDsp::FilterType::LOW_PASS:
                bCoefficients = calculateLowPassCoefficients(cutoffFreq, resonance);
                aCoefficients = calculateDenominatorCoefficients(cutoffFreq, resonance);
                break;
            case DDsp::FilterType::HIGH_PASS:
                bCoefficients = calculateHighPassCoefficients(cutoffFreq, resonance);
                aCoefficients = calculateDenominatorCoefficients(cutoffFreq, resonance);
                break;
            case DDsp::FilterType::BAND_PASS:
                bCoefficients = calculateBandPassCoefficients(cutoffFreq, resonance);
                aCoefficients = calculateDenominatorCoefficients(cutoffFreq, resonance);
                break;
            case DDsp::FilterType::BAND_STOP:
                bCoefficients = calculateBandStopCoefficients(cutoffFreq, resonance);
                aCoefficients = calculateDenominatorCoefficients(cutoffFreq, resonance);
                break;
            default:
                // Log an error if the filter type is unknown
                reportError(errorLevel::D_ERROR, errorCode::INVALID_ARGUMENT, "Unknown filter type.", __FILE__, __LINE__);
            }
        }

        // @brief calculate the low-pass filter coefficients.
        // @param cutoffFreq the cutoff frequency.
        // @param resonance the resonance.
        // @return a vector of filter coefficients.
        dVector<Type> calculateLowPassCoefficients(Type cutoffFreq, Type resonance) {

            // butterworth filter design
            const int order = 4; // filter order (adjust as needed)
            const double sampleRate = 44100.0; // sample rate (adjust as needed)

            // calculate normalized cutoff frequency
            const double omegaC = 2.0 * D_PI * static_cast<double>(cutoffFreq) / sampleRate;

            // calculate poles of the Butterworth filter
            dVectorComplex<std::complex<double>> poles(order);
            for (int k = 0; k < order; ++k) {
                double realPart = -dTrig<double>::sin((2 * k + 1) * D_PI / (2.0 * order));
                double imagPart = dTrig<double>::cos((2 * k + 1) * D_PI / (2.0 * order));
                poles[k] = std::complex<double>(realPart, imagPart);
            }

            // calculate filter coefficients using poles
            dVector<Type> coefficients(order + 1);
            coefficients[0] = static_cast<Type>(dExpLogFuntions<Type>::pow(omegaC, order)); // gain coefficient
            for (int i = 1; i <= order; ++i) {
                Type prod = static_cast<Type>(1.0);
                for (int j = 0; j < order; ++j) {
                    if (i != j + 1) {
                        prod *= omegaC - poles[j].real();
                    }
                }
                coefficients[i] = prod;
            }

            return coefficients;
        }

        // @brief calculate the high-pass filter coefficients.
        // @param cutoffFreq the cutoff frequency.
        // @param resonance the resonance.
        // @return a vector of filter coefficients.
        dVector<Type> calculateHighPassCoefficients(Type cutoffFreq, Type resonance) {
            // butterworth filter design
            const int order = 4; // filter order (adjust as needed)
            const double sampleRate = 44100.0; // sample rate (adjust as needed)

            // calculate normalized cutoff frequency
            const double omegaC = 2.0 * D_PI * static_cast<double>(cutoffFreq) / sampleRate;

            // calculate poles of the Butterworth filter
            dVectorComplex<std::complex<double>> poles(order);
            for (int k = 0; k < order; ++k) {
                double realPart = -dTrig<double>::sin((2 * k + 1) * D_PI / (2.0 * order));
                double imagPart = dTrig<double>::cos((2 * k + 1) * D_PI / (2.0 * order));
                poles[k] = std::complex<double>(realPart, imagPart);
            }

            // calculate filter coefficients using poles
            dVector<Type> coefficients(order + 1);
            coefficients[0] = static_cast<Type>(dExpLogFunctions<Type>::pow(omegaC, order)); // gain coefficient
            for (int i = 1; i <= order; ++i) {
                Type prod = static_cast<Type>(1.0);
                for (int j = 0; j < order; ++j) {
                    if (i != j + 1) {
                        prod *= omegaC;
                        prod /= (omegaC - poles[j].real());
                    }
                }
                coefficients[i] = prod;
            }

            return coefficients;
        }

        // @brief calculate the band-pass filter coefficients.
        // @param cutoffFreq the cutoff frequency.
        // @param resonance the resonance.
        // @return a vector of filter coefficients.
        dVector<Type> calculateBandPassCoefficients(Type cutoffFreq, Type resonance) {
            // butterworth filter design
            const int order = 4; // filter order (adjust as needed)
            const double sampleRate = 44100.0; // sample rate (adjust as needed)

            // calculate normalized cutoff frequency
            const double omegaC = 2.0 * D_PI * static_cast<double>(cutoffFreq) / sampleRate;

            // calculate poles of the Butterworth filter
            dVectorComplex<std::complex<double>> poles(order * 2);
            for (int k = 0; k < order * 2; ++k) {
                double realPart = -dTrig<double>::sin((2 * k + 1) * D_PI / (2.0 * order * 2));
                double imagPart = dTrig<double>::cos((2 * k + 1) * D_PI / (2.0 * order * 2));
                poles[k] = std::complex<double>(realPart, imagPart);
            }

            // calculate filter coefficients using poles
            dVector<Type> coefficients(order * 2 + 1);
            coefficients[0] = static_cast<Type>(1.0); // gain coefficient
            for (int i = 1; i <= order * 2; ++i) {
                Type prod = static_cast<Type>(1.0);
                for (int j = 0; j < order * 2; ++j) {
                    if (i != j + 1) {
                        prod *= omegaC;
                        prod /= (omegaC - poles[j].real());
                    }
                }
                coefficients[i] = prod;
            }

            return coefficients;
        }

        // @brief calculate the band-stop filter coefficients.
        // @param cutoffFreq the cutoff frequency.
        // @param resonance the resonance.
        // @return a vector of filter coefficients.
        dVector<Type> calculateBandStopCoefficients(Type cutoffFreq, Type resonance) {
            // butterworth filter design
            const int order = 4; // filter order (adjust as needed)
            const double sampleRate = 44100.0; // sample rate (adjust as needed)

            // calculate normalized cutoff frequency
            const double omegaC = 2.0 * D_PI * static_cast<double>(cutoffFreq) / sampleRate;

            // calculate poles of the Butterworth filter
            dVectorComplex<std::complex<double>> poles(order * 2);
            for (int k = 0; k < order * 2; ++k) {
                double realPart = -dTrig<double>::sin((2 * k + 1) * D_PI / (2.0 * order * 2));
                double imagPart = dTrig<double>::cos((2 * k + 1) * D_PI / (2.0 * order * 2));
                poles[k] = std::complex<double>(realPart, imagPart);
            }

            // calculate filter coefficients using poles
            dVector<Type> coefficients(order * 2 + 1);
            coefficients[0] = static_cast<Type>(dExpLogFunctions<Type>::pow(omegaC, order * 2)); // Gain coefficient
            for (int i = 1; i <= order * 2; ++i) {
                Type prod = static_cast<Type>(1.0);
                for (int j = 0; j < order * 2; ++j) {
                    if (i != j + 1) {
                        prod *= omegaC - poles[j].real();
                    }
                }
                coefficients[i] = prod;
            }

            return coefficients;
        }

        // @brief calculate the denominator coefficients for the filter.
        // @param cutoffFreq the cutoff frequency.
        // @param resonance the resonance.
        // @return a vector of denominator coefficients.
        dVector<Type> calculateDenominatorCoefficients(Type cutoffFreq, Type resonance) {
            // butterworth filter design
            const int order = 4; // Filter order (adjust as needed)
            const double sampleRate = 44100.0; // Sample rate (adjust as needed)

            // calculate normalized cutoff frequency
            const double omegaC = 2.0 * D_PI * static_cast<double>(cutoffFreq) / sampleRate;

            // calculate poles of the Butterworth filter
            dVectorComplex<std::complex<double>> poles(order * 2);
            for (int k = 0; k < order * 2; ++k) {
                double realPart = -dTrig<double>::sin((2 * k + 1) * D_PI / (2.0 * order * 2));
                double imagPart = dTrig<double>::cos((2 * k + 1) * D_PI / (2.0 * order * 2));
                poles[k] = std::complex<double>(realPart, imagPart);
            }

            // calculate filter coefficients using poles
            dVector<Type> coefficients(order * 2 + 1);
            coefficients[0] = static_cast<Type>(1.0); // gain coefficient
            for (int i = 1; i <= order * 2; ++i) {
                Type prod = static_cast<Type>(1.0);
                for (int j = 0; j < order * 2; ++j) {
                    if (i != j + 1) {
                        prod *= omegaC - poles[j].real();
                    }
                }
                coefficients[i] = prod;
            }

            return coefficients;
        }

        // filter coefficients
        dVector<Type> bCoefficients;
        dVector<Type> aCoefficients;

        // state variables for the filter
        dVector<Type> xHistory; // input
        dVector<Type> yHistory; // output

        // filter type
        FilterType filterType;
    };
}