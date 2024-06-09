#pragma once

#include "dUtils/dMath/dWaveforms/dWaveform.h"

#include "dUtils/dMath/dGeneralMath/dTrig.h"
#include "dUtils/dMath/dGeneralMath/dMathDefines.h"

namespace doob {
    class dTriangleWave : public dWaveform {
    public:
        double generate(double t, double frequency, double amplitude, double phase) override {
            return amplitude * (2 / D_PI) * dTrig<double>::asin(dTrig<double>::sin(2 * D_PI * frequency * t + phase));
        }
    };
}