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

template <WhichD W>
double stencil3_func(double x, double y, double h_x, double h_y) {
  if constexpr (W == WhichD::x) {
    return (F(x + h_x, y) - F(x - h_x, y)) / (2 * h_x);
  } else if constexpr (W == WhichD::y) {
    return (F(x, y + h_y) - F(x, y - h_y)) / (2 * h_y);
  } else if constexpr (W == WhichD::xx) {
    return (F(x + h_x, y) - 2 * F(x, y) + F(x - h_x, y)) / (h_x * h_x);

  } else if constexpr (W == WhichD::yy) {
    return (F(x, y + h_y) - 2 * F(x, y) + F(x, y - h_y)) / (h_y * h_y);
  } else if constexpr (W == WhichD::xy) {
    return (1 / (4 * h_x * h_y)) * (F(x + h_x, y + h_y) - F(x - h_x, y + h_y) -
                                    F(x + h_x, y - h_y) + F(x - h_x, y - h_y));
  }
}

template <WhichD W>
double stencil5_func(double x, double y, double h_x, double h_y) {
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
    return 0;
  }
}

const double h = 1e-4;

const int n = 4;  // might be 2,3,4 ...

template <WhichD W, DiffMethod M, typename Collable>
constexpr double Differentiator(const Collable &F, double x, double y) {
  double h_x = my_abs(x) < 1 ? h : h * my_abs(x);
  double h_y = my_abs(y) < 1 ? h : h * my_abs(x);
  double h_xn = h_x / n;
  double h_yn = h_y / n;
  if constexpr (M == DiffMethod::stencil3) {
    if constexpr (W == WhichD::x) {
      return stencil3_func<WhichD::x>(x, y, h_x, h_y);
    } else if constexpr (W == WhichD::y) {
      return stencil3_func<WhichD::y>(x, y, h_x, h_y);
    } else if constexpr (W == WhichD::xx) {
      return stencil3_func<WhichD::xx>(x, y, h_x, h_y);
    } else if constexpr (W == WhichD::yy) {
      return stencil3_func<WhichD::xy>(x, y, h_x, h_y);

    } else if constexpr (W == WhichD::xy) {
      return stencil3_func<WhichD::xy>(x, y, h_x, h_y);
    }
  } else if constexpr (M == DiffMethod::stencil3Extra) {
    if constexpr (W == WhichD::x) {
      return (n * n * (stencil3_func<WhichD::x>(x, y, h_xn, h_yn)) -
              stencil3_func<WhichD::x>(x, y, h_x, h_y)) /
             (n * n - 1);
    } else if constexpr (W == WhichD::y) {
      return (n * n * (stencil3_func<WhichD::y>(x, y, h_xn, h_yn)) -
              stencil3_func<WhichD::y>(x, y, h_x, h_y)) /
             (n * n - 1);
    } else if constexpr (W == WhichD::xx) {
      return (n * n * (stencil3_func<WhichD::xx>(x, y, h_xn, h_yn)) -
              stencil3_func<WhichD::xx>(x, y, h_x, h_y)) /
             (n * n - 1);
    } else if constexpr (W == WhichD::yy) {
      return (n * n * (stencil3_func<WhichD::yy>(x, y, h_xn, h_yn)) -
              stencil3_func<WhichD::yy>(x, y, h_x, h_y)) /
             (n * n - 1);
    } else if constexpr (W == WhichD::xy) {
      return (n * n * (stencil3_func<WhichD::xy>(x, y, h_xn, h_yn)) -
              stencil3_func<WhichD::xy>(x, y, h_x, h_y)) /
             (n * n - 1);
    }
  } else if constexpr (M == DiffMethod::stencil5) {
    if constexpr (W == WhichD::x) {
      return stencil5_func<WhichD::x>(x, y, h_x, h_y);
    } else if constexpr (W == WhichD::y) {
      return stencil5_func<WhichD::y>(x, y, h_x, h_y);
    } else if constexpr (W == WhichD::xx) {
      return stencil5_func<WhichD::xx>(x, y, h_x, h_y);
    } else if constexpr (W == WhichD::yy) {
      return stencil5_func<WhichD::yy>(x, y, h_x, h_y);
    } else if constexpr (W == WhichD::xy) {
      // TODO
    }
  }

  else if constexpr (M == DiffMethod::stencil5Extra) {
    if constexpr (W == WhichD::x) {
      return (n * n * (stencil5_func<WhichD::x>(x, y, h_xn, h_yn)) -
              stencil5_func<WhichD::x>(x, y, h_x, h_y)) /
             (n * n - 1);
    } else if constexpr (W == WhichD::y) {
      return (n * n * (stencil5_func<WhichD::y>(x, y, h_xn, h_yn)) -
              stencil5_func<WhichD::y>(x, y, h_x, h_y)) /
             (n * n - 1);
    } else if constexpr (W == WhichD::xx) {
      return (n * n * (stencil5_func<WhichD::xx>(x, y, h_xn, h_yn)) -
              stencil5_func<WhichD::xx>(x, y, h_x, h_y)) /
             (n * n - 1);
    } else if constexpr (W == WhichD::yy) {
      return (n * n * (stencil5_func<WhichD::yy>(x, y, h_xn, h_yn)) -
              stencil5_func<WhichD::yy>(x, y, h_x, h_y)) /
             (n * n - 1);
    } else if constexpr (W == WhichD::xy) {
      // TODO
    }

  } else if constexpr (M == DiffMethod::FwdAAD) {
    // TODO
  }
}

}  // namespace ADAAI

#endif
