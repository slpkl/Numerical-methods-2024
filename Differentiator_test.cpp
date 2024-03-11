#include <iostream>
#include "diff.hpp"
#include <iomanip>

using namespace ADAAI;

// analytical implementations of  dF/dx, dF/dy, dF/dx^, dF/dy^2, dF/dxdy 

constexpr double F_x(double x, double y) {
  return 2 * std::exp(2 * x) * std::sin(2 * y);
}

constexpr double F_y(double x, double y) {
  return 2 * std::exp(2 * x) * std::cos(2 * y);
}

constexpr double F_xx(double x, double y) {
  return 4 * std::exp(2 * x) * std::sin(2 * y);
}

constexpr double F_yy(double x, double y) {
  return -4*std::exp(2 * x) * std::sin(2 * y);
}

constexpr double F_xy(double x, double y) {
  return 4 * std::exp(2 * x) * std::cos(2 * y);
}

constexpr double my_abs(double x) { return (x > 0) ? x : -x; }

int main(){
    //TODO: tests for stencil3 x, y, xx, yy, xy (2*5 inputs)
    double x = 6.0;
    double y = 7.0;
    double difference = Differentiator<WhichD::xx, DiffMethod::stencil3>(F,6,7) - F_xx(6,7);
    std::cout << "x_0: " << x << " " << "y_0: " << y << " " << "diff: " << std::setprecision(15) << difference << "\n";
    return 0;
}
