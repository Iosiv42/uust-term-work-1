#define _USE_MATH_DEFINES
#include "fourier.h"
#include <cmath>
#include <complex>
#include <sys/types.h>
#include <vector>
using namespace std::complex_literals;
using namespace Interpolators;

// Преобразование Фурье. Пригодится если размер не идеальная степень двойки
vector<complex<double>> dft(vector<double> &x, uint start, uint stop, uint step) {
    uint N = (stop - start) / step;
    vector<complex<double>> X;
    for (uint k = 0; k < N; k++) {
        complex<double> sum = 0;
        for (uint n = 0; n < N; n++) {
            sum += x[start + n*step] * std::exp(-2*M_PI*1i*double(n*k) / double(N));
        }
        X.push_back(sum);
    }

    return X;
}

// Помошник для быстрого преобразования Фурье
vector<complex<double>> fft_helper(vector<double> &x, uint start, uint stop, uint step) {
    uint N = (stop - start + 1) / step;

    if (N == 1) {
        vector<complex<double>> X;
        X.push_back(x[start] + 0i);
        return X;
    }
    if (N % 2 != 0) {
        return dft(x, start, stop, step);
    }

    vector<complex<double>> X(N);
    vector<complex<double>>
        E = fft_helper(x, start, stop, step*2),
        O = fft_helper(x, start + 1, stop, step*2);
    for (uint k = 0; k < N/2; k++) {
        complex<double>
            a = E[k],
            b = std::exp(-2*M_PI*k*1i / double(N)) * O[k];
        X[k] = a + b;
        X[k + N/2] = a - b;
    }

    return X;
}

// Быстрое преобразование Фурье
inline vector<complex<double>> fft(vector<double> &x) {
    return fft_helper(x, 0, x.size(), 1);
}

// Обратное преобразование Фурье для одного значения
inline double idft_single(vector<complex<double>> X, double x) {
    uint N = X.size();

    double sum = 0;
    for (uint k = 0; k < N; k++) {
        complex<double> da = std::exp(2*M_PI*k*x*1i / double(N));
        sum += real(X[k] * da);
    }

    return sum / double(N);
}

inline double Fourier::interpolate(vector<double> &samples, double x) {
    return idft_single(fft(samples), x);
}

vector<double> Fourier::interpolate(
    vector<double> &samples,
    double start, double stop, double step
) {
    vector<complex<double>> X = fft(samples);
    vector<double> interpolated;
    uint N = samples.size();

    for (double n = start; n < stop; n += step) {
        interpolated.push_back(idft_single(X, n));
    }

    return interpolated;
}
