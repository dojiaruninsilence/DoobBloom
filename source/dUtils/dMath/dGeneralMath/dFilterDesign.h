#pragma once

#include "dUtils/dMath/dGeneralMath/dVector.h"
#include "dUtils/dMath/dGeneralMath/dMathDefines.h"
#include "dUtils/dMath/dGeneralMath/dTrig.h"

namespace doob {
    template <typename Type>
    class dFilterDesign {
    public:
        // design a low pass filter using specified parameters
        static dVector<Type> designLowPassFilter(
            Type cutoffFrequency, size_t filterOrder, Type samplingFrequency) {

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

            return filterCoefficients;
        }

        // Design a high-pass filter using specified parameters
        static dVector<Type> designHighPassFilter(
            Type cutoffFrequency, size_t filterOrder, Type samplingFrequency) {

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

            return filterCoefficients;
        }

        // design a band pass filter using specified parameters
        static dVector<Type> designBandPassFilter(
            Type lowCutoffFrequency, Type highCutoffFrequency, 
            size_t filterOrder, Type samplingFrequency) {

            Type lowwc = (Type(2.0) * lowCutoffFrequency) / samplingFrequency;
            Type highwc = (Type(2.0) * highCutoffFrequency) / samplingFrequency;

            dVector<Type> lowPassCoefficients = designLowPassFilter(highCutoffFrequency, filterOrder, samplingFrequency);

            dVector<Type> highPassCoefficients = designHighPassFilter(lowCutoffFrequency, filterOrder, samplingFrequency);

            dVector<Type> bandPassCoefficients(filterOrder + 1);
            for (size_t n = 0; n <= filterOrder; ++n) {
                bandPassCoefficients[n] = lowPassCoefficients[n] + highPassCoefficients[n];
            }

            return bandPassCoefficients;
        }


        // design a band stop filter using specified parameters
        static dVector<Type> designBandStopFilter(
            Type lowCutoffFrequency, Type highCutoffFrequency, 
            size_t filterOrder, Type samplingFrequency) {
            Type lowws = (Type(2.0) * lowStopFrequency) / samplingFrequency;
            Type highws = (Type(2.0) * highStopFrequency) / samplingFrequency;

            dVector<Type> highPassCoefficients = designHighPassFilter(lowStopFrequency, filterOrder, samplingFrequency);

            dVector<Type> lowPassCoefficients = designLowPassFilter(highStopFrequency, filterOrder, samplingFrequency);

            dVector<Type> bandStopCoefficients(filterOrder + 1);
            for (size_t n = 0; n <= filterOrder; ++n) {
                bandStopCoefficients[n] = highPassCoefficients[n] + lowPassCoefficients[n];
            }

            return bandStopCoefficients;
        }
    };
}