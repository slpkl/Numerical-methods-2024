#include "Consts.hpp"
#include "Numerical_coeffs.hpp"
#include "Chebyshev.hpp"
#include "ak.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace ADAAI;

int main() {
    for (int k = 0; k < 50; k++) {
        std::cout << std::setprecision(30) << "Anal: " << a_k<long double>(k) << ", " 
        << "Numerical: " << numerical_coefs<long double>(10, k)
        << ", " << "Diff: " << abs(a_k<long double>(k) - numerical_coefs<long double>(10, k)) 
        << "  k = " << k <<'\n';
    }
}
