#pragma once
#include "interpolator.h"

namespace Interpolators {
    // Интерполятор Фурье
    class Fourier : public Interpolator {
    public:
        Fourier() {}

        virtual double interpolate(vector<double> &samples, double x);
        virtual vector<double> interpolate(
            vector<double> &samples,
            double start, double stop, double step
        );
    };
}
