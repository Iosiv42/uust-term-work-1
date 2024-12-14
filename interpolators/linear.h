#pragma once
#include <cmath>
#include <sys/types.h>
#include <vector>
#include "interpolator.h"

namespace Interpolators {
    // Линейный интерполятор
    class Linear : public Interpolator {
    public:
        Linear() {}

        virtual double interpolate(vector<double> &samples, double x);
        virtual vector<double> interpolate(
            vector<double> &samples,
            double start, double stop, double step
        );
    };
}
