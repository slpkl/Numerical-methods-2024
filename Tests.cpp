#include "Consts.hpp"
#include "Exp.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace ADAAI;

const int N = 18;

double my_abs(double a) { return (a > 0) ? a : (-1) * a; }

int main()
{
    double max_diff = 0;
    int success_count = 0;
    int unsuccess_count = 0;

    std::cout << "Check int:" << '\n';
    for (double i = -50; i <= 50; i++)
    {
        max_diff = std::max(max_diff, (my_abs(Exp(i) - exp(i))));
        if (my_abs(Exp(i) - exp(i)) <= 10* Eps<float>)
        {
            std::cout << "Test Passed, "
                      << "Pow = " << i << ", " << std::setprecision(N)
                      << "Our: " << Exp(i) << ", Ideal: " << exp(i)
                      << ", Diff: " << my_abs(Exp(i)) - exp(i) << '\n';
            success_count++;
        }
        else
        {
            std::cout << "Test Failed, "
                      << "Pow = " << i << ", " << std::setprecision(N)
                      << "Our: " << Exp(i) << ", Ideal: " << exp(i)
                      << ", Diff: " << my_abs(Exp(i) - exp(i)) << '\n';
            unsuccess_count++;
        }
    }

    std::cout << '\n';
    std::cout << "Check float:" << '\n';

    std::vector<float> float_arr = {1.25, 1.5, 1.75, 2.25, 2.5, 2.75,
                                    -1.25, -1.5, -1.75, -2.25, -2.5, -2.75,
                                    -25.5, -24.5, -23.5, -20.145, -15.625, 25.5,
                                    24.5, 23.5, 20.145, 15.625};

    for (auto k : float_arr)
    {
        max_diff = std::max(max_diff, (my_abs(Exp(k) - exp(k))));
        if (my_abs(Exp(k) - exp(k)) <= 10*Eps<float>)
        {
            std::cout << "Test Passed, "
                      << "Pow = " << k << ", " << std::setprecision(N)
                      << "Our: " << Exp(k) << ", Ideal: " << exp(k)
                      << ", Diff: " << my_abs(Exp(k) - exp(k)) << '\n';
            success_count++;
        }
        else
        {
            std::cout << "Test Failed, "
                      << "Pow = " << k << ", " << std::setprecision(N)
                      << "Our: " << Exp(k) << ", Ideal: " << exp(k)
                      << ", Diff: " << my_abs(Exp(k) - exp(k)) << '\n';
            unsuccess_count++;
        }
    }

    std::vector<long double> double_arr = {
        1.252525l, 1.55555l, 1.757575l, 2.252525l, 2.5555l, 2.757575l,
        -1.252525l, -1.52525l, -1.751313l, -2.251313l, -2.51313l, -2.751313l,
        -25.51313l, -24.5515l, -23.52515l, -20.14531l, -15.625544474l, 25.585348l,
        24.505304l, 23.584583l, 20.1453123l, 15.625543l};

    std::cout << '\n';
    std::cout << "Check long double" << '\n';

    for (auto k : double_arr)
    {
        max_diff = std::max(max_diff, (my_abs(Exp(k) - exp(k))));
        if (my_abs(Exp(k) - exp(k)) <= 10*Eps<long double>)
        {
            std::cout << "Test Passed, "
                      << "Pow = " << k << ", " << std::setprecision(N)
                      << "Our: " << Exp(k) << ", Ideal: " << exp(k)
                      << ", Diff: " << my_abs(Exp(k) - exp(k)) << '\n';
            success_count++;
        }
        else
        {
            std::cout << "Test Failed, "
                      << "Pow = " << k << ", " << std::setprecision(N)
                      << "Our: " << Exp(k) << ", Ideal: " << exp(k)
                      << ", Diff: " << my_abs(Exp(k) - exp(k)) << '\n';
            unsuccess_count++;
        }
    }

    std::cout << '\n';
    std::cout << "Max diff: " << max_diff << '\n';
    std::cout << "Success: " << success_count << '\n';
    std::cout << "Failed: " << unsuccess_count << '\n';
}
