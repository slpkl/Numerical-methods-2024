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

int main() {
  double max_diff = 0;
  int success_count = 0;
  int unsuccess_count = 0;

  std::cout << "Check int:" << '\n';
  for (double i = -50; i <= 50; i++) {
    max_diff = std::max(max_diff, (my_abs(Exp(i) - exp(i))));
    if (my_abs(Exp(i) - exp(i)) <= 1e-18) {
      std::cout << "Test Passed, "
                << "Pow = " << i << ", " << std::setprecision(N)
                << "Our: " << Exp(i) << ", Ideal: " << exp(i)
                << ", Diff: " << my_abs(Exp(i) - exp(i)) << '\n';
      success_count++;
    } else {
      std::cout << "Test Failed, "
                << "Pow = " << i << ", " << std::setprecision(N)
                << "Our: " << Exp(i) << ", Ideal: " << exp(i)
                << ", Diff: " << my_abs(Exp(i) - exp(i)) << '\n';
      unsuccess_count++;
    }
  }

  std::cout << '\n';
  std::cout << "Check float:" << '\n';

  std::vector<float> float_arr = {1.25,  1.5,   1.75,   2.25,    2.5,     2.75,
                                  -1.25, -1.5,  -1.75,  -2.25,   -2.5,    -2.75,
                                  -25.5, -24.5, -23.5,  -20.145, -15.625, 25.5,
                                  24.5,  23.5,  20.145, 15.625};

  for (auto k : float_arr) {
    max_diff = std::max(max_diff, (my_abs(Exp(k) - exp(k))));
    if (my_abs(Exp(k) - exp(k)) <= 1e-18) {
      std::cout << "Test Passed, "
                << "Pow = " << k << ", " << std::setprecision(N)
                << "Our: " << Exp(k) << ", Ideal: " << exp(k)
                << ", Diff: " << my_abs(Exp(k) - exp(k)) << '\n';
      success_count++;
    } else {
      std::cout << "Test Failed, "
                << "Pow = " << k << ", " << std::setprecision(N)
                << "Our: " << Exp(k) << ", Ideal: " << exp(k)
                << ", Diff: " << my_abs(Exp(k) - exp(k)) << '\n';
      unsuccess_count++;
    }
  }

  std::vector<double> double_arr = {
      1.252525,  1.55555,   1.757575,   2.252525,  2.5555,        2.757575,
      -1.252525, -1.52525,  -1.751313,  -2.251313, -2.51313,      -2.751313,
      -25.51313, -24.5515,  -23.52515,  -20.14531, -15.625544474, 25.585348,
      24.505304, 23.584583, 20.1453123, 15.625543};

  std::cout << '\n';
  std::cout << "Check long double" << '\n';

  for (auto k : double_arr) {
    max_diff = std::max(max_diff, (my_abs(Exp(k) - exp(k))));
    if (my_abs(Exp(k) - exp(k)) <= 1e-18) {
      std::cout << "Test Passed, "
                << "Pow = " << k << ", " << std::setprecision(N)
                << "Our: " << Exp(k) << ", Ideal: " << exp(k)
                << ", Diff: " << my_abs(Exp(k) - exp(k)) << '\n';
      success_count++;
    } else {
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
