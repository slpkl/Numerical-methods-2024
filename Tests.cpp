#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include "Consts.hpp"
#include "Exp.hpp"

using namespace ADAAI;

int const N = 10;

double my_abs(double a) {
    return (a > 0) ? a : (-1) * a;
}

int counter = 0;
int success_count = 0;
int unsuccess_count = 0;

template <typename F>
void TestFunction(F x) {
    F IdealExp = exp(x);
    F OurExp = Exp(x);
    F ErrorLimit = std::numeric_limits<F>::epsilon() * N;
    F TypeMetric;
    if (x <= 0) {
        TypeMetric = my_abs(IdealExp - OurExp);
    } else {
        TypeMetric = my_abs((IdealExp / OurExp) - 1.0);
    }

    if (TypeMetric <= ErrorLimit) {
        std::cout << "Test Passed!  "
                  << " "
                  << "Pow = " << x << ", "
                  << "Diff: " << my_abs(IdealExp - OurExp) << '\n';
        counter++;
        success_count++;
    } else {
        std::cout << "Test Failed!  "
                  << " "
                  << "Pow = " << x << ", "
                  << "Ideal: " << exp(x) << ", "
                  << "Our: " << Exp(x) << ", "
                  << "Diff: " << my_abs(IdealExp - OurExp) << '\n';
        counter++;
        unsuccess_count++;
    }
}

int main() {
    std::vector<float> float_arr = {
        1.25,    1.5,   1.75, 2.25,  2.5,    2.75,  -1.25, -1.5,
        -1.75,   -2.25, -2.5, -2.75, -25.5,  -24.5, -23.5, -20.145,
        -15.625, 25.5,  24.5, 23.5,  20.145, 15.625};

    std::vector<double> double_arr = {
        -10.5, -5.0,  -4.66, -4.5,  -4.27, -3.66, -3.5, -3.2, -2.7,
        -2.56, -2.44, -2.1,  -1.97, -1.5,  -1.06, -0.7, 0.3,  0.4,
        0.5,   0.6,   0.7,   1.1,   2.44,  2.56,  2.7,  3.2,  3.5,
        3.65,  4.27,  4.5,   466,   5.0,   10.5};

    std::vector<long double> long_double_arr = {
        1.252525l,   1.55555l,       1.757575l,  2.252525l,  2.5555l,
        2.757575l,   -1.252525l,     -1.52525l,  -1.751313l, -2.251313l,
        -2.51313l,   -2.751313l,     -25.51313l, -24.5515l,  -23.52515l,
        -20.14531l,  -15.625544474l, 25.585348l, 24.505304l, 23.584583l,
        20.1453123l, 15.625543l};

    std::cout << "Testing float:\n";
    for (auto k : float_arr) {
        TestFunction(k);
    }

    std::cout << "\n\n\n"
              << "Testing double:\n";
    for (auto k : double_arr) {
        TestFunction(k);
    }

    std::cout << "\n\n\n"
              << "Testing long double:\n";
    for (auto k : long_double_arr) {
        TestFunction(k);
    }

    std::cout << "\n\n\n"
              << "Succes: " << success_count << '\n'
              << "Failed: " << unsuccess_count << '\n'
              << "All: " << counter << '\n';
}
