#pragma once
#include "Consts.hpp"
#include <type_traits>
#include <iostream>
#include <cmath>
#include <limits>


namespace ADAAI {

template <typename F>
constexpr F Pow(F x, int k) {
    F res = 1;
    for (int i = 0; i < k; i++) {
        res *= x;
    }
    return res;
}

template <typename F>
constexpr F AntiFactorial(F x_pow, int n) {
    F res = x_pow;
    for (int64_t i = 1; i <= n; i++) {
        res = res / static_cast<F>(i);
    }
    return res;
}

template <typename F>
constexpr F Exp(F x){
    static_assert(std::is_floating_point_v<F>);
    if(x != x) {
        return x;
    }
    F y_1; //fractional part
    F y_0; //integer part
    F y = x * Log2E<F>;
    y_1 = std::modf(y, &y_0);
    int64_t n;

    if (y < 0){
        if (y_1 < -0.5) {
            y_0--;
            y_1++;
        }
    }
    else if (y_1 > 0.5) {
        y_0++;
        y_1--;
    }
    
    if(y_0 < INT64_MIN ){
        return 0.0;
    }
    else if( y_0 > INT64_MAX ){
        return Inf<F>;
    }
    else {
        n = static_cast<int>(y_0);
    }
    F x_1 = y_1 / Log2E<F>;
    F exp_temp = 0;
    int k = 0;
    while(k < 25) {
        F current_memb = AntiFactorial(Pow(x_1, k), k);
        exp_temp += current_memb;

        if(x_1 > 0) {
            F res_error = Sqrt2<F> * AntiFactorial(Pow(x_1, k+1), k+1);
            if (res_error < 10 * Eps<F>) {
                break;
            }
        }
        else {
            F res_error = Pow(x_1, k + 1) / AntiFactorial(Pow(x_1, k+1), k+1);

            if (res_error > 0) {
                if (res_error < 10 * Eps<F>) {
                break;
                }
            }
            else {
                if (-res_error < 10 * Eps<F>) {
                break;
                }
            }
        }

        k++;
    }

    F exp_res = ldexp(exp_temp, n);
    
    return exp_res;    

    }

}
