#include "Consts.hpp"
#include "Numerical_coeffs.hpp"
#include <cmath>
#include <iostream>

using namespace ADAAI;

const int N = 20;
const int num_N = 1e5;

long double coeffs_arr[N];
long double x_i[N];

void x_calc()
{
  for (int i = 0; i < N; i++)
  {
    x_i[i] = (Pi<long double> * i) / (N + 1);
  }
}

void coeffs()
{
  for (int i = 0; i < N; i++)
  {
    coeffs_arr[i] = numerical_coefs<long double>(num_N, i);
  }
}

long double f(long double x)
{
  coeffs();
  long double function_res = coeffs_arr[0] / 2;
  for (int i = 1; i < N; i++)
  {
    function_res += coeffs_arr[i] * cos(i * x);
  }
  return function_res;
}

int main()
{
  x_calc();
  for (int i = 0; i < N; i++)
  {
    std::cout << "x_i = " << x_i[i] << ", "
              << "f(x) = " << f(x_i[i]) << '\n';
  }
}
