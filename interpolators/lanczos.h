#pragma once
#include <vector>
#include "interpolator.h"

namespace Interpolators {
    // Интерполятор Ланцоша
    class Lanczos : public Interpolator {
    public:
        Lanczos() {}

        virtual double interpolate(vector<double> &samples, double x);
        virtual vector<double> interpolate(
            vector<double> &samples,
            double start, double stop, double step
        );
    };
}
