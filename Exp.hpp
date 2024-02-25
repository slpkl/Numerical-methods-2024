#pragma once
#include <cmath>
#include <iostream>
#include <limits>
#include <type_traits>
#include "Chebyshev.hpp"
#include "Coefs.hpp"
#include "Consts.hpp"

namespace ADAAI {

template <typename F>
constexpr F Pow(F x, int k) {
  return (k > 0) ? Pow(x, k - 1) * x : 1;
}

template <typename F>
constexpr long long Factorial(long long k) {
  return (k > 1) ? Factorial<F>(k - 1) * k : 1;
}

template <typename F>
constexpr inline F TaylorLHS(int k) {
  return (Sqrt2<F> * Pow(1.0l / Log2E<F> / 2.0l, k) / Factorial<F>(k + 1));
}

template <typename F>
static constexpr inline int MkExpTaylorOrder() {
  for (int i = 0; i < 1000; ++i) {
    if (TaylorLHS<F>(i) < Eps<F>) { return i - 1; }
  }
}

enum class MethodE : int { Taylor, Pade, Cheb };

template <MethodE M = MethodE::Cheb, typename F>
constexpr F Exp(F x) {
  static_assert(std::is_floating_point_v<F>);
  if (x != x) { return x; }

  F y_1;  // fractional part
  F y_0;  // integer part
  F y = x * Log2E<F>;
  y_1 = std::modf(y, &y_0);
  int64_t n;

  if (y < 0) {
    if (y_1 < -0.5) {
      y_0--;
      y_1++;
    }
  } else if (y_1 > 0.5) {
    y_0++;
    y_1--;
  }

  if (y_0 < INT64_MIN) {
    return 0.0;
  } else if (y_0 > INT64_MAX) {
    return Inf<F>;
  } else {
    n = static_cast<int>(y_0);
  }

  F x_1 = y_1 / Log2E<F>;
  F exp_temp = 1;
  if constexpr (M == MethodE::Taylor) {
    constexpr int N = MkExpTaylorOrder<F>();
    int k = 1;

    F current_memb = 1;
    while (k <= N) {
      current_memb /= k;
      current_memb *= x_1;
      exp_temp += current_memb;
      k++;
    }
  } else if constexpr (M == MethodE::Pade) {
    F numerator = 1;
    F denumerator = 1;
    F current_memb = 1;
    for (int i = 0; i < 7; i++) {
      current_memb *= x_1;
      
      numerator += current_memb * Polynom<std::array<F, 7>>[i];

      if (i % 2 == 0) {
        denumerator -= current_memb * Polynom<std::array<F, 7>>[i];
      } else {
        denumerator += current_memb * Polynom<std::array<F, 7>>[i];
      }
    }
    exp_temp = numerator / denumerator;
  } else if constexpr (M == MethodE::Cheb) {
    int N = 30;
    gsl_vector *c = gsl_vector_alloc(N + 1);
    Coefs(N, c);
    exp_temp = 0;
    for (int i = 0; i < N + 1; i++) {
      exp_temp += gsl_vector_get(c, i) * Tn(i, x_1);
    }
  }
  F exp_res = ldexpl(exp_temp, n);
  return exp_res;
}
}  // namespace ADAAI
