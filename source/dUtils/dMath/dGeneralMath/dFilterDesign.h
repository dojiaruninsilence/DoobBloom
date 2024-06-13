#pragma once

#include "dUtils/dDiagnostics/dErrKit.h"

#include "dUtils/dMath/dGeneralMath/dVector.h"
#include "dUtils/dMath/dGeneralMath/dMathDefines.h"
#include "dUtils/dMath/dGeneralMath/dTrig.h"

namespace doob {

    // class template for designing various types of digital filters
    template <typename Type>
    class dFilterDesign {
    public:
        // design a low-pass filter using specified parameters
        // cutoffFrequency: the cutoff frequency of the filter
        // filterOrder: the order of the filter (number of taps - 1)
        // samplingFrequency: the sampling frequency of the signal
        static dVector<Type> designLowPassFilter(
            Type cutoffFrequency, size_t filterOrder, Type samplingFrequency) {

            if (cutoffFrequency <= 0 || samplingFrequency <= 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR, 
                    "Cutoff frequency and sampling frequency must be positive.", __FILE__, __LINE__);
            }

            if (cutoffFrequency >= samplingFrequency / 2) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR, 
                    "Cutoff frequency must be less than half the sampling frequency.", __FILE__, __LINE__);
            }

            Type wc = (Type(2.0) * cutoffFrequency) / samplingFrequency;

            dVector<Type> filterCoefficients(filterOrder + 1);
            Type sum = Type(0);
            for (size_t n = 0; n <= filterOrder; ++n) {
                Type hn = (n == filterOrder / 2) ? wc / Type(D_PI) : dTrig<Type>::sin(wc * (n - filterOrder / 2)) / (Type(D_PI) * (n - filterOrder / 2));
                filterCoefficients[n] = hn * Type(0.54) - Type(0.46) * dTrig<Type>::cos(Type(2.0) * Type(D_PI) * n / Type(filterOrder));
                sum += filterCoefficients[n];
            }

            for (size_t n = 0; n <= filterOrder; ++n) {
                filterCoefficients[n] /= sum;
            }

            DB_INFO("Low-pass filter designed with cutoff frequency: {}, filter order: {}, sampling frequency: {}",
                cutoffFrequency, filterOrder, samplingFrequency);

            return filterCoefficients;
        }

        // design a high-pass filter using specified parameters
        // cutoffFrequency: the cutoff frequency of the filter
        // filterOrder: the order of the filter (number of taps - 1)
        // samplingFrequency: the sampling frequency of the signal
        static dVector<Type> designHighPassFilter(
            Type cutoffFrequency, size_t filterOrder, Type samplingFrequency) {

            if (cutoffFrequency <= 0 || samplingFrequency <= 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Cutoff frequency and sampling frequency must be positive.", __FILE__, __LINE__);
            }

            if (cutoffFrequency >= samplingFrequency / 2) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Cutoff frequency must be less than half the sampling frequency.", __FILE__, __LINE__);
            }

            Type wc = (Type(2.0) * cutoffFrequency) / samplingFrequency;

            dVector<Type> filterCoefficients(filterOrder + 1);
            Type sum = Type(0);
            for (size_t n = 0; n <= filterOrder; ++n) {
                Type hn = (n == filterOrder / 2) ? Type(1.0) - wc / Type(D_PI) : -dTrig<Type>::sin(wc * (n - filterOrder / 2)) / (Type(D_PI) * (n - filterOrder / 2));
                filterCoefficients[n] = hn * Type(0.54) - Type(0.46) * dTrig<Type>::cos(Type(2.0) * Type(D_PI) * n / Type(filterOrder));
                sum += filterCoefficients[n];
            }

            for (size_t n = 0; n <= filterOrder; ++n) {
                filterCoefficients[n] /= sum;
            }

            for (size_t n = 0; n <= filterOrder; ++n) {
                filterCoefficients[n] = -filterCoefficients[n];
            }
            filterCoefficients[filterOrder / 2] += Type(1.0);

            DB_INFO("High-pass filter designed with cutoff frequency: {}, filter order: {}, sampling frequency: {}",
                cutoffFrequency, filterOrder, samplingFrequency);

            return filterCoefficients;
        }

        // design a band-pass filter using specified parameters
        // lowCutoffFrequency: the lower cutoff frequency of the filter
        // highCutoffFrequency: the upper cutoff frequency of the filter
        // filterOrder: the order of the filter (number of taps - 1)
        // samplingFrequency: the sampling frequency of the signal
        static dVector<Type> designBandPassFilter(
            Type lowCutoffFrequency, Type highCutoffFrequency, 
            size_t filterOrder, Type samplingFrequency) {

            if (lowCutoffFrequency <= 0 || highCutoffFrequency <= 0 || samplingFrequency <= 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Cutoff frequency and sampling frequency must be positive.", __FILE__, __LINE__);
            }

            if (lowCutoffFrequency >= highCutoffFrequency) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Low cutoff frequency must be less than high cutoff frequency.", __FILE__, __LINE__);
            }

            if (highCutoffFrequency >= samplingFrequency / 2) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "High cutoff frequency must be less than half the sampling frequency.", __FILE__, __LINE__);
            }

            Type lowwc = (Type(2.0) * lowCutoffFrequency) / samplingFrequency;
            Type highwc = (Type(2.0) * highCutoffFrequency) / samplingFrequency;

            dVector<Type> lowPassCoefficients = designLowPassFilter(highCutoffFrequency, filterOrder, samplingFrequency);

            dVector<Type> highPassCoefficients = designHighPassFilter(lowCutoffFrequency, filterOrder, samplingFrequency);

            dVector<Type> bandPassCoefficients(filterOrder + 1);
            for (size_t n = 0; n <= filterOrder; ++n) {
                bandPassCoefficients[n] = lowPassCoefficients[n] + highPassCoefficients[n];
            }

            DB_INFO("Band-pass filter designed with low cutoff frequency: {}, high cutoff frequency: {}, filter order: {}, sampling frequency: {}",
                lowCutoffFrequency, highCutoffFrequency, filterOrder, samplingFrequency);

            return bandPassCoefficients;
        }


        // design a band-stop filter using specified parameters
        // lowCutoffFrequency: the lower cutoff frequency of the filter
        // highCutoffFrequency: the upper cutoff frequency of the filter
        // filterOrder: the order of the filter (number of taps - 1)
        // samplingFrequency: the sampling frequency of the signal
        static dVector<Type> designBandStopFilter(
            Type lowCutoffFrequency, Type highCutoffFrequency, 
            size_t filterOrder, Type samplingFrequency) {

            if (lowCutoffFrequency <= 0 || highCutoffFrequency <= 0 || samplingFrequency <= 0) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Cutoff frequency and sampling frequency must be positive.", __FILE__, __LINE__);
            }

            if (lowCutoffFrequency >= highCutoffFrequency) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "Low cutoff frequency must be less than high cutoff frequency.", __FILE__, __LINE__);
            }

            if (highCutoffFrequency >= samplingFrequency / 2) {
                reportError(errorLevel::D_ERROR, errorCode::INPUT_VALIDATION_ERROR,
                    "High cutoff frequency must be less than half the sampling frequency.", __FILE__, __LINE__);
            }

            Type lowws = (Type(2.0) * lowStopFrequency) / samplingFrequency;
            Type highws = (Type(2.0) * highStopFrequency) / samplingFrequency;

            dVector<Type> highPassCoefficients = designHighPassFilter(lowStopFrequency, filterOrder, samplingFrequency);

            dVector<Type> lowPassCoefficients = designLowPassFilter(highStopFrequency, filterOrder, samplingFrequency);

            dVector<Type> bandStopCoefficients(filterOrder + 1);
            for (size_t n = 0; n <= filterOrder; ++n) {
                bandStopCoefficients[n] = highPassCoefficients[n] + lowPassCoefficients[n];
            }

            DB_INFO("Band-stop filter designed with low cutoff frequency: {}, high cutoff frequency: {}, filter order: {}, sampling frequency: {}",
                lowCutoffFrequency, highCutoffFrequency, filterOrder, samplingFrequency);

            return bandStopCoefficients;
        }
    };
}