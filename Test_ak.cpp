#include <cmath>
#include <iostream>
#include "Chebyshev.hpp"
#include "Consts.hpp"

namespace ADAAI {

template <typename F>
constexpr F numerical_coefs(int N, int k) {
  int m = N + 1;
  F result_sum = 0;
  for (int i = 1; i <= N + 1; i++) {
    F argument = std::cos(
        Pi<F> * (2 * static_cast<F>(i) - 1) / (2 * static_cast<F>(N) + 2)
    );
    F exp_pow_acos = std::exp(std::acos(argument));
    F T_k = Tn(k, argument);
    result_sum += exp_pow_acos * T_k;
  }
  result_sum = result_sum / (N + 1);
  result_sum = result_sum * 2;
  return result_sum;
}
}  // namespace ADAAI
