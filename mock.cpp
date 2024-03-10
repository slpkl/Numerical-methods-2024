#include <cmath>
#include <iostream>

enum class DiffMethod : int {
  stencil3,
  stencil3Extra,
  stencil5,
  stencil5Extra,
  FwdAAD
};

constexpr double my_abs(double x) { return (x > 0) ? x : -x; }

enum class WhichD : int { x, y, xx, yy, xy };

const double h = 1e-4;

double F(double x, double y) { return std::exp(2 * x) * std::sin(2 * x); }

template <WhichD W, DiffMethod M, typename Collable>
constexpr double Differentiator(const Collable &F, double x, double y) {
  if constexpr (M == DiffMethod::stencil3) {
    if constexpr (W == x) {
      if constexpr (my_abs(x) < 1) {
        return (f(x + h) - f(x - h)) / (2 * h);
      } else if constexpr (my_abs(x) >= 1) {
        constexpr double h_x = h * my_abs(x);
        return (f(x + h_x) - f(x - h_x)) / (2 * h_x);
      }
    } else if constexpr (W == y) {
    } else if constexpr (W == xx) {
    } else if constexpr (W == yy) {
    } else if constexpr (W == xy) {
    }

  } else if constexpr (M == DiffMethod::stencil3Extra) {
  } else if constexpr (M == DiffMethod::stencil5) {
  } else if constexpr (M == DiffMethod::stencil5Extra) {
  } else if constexpr (M == DiffMethod::FwdAAD) {
  }
}
