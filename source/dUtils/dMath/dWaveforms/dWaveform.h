#pragma once

namespace doob {
    class dWaveform {
    public:
        virtual ~dWaveform() {}
        virtual double generate(double t, double frequency, double amplitude, double phase) = 0;
    };
}