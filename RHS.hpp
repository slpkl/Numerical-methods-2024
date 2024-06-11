#include "C_D.hpp"
#include "StandartAtmosphereModel.hpp"
#include <iostream>
#include <tuple>

class RHS
{
  // class with function which compute RHS of our ODE.
  //  u = (x, v_x, y, v_y). compute u* = (v_x, (-Q * v_x /v )/m, v_y, (-Q v_y /
  //  v)/m)

private:
  // fields are coordinates of our vector u - initial state
  double x = 0;
  double v_x = 0;
  double y = 0;
  double v_y = 0;

  // memoised constants
  const double m = 106.0;            // kg - projectile mass
  const double d = 0.216;            // m - diameter
  const double v_0 = 1640;           // m/sec - initial velocity
  const double pi = 3.1415926535897; // pi constant
  const double S = pi * d * d / 4;   // projectile cross-section

public:
  constexpr RHS(double p_x, double p_v_x, double p_y, double p_v_y)
  {
    x = p_x;
    v_x = p_v_x;
    y = p_y;
    v_y = p_v_y;
  }

  // compute Air speed via height
  constexpr double compute_A(double h)
  {
    StandartAtmosphereModel atmosphere(h);
    double p = atmosphere.getPressure();
    double ro = atmosphere.getDensity();
    return std::sqrt(p / ro);
  }

  // compute Mach number
  constexpr double compute_M(double v, double h)
  {
    double A_h = compute_A(h);
    return v / A_h;
  }

  // computing aerodynamic drag force
  double compute_Q(double M, double S, double v_x, double v_y, double h)
  {
    C_D cd;
    double Cd_value = cd.compute_CD(M);
    StandartAtmosphereModel atmosphere(h);
    double ro = atmosphere.getPressure();
    double v = std::sqrt(v_x * v_x + v_y * v_y);
    double Q = Cd_value * ro * v * v / 2 * S;
    return Q;
  }

  // finally, compute new vector u*
  constexpr std::tuple<double, double, double, double>
  compute_dt_u(double x, double v_x, double y, double v_y)
  {
    double v = std::sqrt(v_x * v_x + v_y * v_y);
    double M = compute_M(v, y);
    double Q = compute_Q(M, S, v_x, v_y, y);
    double x_new = v_x;
    double vx_new = -Q * (v_x / v) / m;
    double y_new = v_y;
    double vy_new = -Q * (v_y / v) / m;
    return std::make_tuple(x_new, vx_new, y_new, vy_new);
  }

  const std::tuple<double, double, double, double> getRHS()
  {
    return compute_dt_u(x, v_x, y, v_y);
  }
};
