#include "Consts.hpp"
#include <cmath>

using namespace ADAAI;

template <typename F>
constexpr F a_k(int k) {
  return (M_2_PI * (cos(Pi<F> * k) * exp(Pi<F>) - 1)) / (k*k + 1);
}

