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


class AAD22
{
private:
    double m_val;
    double m_d1[2]; // dx, dy
    double m_d2[3]; // dx2, dy2, dxy

public:
    AAD22() = delete;

    constexpr AAD22(double c)
    : m_val(c),
    m_d1 {0, 0},
    m_d2 {0, 0, 0}
    {}

private:
    constexpr AAD22(int i, double v)
    : m_val(v),
    m_d1 {(i == 0) ? 1.0 : 0.0, (i == 0) ? 0.0 : 1.0},
    m_d2 {0, 0, 0}
    {}

public:
    constexpr static AAD22 x(double v)
    {return AAD22(0, v);}

    constexpr static AAD22 y(double v)
    {return AAD22(1, v);}

    // operators

    constexpr AAD22 &operator+() {
        return *this;
    }

    constexpr AAD22 &operator-() {
        this->m_val = -this->m_val;

        this->m_d1[0] = -this->m_d1[0];
        this->m_d1[1] = -this->m_d1[1];

        this->m_d2[0] = -this->m_d2[0];
        this->m_d2[1] = -this->m_d2[1];
        this->m_d2[2] = -this->m_d2[2];

        return *this;
    }

    constexpr AAD22 &operator+=(const AAD22 &right) {
        this->m_val += right.m_val;

        this->m_d1[0] += right.m_d1[0];
        this->m_d1[1] += right.m_d1[1];

        this->m_d2[0] += right.m_d2[0];
        this->m_d2[1] += right.m_d2[1];
        this->m_d2[2] += right.m_d2[2];

        return *this;
    }

    constexpr friend AAD22 operator+(const AAD22 &lhs, const AAD22 &rhs) {
        return AAD22(lhs) += rhs;
    }

    constexpr AAD22 &operator-=(const AAD22 &right) {
        this->m_val -= right.m_val;

        this->m_d1[0] -= right.m_d1[0];
        this->m_d1[1] -= right.m_d1[1];

        this->m_d2[0] -= right.m_d2[0];
        this->m_d2[1] -= right.m_d2[1];
        this->m_d2[2] -= right.m_d2[2];

        return *this;
    }

    constexpr friend AAD22 operator-(const AAD22 &lhs, const AAD22 &rhs) {
        return AAD22(lhs) -= rhs;
    }

    constexpr friend AAD22 operator*(const AAD22 &lhs, const AAD22 &rhs) {
        AAD22 res = lhs;
        res.m_val = lhs.m_val * rhs.m_val;

        res.m_d1[0] = lhs.m_d1[0] * rhs.m_val + lhs.m_val * rhs.m_d1[0]; 
        res.m_d1[1] = lhs.m_d1[1] * rhs.m_val + lhs.m_val * rhs.m_d1[1];

        res.m_d2[0] = 2 * lhs.m_d1[0] * rhs.m_d1[0] + rhs.m_val * lhs.m_d2[0] + lhs.m_val * rhs.m_d2[0];
        
        res.m_d2[1] = 2 * lhs.m_d1[1] * rhs.m_d1[1] + rhs.m_val * lhs.m_d2[1] + lhs.m_val * rhs.m_d2[1];

        res.m_d2[2] = (lhs.m_d1[0] * rhs.m_d1[1] + rhs.m_val * lhs.m_d2[2]) \
        + (rhs.m_d1[0] * lhs.m_d1[1] + lhs.m_val * rhs.m_d2[2]);

        return res;
    }

    constexpr AAD22 &operator*=(const AAD22 &right) {
        *this = *this * right;
        return *this;
    }

    constexpr friend AAD22 operator/(const AAD22 &lhs, const AAD22 &rhs) {
        AAD22 res = lhs;
        res.m_val = lhs.m_val / rhs.m_val;

        res.m_d1[0] = (lhs.m_d1[0] * rhs.m_val - lhs.m_val * rhs.m_d1[0]) / (rhs.m_val * rhs.m_val); 
        res.m_d1[1] = (lhs.m_d1[1] * rhs.m_val - lhs.m_val * rhs.m_d1[1]) / (rhs.m_val * rhs.m_val);

        res.m_d2[0] = (-rhs.m_val * (2 * lhs.m_d1[0] * rhs.m_d1[0] + lhs.m_val * rhs.m_d2[0])
        + lhs.m_d2[0] * rhs.m_val * rhs.m_val + 2 * lhs.m_val * rhs.m_d1[0] * rhs.m_d1[0]) 
        / (rhs.m_val * rhs.m_val * rhs.m_val);
        
        res.m_d2[1] = (-rhs.m_val * (2 * lhs.m_d1[1] * rhs.m_d1[1] + lhs.m_val * rhs.m_d2[1])
        + lhs.m_d2[1] * rhs.m_val * rhs.m_val + 2 * lhs.m_val * rhs.m_d1[1] * rhs.m_d1[1]) 
        / (rhs.m_val * rhs.m_val * rhs.m_val);

        res.m_d2[2] = (-rhs.m_val * (lhs.m_d1[0] * rhs.m_d1[1] + lhs.m_d1[1] + rhs.m_d1[0] + lhs.m_val * rhs.m_d2[2]) 
        + lhs.m_d2[2] * rhs.m_val * rhs.m_val + 2 * lhs.m_val * rhs.m_d1[0] * rhs.m_d1[1])
        / (rhs.m_val * rhs.m_val * rhs.m_val);

        return res;
    }

    constexpr AAD22 &operator/=(const AAD22 &right) {
        *this = *this / right;
        return *this;
    }

    // functions 

    constexpr friend AAD22 exp(const AAD22 &func) {
        AAD22 res = func;
        res.m_val = std::exp(func.m_val);
        res.m_d1[0] = std::exp(func.m_val) * func.m_d1[0];
        res.m_d1[1] = std::exp(func.m_val) * func.m_d1[1];

        res.m_d2[0] = std::exp(func.m_val) * (func.m_d1[0] * func.m_d1[0] + func.m_d2[0]);
        res.m_d2[1] = std::exp(func.m_val) * (func.m_d1[1] * func.m_d1[1] + func.m_d2[1]);
        res.m_d2[2] = std::exp(func.m_val) * (func.m_d1[0] * func.m_d1[1] + func.m_d2[2]);

        return res;
    }

    constexpr friend AAD22 sin(const AAD22 &func) {
        AAD22 res = func;
        res.m_val = std::sin(func.m_val);
        res.m_d1[0] = std::cos(func.m_val) * func.m_d1[0];
        res.m_d1[1] = std::cos(func.m_val) * func.m_d1[1];

        res.m_d2[0] = std::cos(func.m_val) * func.m_d2[0] - std::sin(func.m_val) * func.m_d1[0] * func.m_d1[0];
        res.m_d2[1] = std::cos(func.m_val) * func.m_d2[1] - std::sin(func.m_val) * func.m_d1[1] * func.m_d1[1];
        res.m_d2[2] = std::cos(func.m_val) * func.m_d2[2] - std::sin(func.m_val) * func.m_d1[0] * func.m_d1[1];

        return res;
    }

    constexpr friend AAD22 cos(const AAD22 &func) {
        AAD22 res = func;
        res.m_val = std::cos(func.m_val);
        res.m_d1[0] = -std::sin(func.m_val) * func.m_d1[0];
        res.m_d1[1] =  -std::sin(func.m_val) * func.m_d1[1];

        res.m_d2[0] = -std::sin(func.m_val) * func.m_d2[0] - std::cos(func.m_val) * func.m_d1[0] * func.m_d1[0];
        res.m_d2[1] = -std::sin(func.m_val) * func.m_d2[1] - std::cos(func.m_val) * func.m_d1[1] * func.m_d1[1];
        res.m_d2[2] = -std::sin(func.m_val) * func.m_d2[2] - std::cos(func.m_val) * func.m_d1[0] * func.m_d1[1];

        return res;
    }

    // getters
    
    constexpr double get_x() {
        return m_d1[0];
    }

    constexpr double get_y() {
        return m_d1[1];
    }

    constexpr double get_xx() {
        return m_d2[0];
    }

    constexpr double get_yy() {
        return m_d2[1];
    }

    constexpr double get_xy() {
        return m_d2[2];
    }
};

constexpr AAD22 F(AAD22 const&x, AAD22 const&y) {
  return exp(2 * x) * sin(2 * y);
}

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
        AAD22 X = AAD22::x(x);
        AAD22 Y = AAD22::y(y);
        AAD22 Res = F(X, Y);
        if constexpr (W == WhichD::x) {
            return Res.get_x();
        } else if constexpr (W == WhichD::y) {
            return Res.get_y();
        } else if constexpr (W == WhichD::xx) {
            return Res.get_xx();
        } else if constexpr (W == WhichD::yy) {
            return Res.get_yy();
        } else if constexpr (W == WhichD::xy){
            return Res.get_xy();
        }
  }
}

}  // namespace ADAAI

#endif
