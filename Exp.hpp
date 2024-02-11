#pragma once
#include "Consts.hpp"
#include <type_traits>
#include <iostream>
#include <cmath>
#include <limits>


namespace ADAAI {

template <typename F>
constexpr F  Exp(F x){
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
    int k = 1;

    F current_memb = 1;
    while(k < 20) {
        current_memb *= x_1;
        current_memb /= k;
        
        exp_temp += current_memb;
        k++;
    }

    F exp_res = ldexpl(exp_temp + 1, n);  
    return exp_res;    

    }

}
