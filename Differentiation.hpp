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
  double h_x = my_abs(x) < 1 ? h : h * my_abs(x);
  double h_y = my_abs(y) < 1 ? h : h * my_abs(x);
  if constexpr (M == DiffMethod::stencil3) {
    if constexpr (W == WhichD::x) {
      return (F(x + h, y) - F(x - h, y)) / (2 * h);
    } else if constexpr (W == WhichD::y) {
      return (F(x, y + h_x) - F(x, y - h_x)) / (2 * h_x);
    } else if constexpr (W == WhichD::xx) {
      return (F(x + h_x, y) - 2 * F(x, y) + F(x - h_x, y)) / (h_x * h_x);

    } else if constexpr (W == WhichD::yy) {
      return (F(x, y + h_x) - 2 * F(x, y) + F(x, y - h_x)) / (h_x * h_x);

    } else if constexpr (W == WhichD::xy) {
      return (1 / (4 * h_x * h_y)) *
             (F(x + h_x, y + h_y) - F(x - h_x, y - h_y) - F(x + h_x, y - h_y) +
              F(x - h_x, y - h_y));
    }
  } else if constexpr (M == DiffMethod::stencil3Extra) {
  } else if constexpr (M == DiffMethod::stencil5) {
    if constexpr (W == WhichD::x) {
      return (1 / 12) * F(x - 2 * h_x, y) - (2 / 3) * F(x - h_x, y) +
             (2 / 3) * F(x + h_x, y) - (1 / 12) * F(x + 2 * h_x, y);
    } else if constexpr (W == WhichD::y) {
      return (1 / 12) * F(x, y - 2 * h_y) - (2 / 3) * F(x, y - h_y) +
             (2 / 3) * F(x, y + h_y) - (1 / 12) * F(x, y + 2 * h_y);
    } else if constexpr (W == WhichD::xx) {
      return (-1 / 12) * F(x - 2 * h_x, y) + (4 / 3) * F(x - h_x, y) -
             (5 / 2) * F(x, y) + (4 / 3) * F(x + h_x, y) -
             (1 / 12) * F(x + 2 * h_x, y);
    } else if constexpr (W == WhichD::yy) {
      return (-1 / 12) * F(x, y - 2 * h_y) + (4 / 3) * F(x, y - h_y) -
             (5 / 2) * F(x, y) + (4 / 3) * F(x, y + h_y) -
             (1 / 12) * F(x, y + 2 * h_y);
    } else if constexpr (W == WhichD::xy) {
    }
  }

  else if constexpr (M == DiffMethod::stencil5Extra) {
  } else if constexpr (M == DiffMethod::FwdAAD) {
  }
}

}  // namespace ADAAI

#endif
