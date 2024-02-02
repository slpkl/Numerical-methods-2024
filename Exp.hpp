#pragma once
#include "Consts.hpp"
#include <type_traits>
#include <iostream>
#include <cmath>
#include <limits>

namespace ADAAI
{

    template <typename F>
    constexpr F Pow(F x, int k)
    {
        F res = 1;
        for (int i = 0; i < k; i++)
        {
            res *= x;
        }
        return res;
    }

    int Factorial(int n)
    {
        int res = 1;
        for (int i = 1; i <= n; i++)
        {
            res *= i;
        }
        return res;
    }

    template <typename F>
    constexpr F Exp(F x)
    {
        static_assert(std::is_floating_point_v<F>);
        F y_1; // fractional part
        F y_0; // integer part
        F y = x * Log2E<F>;
        y_1 = std::modf(y, &y_0);
        int32_t n;

        // check Nan
        if (x != x)
        {
            return x;
        }

        if (y < 0)
        {
            if (y_1 < -0.5)
            {
                y_0--;
                y_1++;
            }
        }
        else if (y_1 > 0.5)
        {
            y_0++;
            y_1--;
        }

        if (y_0 < INT64_MIN)
        {
            return 0.0;
        }
        else if (y_0 > INT64_MAX)
        {
            return Inf<F>;
        }
        else
        {
            n = static_cast<int>(y_0);
        }
        F x_1 = y_1 / Log2E<F>;
        F exp_temp = 0;
        int k = 0;
        while (true)
        {
            F current_memb = Pow(x_1, k) / static_cast<F>(Factorial(k));
            exp_temp += current_memb;

            if (x_1 > 0)
            {
                F res_error = Sqrt2<F> * Pow(x_1, k + 1) / static_cast<F>(Factorial(k + 1));
                if (res_error < 10 * Eps<F>)
                {
                    break;
                }
            }
            else
            {
                F res_error = Pow(x_1, k + 1) / static_cast<F>(Factorial(k + 1));
                if (res_error > 0)
                {
                    if (res_error < 10 * Eps<F>)
                    {
                        break;
                    }
                }
                else
                {
                    if (-res_error < 10 * Eps<F>)
                    {
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
