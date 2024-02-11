#pragma once
#include <cmath>
#include <iostream>
#include <limits>
#include <type_traits>
#include "Consts.hpp"

namespace ADAAI {

enum class MethodE : int { Taylor, Pade };

template <MethodE M = MethodE::Pade, typename F>
constexpr F Exp(F x) {
    static_assert(std::is_floating_point_v<F>);
    if (x != x) {
        return x;
    }
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

    if constexpr (M == MethodE::Taylor) {
        F exp_temp = 1;
        int k = 1;

        F current_memb = 1;
        while (k < 35) {
            current_memb /= k;
            current_memb *= x_1;
            exp_temp += current_memb;
            k++;
        }

        F exp_res = ldexpl(exp_temp, n);
        return exp_res;
    } else if constexpr (M == MethodE::Pade) {
    }
}
}  // namespace ADAAI
