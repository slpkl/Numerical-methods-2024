#include <array>
#include <cmath>
#include <iostream>
#include <limits>

constexpr int N = 4;
constexpr double k = 1.0;
constexpr double dt = 0.1;

struct State {
  double x; //координата
  double v; //скорость
};

template <std::size_t N>
double lagrange(const std::array<double, N> &times, std::size_t i, double t) {
    double result = 1.0;

    for (std::size_t j = 0; j < N; ++j) {
        if (j != i) {
            double denom = times[i] - times[j];
            if (std::fabs(denom) < std::numeric_limits<double>::epsilon()) {
                return -1.0; 
            }
            result = result * ((t - times[j]) / denom);
        }
    }
    return result;
}

template <std::size_t N>
double lagrange_derivative(const std::array<double, N> &times, std::size_t i, double t) {
    double result = 0.0;

    for (std::size_t j = 0; j < N; ++j) {
        if (j == i) continue;

        double denom_ij = times[i] - times[j];
        if (std::fabs(denom_ij) < std::numeric_limits<double>::epsilon()) {
            return -1.0; 
        }

        double term = 1.0 / denom_ij;

        for (std::size_t l = 0; l < N; ++l) {
            if (l != i && l != j) {
                double denom_il = times[i] - times[l];
                if (std::fabs(denom_il) < std::numeric_limits<double>::epsilon()) {
                    return -1.0;
                }

                term *= (t - times[l]) / denom_il;
            }
        }

        result += term;
    }

    return result;
}

std::array<double, N> compute_coefficients(const State &state) {
  std::array<double, N> coeffs;
  coeffs[0] = state.x;
  coeffs[1] = state.v;
  coeffs[2] = -k * state.x;
  coeffs[3] = -k * state.v;

  for (size_t i = 2; i < N; ++i) {
    coeffs[i] /= static_cast<double>(i * (i - 1));
  }

  return coeffs;
}

State interpolate(const std::array<State, N> &states,
                  const std::array<double, N> &times, double t) {
  double p = 0.0;
  double q = 0.0;
  for (size_t i = 0; i < N; ++i) {
    double basis = lagrange(times, i, t);
    double basis_derivative = lagrange_derivative(times, i, t);
    p += states[i].x * basis;
    q += states[i].v * basis_derivative;
  }
  return {p, q};
}

State evolve_state(const State &state, const std::array<double, 4> &coeffs,
                   double dt) {
  State new_state = state;
  double dt_pow = 1.0;
  for (size_t i = 1; i < N; ++i) {
    dt_pow *= dt;
    new_state.x += coeffs[i] * dt_pow;
    if (i < 3) {
      new_state.v += coeffs[i + 1] * dt_pow;
    } else {
      new_state.v += 0;
    }
  }
  return new_state;
}

int main() {
    std::array<State, 4> states = {{
        {1.0, 0.0}, {0.995, -0.1}, {0.98, -0.2}, {0.955, -0.3}
    }};
    
    std::array<double, 4> times = {0.0, 1.0, 2.0, 3.0};

    double t = 4.0;

    for (int step = 0; step < 100; ++step) {
        const State& current_state = states.back();
        auto coeffs = compute_coefficients(current_state);
        State new_state = evolve_state(current_state, coeffs, 1.0);

        for (size_t i = 0; i < states.size() - 1; ++i) {
            states[i] = states[i + 1];
            times[i] = times[i + 1];
        }

        states.back() = new_state;
        times.back() = t;
        t += 1.0;

        std::cout << "t = " << t << "    x = " << new_state.x
                  << "    v = " << new_state.v << "\n";
    }

    return 0;
}