#pragma once

#include "dUtils/dMath/dWaveforms/dWaveform.h"

#include "dUtils/dMath/dGeneralMath/dTrig.h"
#include "dUtils/dMath/dGeneralMath/dMathDefines.h"

namespace doob {
    class dSawtoothWave : public dWaveform {
    public:
        double generate(double t, double frequency, double amplitude, double phase) override {
            return amplitude * (2 / D_PI) * dTrig<double>::atan(dTrig<double>::tan(D_PI * frequency * t + phase / 2));
        }
    };
}