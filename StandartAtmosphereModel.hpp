#include <cmath>
#include <iostream>

class StandartAtmosphereModel
{
private:
  double h; // height (meters)
  int l;    //(level: 0,1,2,3)

  double ph(double h, int l)
  {

    // if (r[l] == 0) {
    //   double argument = -g * (h - H[l]) / (R_air * T[l]);
    //   return p[l] * std::exp(argument);
    // } else {
    //   double argument =
    //       g / (R_air * r[l]) * std::log(1 - (r[l] * (h - H[l])) / (T[l]));
    //   return p[l] * std::exp(argument);
    // }

    return r[l] == 0 ? p[l] * std::exp(-g * ((h - H[l]) / (T[l] * R_air)))
                     : p[l] * std::exp((g / (R_air * r[l])) *
                                  std::log(1 - (r[l] * (h - H[l]) / T[l])));
  }

  // calculate density on the given height
  double calculateDensity(double h, int l) 
  {
    double preassure = ph(h, l);
    return preassure / (R_air * (T[l] - r[l] * (h - H[l])));
    // return preassure / (R_air * (Th(h,l)));
  }

public:
  StandartAtmosphereModel(double height) : h(height)
  {
    determineL(); // determine lavel

    // calculate constants

    T[0] = T0;
    for (int i = 1; i < 4; ++i)
    {
      T[i] = T[i - 1] - r[i - 1] * (H[i] - H[i - 1]); // Temperatures at levels
    }

    p[0] = p_0;
    for (int i = 1; i < 4; ++i)
    {
      p[i] = ph(H[i], i - 1); // Pressures at levels
    }
  }

  void determineL()
  {
    if (h >= H[0] && h <= H[1])
    {
      l = 0;
    }
    else if (h > H[1] && h < H[2])
    {
      l = 1;
    }
    else if (h >= H[2] && h < H[3])
    {
      l = 2;
    }
    else if (h >= H[3] && h <= H[4])
    {
      l = 3;
    }
    else
    {
      l = -1;
    }
  }

  double getPressure() { return ph(h, l); }

  double getDensity() { return calculateDensity(h, l); }

  static constexpr double g = 9.80665; // м/с²
  static constexpr double R_air = 287.0528;

  // Precalculated variables
  double r[4] = {6.5 * 1e-3, 0, -1e-3, -2.8 * 1e-3};

  double H[5] = {0.0, 11000.0, 20000.0, 32000.0, 47000.0};

  double p_0 = 101325;
  double p[4];

  double T0 = 288.15;
  double T[4];

    //Display all calculated variables depending on the given height value
  void display()
  {
    std::cout << "height (h): " << h << " м" << std::endl;
    std::cout << "level (l): " << l << std::endl;
    std::cout << "atmosphere preassure: " << getPressure() << " Pa"
              << std::endl;
    std::cout << "air density : " << getDensity() << " kg/m^3" << std::endl;
    // std::cout << T[0] << std::endl;
    // std::cout << T[1] << std::endl;
    // std::cout << T[2] << std::endl;
    // std::cout << T[3] << std::endl;
  }
};
