#pragma once

#include "dUtils/dDiagnostics/dErrKit.h"

#include "dUtils/dMath/dDsp/dWindowFunc.h"

#include "dUtils/dMath/dGeneralMath/dFilterDesign.h"
#include "dUtils/dMath/dGeneralMath/dVector.h"

namespace doob {

    // @enum FilterType
    // @brief Enumeration for the type of FIR filter.
    enum class FilterType {
        LOW_PASS,
        HIGH_PASS,
        BAND_PASS,
        BAND_STOP
    };

    // @enum FilterDesignMethod
    // @brief Enumeration for the method used to design the FIR filter.
    enum class FilterDesignMethod {
        WINDOWING,
        FREQUENCY_SAMPLING,
        PARKS_MCCLELLAN
    };

    // @class dFirFilt
    // @brief Class for designing and applying FIR filters.
    // @tparam Type The data type for filter coefficients and signal processing.
    template <typename Type>
    class dFirFilt {
    public:
        // @brief Constructor for the dFirFilt class.
        // @param coefficients Initial filter coefficients.
        // @param filterLength Length of the filter.
        // @param filterType Type of the filter(low - pass, high - pass, etc.).
        // @param samplingFrequency Sampling frequency of the signal.
        // @param designMethod Method used to design the filter.
        dFirFilt(
            const dVector<Type>& coefficients,
            size_t filterLength,
            FilterType filterType,
            Type samplingFrequency,
            FilterDesignMethod designMethod)
            : m_coefficients(coefficients),
            m_filterLength(filterLength),
            m_filterType(filterType),
            m_samplingFrequency(samplingFrequency),
            m_designMethod(designMethod) {

            // Calculate coefficients and initialize filter state
            calculateCoefficients();
            initializeFilterState();
        }

        // @brief Destructor for the dFirFilt class.
        ~dFirFilt() {}

        // @brief Method to apply the FIR filter to an input signal.
        // @param inputSignal The input signal to be filtered.
        // @return The filtered output signal.
        dVector<Type> filterSignal(const dVector<Type>& inputSignal) {

            // create a vector to store the filtered output signal
            dVector<Type> outputSignal;

            // interate over each sample in the input signal
            for (size_t i = 0; i < inputSignal.getSize(); ++i) {
                // apply the filter to the current input sample and add the filtered sample to the output signal
                outputSignal.push_back(applyFilter(inputSignal, i));

                // update the filter state with the latest input sample
                updateFilterState(inputSignal[i]);
            }

            return outputSignal;
        }
    private:
        // private member variables for filter coefficients, state, ect
        dVector<Type> m_coefficients;
        dVector<Type> m_filterState;
        size_t m_filterLength;
        FilterType m_filterType;
        Type m_samplingFrequency;
        FilterDesignMethod m_designMethod;

        // private methods
        // @brief Method to calculate filter coefficients.
        void calculateCoefficients() {
            // clear existing coefficients
            m_coefficients.resize(0);

            // calculate coefficients using hamming window function
            dVector<Type> window = dWindowFunc::hamming(m_filterLength);

            // calculate ideal response based on filter type
            dVector<Type> idealResponse;
            switch (m_filterType) {
            case FilterType::LOW_PASS:
                // generate ideal low-pass filter response using designLowPassFilter function
                idealResponse = dFilterDesign<Type>::designLowPassFilter(
                    cutoffFrequency, m_filterLength, m_samplingFrequency);
                break;
            case FilterType::HIGH_PASS:
                // generate ideal high-pass filter response using designHighPassFilter function
                idealResponse = dFilterDesign<Type>::designHighPassFilter(
                    cutoffFrequency, m_filterLength, m_samplingFrequency);
                break;
            case FilterType::BAND_PASS:
                // generate ideal band-pass filter response using designBandPassFilter function
                idealResponse = dFilterDesign<Type>::designBandPassFilter(
                    lowCutoffFrequency, highCutoffFrequency, m_filterLength, m_samplingFrequency);
                break;
            case FilterType::BAND_STOP:
                // generate ideal band-stop filter response using designBandStopFilter function
                idealResponse = dFilterDesign<Type>::designBandStopFilter(
                    lowStopFrequency, highStopFrequency, m_filterLength, m_samplingFrequency);
                break;
            default:
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Invalid filter type.", __FILE__, __LINE__);
                return;
            }

            // apply window to ideal response
            for (size_t n = 0; n < m_filterLength; ++n) {
                m_coefficients.push_back(window[n] * idealResponse[n]);
            }
        }

        // @brief Method to initialize the filter state.
        void initializeFilterState() {

            // initialize the filter state vector with zeros
            m_filterState.resize(m_filterLength, Type(0));
        }

        // @brief Method to update the filter state with the latest input sample.
        // @param latest_input_sample The latest input sample to update the filter state.
        void updateFilterState(Type latest_input_sample) {

            // shift existing filter state to the left
            for (size_t i = m_filterLength - 1; i > 0; --i) {
                m_filterState[i] = m_filterState[i - 1];
            }

            // update the first element of the filter state with the latest input sample
            m_filterState[0] = latest_input_sample;
        }

        // @brief Method to apply the filter to a single input sample.
        // @param inputSignal The input signal to be filtered.
        // @param index The current index of the input signal.
        // @return The filtered value of the current input sample.
        Type applyFilter(const DMath::DVector<Type>& inputSignal, size_t index) {
            // ensure that the current index is within the valid range
            if (index >= m_filterLength || index >= inputSignal.getSize()) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Index out of range in applyFilter function", __FILE__, __LINE__);
            }

            Type filteredValue = Type(0);

            // apply the convolution operation
            for (size_t i = 0; i < m_filterLength; ++i) {
                // ensure that the index is within the valid range for the filter state
                size_t stateIndex = index + (m_filterLength - 1) - i;
                if (stateIndex >= m_filterLength) {
                    reportError(errorLevel::D_ERROR, errorCode::OUT_OF_BOUNDS,
                        "Filter state index out of range in applyFilter function", __FILE__, __LINE__);
                }

                filteredValue += m_coefficients[i] * m_filterState[stateIndex];
            }

            return filteredValue;
        }

        // Placeholder variables for design functions
        Type cutoffFrequency = 0; // Example default value
        Type lowCutoffFrequency = 0; // Example default value
        Type highCutoffFrequency = 0; // Example default value
        Type lowStopFrequency = 0; // Example default value
        Type highStopFrequency = 0; // Example default value
    };
}