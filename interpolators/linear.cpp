#include "linear.h"
#include <cstdio>
using namespace Interpolators;

double Linear::interpolate(vector<double> &samples, double x) {
    int fx = floor(x);
    double y1 = samples[fx], y2 = samples[fx + 1];
    return (y2 - y1)*(x - fx) + y1;
}

vector<double> Linear::interpolate(
    vector<double> &samples,
    double start,
    double stop,
    double step
) {
    vector<double> interpolated;

    double x = start;
    while (x < stop) {
        interpolated.push_back(this->interpolate(samples, x));
        x += step;
    }
    
    return interpolated;
}
