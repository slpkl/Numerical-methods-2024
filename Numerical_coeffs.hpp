#include <cmath>
#include "Chebyshev.hpp"
#include <iostream>
#include <Consts.hpp>

template <typename F>
constexpr F numerical_coefs(int N, int k) {
  int m = N + 1;
  F result_sum = 2 / (N + 1);
  for (int i = 1; i <= N + 1; i++) {
    F argument = std::cos((2 * i - 1) / (2 * N + 2) * Pi<F>);
    F exp_pow_acos = std::exp(std::acos(argument));
    F T_k = Tn(k, argument);
    result_sum = result_sum * exp_pow_acos * T_k;
  }
  return result_sum;
}
