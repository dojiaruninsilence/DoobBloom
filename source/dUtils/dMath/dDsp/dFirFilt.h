#pragma once

#include "dUtils/dMath/dDsp/dWindowFunc.h"

#include "dUtils/dMath/dGeneralMath/dFilterDesign.h"
#include "dUtils/dMath/dGeneralMath/dVector.h"

namespace doob {
    enum class FilterType {
        LOW_PASS,
        HIGH_PASS,
        BAND_PASS,
        BAND_STOP
    };

    enum class FilterDesignMethod {
        WINDOWING,
        FREQUENCY_SAMPLING,
        PARKS_MCCLELLAN
    };

    template <typename Type>
    class dFirFilt {
    public:
        // constructor
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

        // destructor
        ~dFirFilt() {}

        // method to apply the fir filter to an input signal
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
        // coefficient calculation method
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
            }

            // apply window to ideal response
            for (size_t n = 0; n < m_filterLength; ++n) {
                m_coefficients.push_back(window[n] * idealResponse[n]);
            }
        }

        // method to initialize filter state
        void initializeFilterState() {

            // initialize the filter state vector with zeros
            m_filterState.resize(m_filterLength, Type(0));
        }

        // method to update filter state
        void updateFilterState(Type latest_input_sample) {

            // shift existing filter state to the left
            for (size_t i = m_filterLength - 1; i > 0; --i) {
                m_filterState[i] = m_filterState[i - 1];
            }

            // update the first element of the filter state with the latest input sample
            m_filterState[0] = latest_input_sample;
        }

        // method to apply the filter to a single input sample
        Type applyFilter(const DMath::DVector<Type>& inputSignal, size_t index) {
            // ensure that the current index is within the valid range
            if (index >= m_filterLength || index >= inputSignal.getSize()) {
                throw std::out_of_range("Index out of range in applyFilter function");
            }

            Type filteredValue = Type(0);

            // apply the convolution operation
            for (size_t i = 0; i < m_filterLength; ++i) {
                // ensure that the index is within the valid range for the filter state
                size_t stateIndex = index + (m_filterLength - 1) - i;
                if (stateIndex >= m_filterLength) {
                    throw std::out_of_range("Filter state index out of range in applyFilter function");
                }

                filteredValue += m_coefficients[i] * m_filterState[stateIndex];
            }

            return filteredValue;
        }
    };
}