#include <cstdio>
#include <vector>
#define _USE_MATH_DEFINES
#include "lanczos.h"
#include <cmath>
using namespace Interpolators;

// Функция нормализованая sinc
inline double sinc(double x) {
    if (x == 0) {
        return 1.;
    }
    return sin(M_PI * x) / (M_PI * x);
}

// Ядро Ланцоша
inline double lanczos_kernel(double x, uint a) {
    if (-double(a) < x && x < double(a)) {
        return sinc(x) * sinc(x / a);
    }
    return 0.;
}

double Lanczos::interpolate(vector<double> &samples, double x) {
    uint a = 3;
    double conv = 0;
    // Делаем свертку
    for (int i = floor(x) - a + 1; i <= floor(x) + a; i++) {
        // Если индекс вне массива, то 0
        double s = (0 <= i && i < samples.size()) ? samples[i] : 0.;
        conv += s * lanczos_kernel(x - i, a);
    }

    return conv;
}

vector<double> Lanczos::interpolate(
    vector<double> &samples,
    double start, double stop, double step
) {
    vector<double> interpolated;
    for (double x = start; x < stop; x += step) {
        interpolated.push_back(this->interpolate(samples, x));
    }
    return interpolated;
}
