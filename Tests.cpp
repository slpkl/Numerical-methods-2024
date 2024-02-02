//#include "Exp.hpp"
//#include "Consts.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

double Exp(double x){
    return 1 + x+ x*x/2 + x*x*x/6 + x*x*x*x/24 + x*x*x*x*x/120 + x*x*x*x*x*x/720;
}

double my_abs(double a) {
  return (a > 0)? a : (-1) * a;
}

int main() {
  double max_diff = 0;


  std::cout << "Check int:" << '\n';
  for (double i = -50; i <= 50; i++) {
    max_diff = std::max(max_diff, (my_abs(Exp(i) - exp(i))));
    std::cout << "Diff: " << my_abs(Exp(i) - exp(i)) << " Pow = " << i <<'\n';
  }

  std::cout << '\n';
  std::cout << "Check float:" << '\n';

  std::vector<float> float_arr = {
      1.25,    1.5,   1.75, 2.25,  2.5,    2.75,   -1.25, -1.5,
      -1.75,   -2.25, -2.5, -2.75, -25.5,  -24.5,  -23.5, -20.145,
      -15.625, 25.5,  24.5, 23.5,  20.145, 15.625
  };

  for (auto k : float_arr) {
    max_diff = std::max(max_diff, (my_abs(Exp(k) - exp(k))));
    std::cout << "Diff: " << my_abs(Exp(k) - exp(k)) << " Pow = " << k <<'\n';
  }

  std::vector<double> double_arr = {
      1.252525,    1.55555,   1.757575, 2.252525,  2.5555,    2.757575,   -1.252525, -1.52525,
      -1.751313,   -2.251313, -2.51313, -2.751313, -25.51313,  -24.5515,  -23.52515, -20.14531,
      -15.625544474, 25.585348,  24.505304, 23.584583,  20.1453123, 15.625543
  };

  std::cout << '\n';
  std::cout << "Check long double" << '\n';

  for (auto k : double_arr) {
    max_diff = std::max(max_diff, (my_abs(Exp(k) - exp(k))));
    std::cout << "Diff: " << my_abs(Exp(k) - exp(k)) << " Pow = " << k <<'\n';
  }
  
  std::cout << '\n';
  std::cout << "Max diff:" << max_diff;
}
