#ifndef Differ
#define Differ

#include <cmath>

namespace ADAAI {

constexpr double F(double x, double y) {
  return std::exp(2 * x) * std::sin(2 * y);
}

constexpr double my_abs(double x) { return (x > 0) ? x : -x; }

enum class DiffMethod : int {
  stencil3,
  stencil3Extra,
  stencil5,
  stencil5Extra,
  FwdAAD
};

enum class WhichD : int { x, y, xx, yy, xy };

const double h = 1e-4;

template <WhichD W, DiffMethod M, typename Collable>
constexpr double Differentiator(const Collable &F, double x, double y) {
  if constexpr (M == DiffMethod::stencil3) {
    if constexpr (W == WhichD::x) {
      if (my_abs(x) < 1) {
        return (F(x + h, y) - F(x - h, y)) / (2 * h);
      } else {
        double h_x = h * my_abs(x);
        return (F(x + h_x, y) - F(x - h_x, y)) / (2 * h_x);
      }
      } else if constexpr (W == WhichD::y) {
      } else if constexpr (W == WhichD::xx) {
      } else if constexpr (W == WhichD::yy) {
      } else if constexpr (W == WhichD::xy) {
      }

    } else if constexpr (M == DiffMethod::stencil3Extra) {
    } else if constexpr (M == DiffMethod::stencil5) {
    } else if constexpr (M == DiffMethod::stencil5Extra) {
    } else if constexpr (M == DiffMethod::FwdAAD) {
    }
}

} // namespace ADAAI

#endif