#include "Consts.hpp"
#include "Numerical_coeffs.hpp"
#include "Chebyshev.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace ADAAI;

const int N = 52;

template <typename F>
constexpr F a_k(int k) {
  return (M_2_PI * (cos(Pi<F> * k) * exp(Pi<F>) - 1)) / (k*k + 1);
}

long double my_abs(long double x) {
    return (x > 0) ? x : -x;
}

int main() {
    for (int k = 1; k < 50; k++) {
        std::cout << "k = " << k << ", " << std::setprecision(15) << "Analyst: " << std::setprecision(15)
        << a_k<long double>(k) << ", " 
        << "Numerical: " << numerical_coefs<long double>(N, k)
        << ", " << "Diff: " << my_abs(a_k<long double>(k) - numerical_coefs<long double>(N, k)) 
        << '\n';
    }
}
