#pragma once
#include <vector>
using namespace std;

namespace Interpolators {
    class Interpolator {
    public:
        virtual double interpolate(vector<double> &samples, double x) = 0;
        virtual vector<double> interpolate(
                vector<double> &samples,
                double start, double stop, double step
        ) = 0;
        virtual ~Interpolator() {}
    };
}
