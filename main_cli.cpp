// Первым аргументом идет расположение файла, а вторым метод. выход находиться
// в этой же директории в файле interpolated.csv
// На данный момент возможна работа только с файлами, которые хранят в себе
// числовые данные разделенные новой строкой.
// Пример исползования:
// ./intp_cli dvals.csv fourier
//
// возможные методы: fourier, linear, lanczos

#include <cmath>
#include <complex>
#include <csignal>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <sys/types.h>
#include <vector>
#include "interpolators/fourier.h"
#include "interpolators/linear.h"
#include "interpolators/interpolator.h"
#include "interpolators/lanczos.h"
using namespace std;
using namespace Interpolators;

const double PI = 3.1415926535897932384626433;

Interpolator *intp_by_name(string name) {
    Interpolator *ptr;
    if (name == "linear") {
        ptr = new Interpolators::Linear();
    } else if (name == "fourier") {
        ptr = new Interpolators::Fourier();
    } else if (name == "lanczos") {
        ptr = new Interpolators::Lanczos();
    }

    return ptr;
}

class Parameters {
public:
    Parameters() {}
    char* csv_path;
    char* intp_method;
};

int main(int argc, char* argv[]) {
    Parameters params;

    if (argc >= 3) {
        params.csv_path = argv[1];
        params.intp_method = argv[2];
    }

    srand(time(NULL));

    // Входной и выходной файл
    ifstream discrete_vals_csv;
    ofstream real_vals_csv;
    discrete_vals_csv.open(params.csv_path);
    real_vals_csv.open("interpolated.csv");
    
    // Читаем по линиям
    vector<double> samples;
    string line;
    while (discrete_vals_csv >> line) {
        samples.push_back(stod(line));
    }
    discrete_vals_csv.close();

    Interpolator *I = intp_by_name(params.intp_method);
    vector<double> interpolated = I->interpolate(
        samples, 0, 
        samples.size() - 1, 
        0.05
    );

    // Вносим интерполированные данные
    double x = 0;
    for (double y : interpolated) {
        real_vals_csv << x << "\t" << y << endl;
        x += 0.05;
    }

    delete I;
    real_vals_csv.close();

    return 0;
}
