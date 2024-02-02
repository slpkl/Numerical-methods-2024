#pragma once
#include "Consts.hpp"
#include <type_traits>
#include <iostream>
#include <cmath>
#include <cstdint>

namespace ADAAI {

template <typename F>

constexpr F Exp(F x){
    static_assert(std::is_floating_point_v<F>);
    F y_1; //fractional part
    F y_0; //integer part
    F y = x/Log2E;
    y = std::modf(y, &y_0);
    if (y < 0){
        //make |x_1| < 0.5, adjust x_0
    }

    if( y_0 < INT_MIN ){
        return 0.0;
    }
     
    else if( y_0 > INT_MAX ){
        return Inf;
    }

    else {
        n = int(y_0)
    }
    //f_1 = 
    F x_1 = y_1 * Log2E;
    ldexp(f_1 , n)
    
    //compute f_1
    F delta = 10.0 * Eps<F>
    for i in range(0,n){
        
    }

}


}
