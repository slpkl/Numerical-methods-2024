#include "Differentiation.hpp"
#include <iomanip>
#include <iostream>
#include <string>

using namespace ADAAI;

// analytical implementations of  dF/dx, dF/dy, dF/dx^, dF/dy^2, dF/dxdy

constexpr double F_x(double x, double y)
{
  return 2 * std::exp(2 * x) * std::sin(2 * y);
}

constexpr double F_y(double x, double y)
{
  return 2 * std::exp(2 * x) * std::cos(2 * y);
}

constexpr double F_xx(double x, double y)
{
  return 4 * std::exp(2 * x) * std::sin(2 * y);
}

constexpr double F_yy(double x, double y)
{
  return -4 * std::exp(2 * x) * std::sin(2 * y);
}

constexpr double F_xy(double x, double y)
{
  return 4 * std::exp(2 * x) * std::cos(2 * y);
}

constexpr double my_abs(double x) { return (x > 0) ? x : -x; }

void testing_stencil3(double x_0, double y_0)
{

  std::cout << "-----------------------------------------------\n";
  std::cout << "x_0: " << x_0 << ", "
            << "y_0: " << y_0 << '\n';

  double difference_x =
      (Differentiator<WhichD::x, DiffMethod::stencil3>(F, x_0, y_0) -
       F_x(x_0, y_0));
  double difference_y =
      (Differentiator<WhichD::y, DiffMethod::stencil3>(F, x_0, y_0) -
       F_y(x_0, y_0));
  double difference_xx =
      (Differentiator<WhichD::xx, DiffMethod::stencil3>(F, x_0, y_0) -
       F_xx(x_0, y_0));
  double difference_yy =
      (Differentiator<WhichD::yy, DiffMethod::stencil3>(F, x_0, y_0) -
       F_yy(x_0, y_0));
  double difference_xy =
      (Differentiator<WhichD::xy, DiffMethod::stencil3>(F, x_0, y_0) -
       F_xy(x_0, y_0));

  double difference_array[5] = {difference_x, difference_y, difference_xx,
                                difference_yy, difference_xy};
  std::string diff_string_array[5] = {"DIFF_X | ", "DIFF_Y | ", "DIFF_XX | ",
                                      "DIFF_YY | ", "DIFF_XY | "};

  for (int i = 0; i < 5; i++)
  {
    std::cout << diff_string_array[i] << "Diff: " << std::setprecision(10)
              << difference_array[i] << '\n';
  }

  std::cout << (Differentiator<WhichD::yy, DiffMethod::stencil3>(F, x_0, y_0))
            << " " << F_yy(x_0, y_0) << '\n';
}

void testing_stencil3_extra(double x_0, double y_0)
{

  std::cout << "-----------------------------------------------\n";
  std::cout << "x_0: " << x_0 << ", "
            << "y_0: " << y_0 << '\n';

  double difference_x =
      (Differentiator<WhichD::x, DiffMethod::stencil3Extra>(F, x_0, y_0) -
       F_x(x_0, y_0));
  double difference_y =
      (Differentiator<WhichD::y, DiffMethod::stencil3Extra>(F, x_0, y_0) -
       F_y(x_0, y_0));
  double difference_xx =
      (Differentiator<WhichD::xx, DiffMethod::stencil3Extra>(F, x_0, y_0) -
       F_xx(x_0, y_0));
  double difference_yy =
      (Differentiator<WhichD::yy, DiffMethod::stencil3Extra>(F, x_0, y_0) -
       F_yy(x_0, y_0));
  double difference_xy =
      (Differentiator<WhichD::xy, DiffMethod::stencil3Extra>(F, x_0, y_0) -
       F_xy(x_0, y_0));

  double difference_array[5] = {difference_x, difference_y, difference_xx,
                                difference_yy, difference_xy};
  std::string diff_string_array[5] = {"DIFF_X | ", "DIFF_Y | ", "DIFF_XX | ",
                                      "DIFF_YY | ", "DIFF_XY | "};

  for (int i = 0; i < 5; i++)
  {
    std::cout << diff_string_array[i] << "Diff: " << std::setprecision(10)
              << difference_array[i] << '\n';
  }
}

void testing_stencil5(double x_0, double y_0)
{

  std::cout << "-----------------------------------------------\n";
  std::cout << "x_0: " << x_0 << ", "
            << "y_0: " << y_0 << '\n';

  double difference_x =
      (Differentiator<WhichD::x, DiffMethod::stencil5>(F, x_0, y_0) -
       F_x(x_0, y_0));
  double difference_y =
      (Differentiator<WhichD::y, DiffMethod::stencil5>(F, x_0, y_0) -
       F_y(x_0, y_0));
  double difference_xx =
      (Differentiator<WhichD::xx, DiffMethod::stencil5>(F, x_0, y_0) -
       F_xx(x_0, y_0));
  double difference_yy =
      (Differentiator<WhichD::yy, DiffMethod::stencil5>(F, x_0, y_0) -
       F_yy(x_0, y_0));
  double difference_xy =
      (Differentiator<WhichD::xy, DiffMethod::stencil5>(F, x_0, y_0) -
       F_xy(x_0, y_0));

  double difference_array[5] = {difference_x, difference_y, difference_xx,
                                difference_yy, difference_xy};
  std::string diff_string_array[5] = {"DIFF_X | ", "DIFF_Y | ", "DIFF_XX | ",
                                      "DIFF_YY | ", "DIFF_XY | "};

  for (int i = 0; i < 5; i++)
  {
    std::cout << diff_string_array[i] << "Diff: " << std::setprecision(10)
              << difference_array[i] << '\n';
  }
}

void testing_stencil5_extra(double x_0, double y_0)
{

  std::cout << "-----------------------------------------------\n";
  std::cout << "x_0: " << x_0 << ", "
            << "y_0: " << y_0 << '\n';

  double difference_x =
      (Differentiator<WhichD::x, DiffMethod::stencil5Extra>(F, x_0, y_0) -
       F_x(x_0, y_0));
  double difference_y =
      (Differentiator<WhichD::y, DiffMethod::stencil5Extra>(F, x_0, y_0) -
       F_y(x_0, y_0));
  double difference_xx =
      (Differentiator<WhichD::xx, DiffMethod::stencil5Extra>(F, x_0, y_0) -
       F_xx(x_0, y_0));
  double difference_yy =
      (Differentiator<WhichD::yy, DiffMethod::stencil5Extra>(F, x_0, y_0) -
       F_yy(x_0, y_0));
  double difference_xy =
      (Differentiator<WhichD::xy, DiffMethod::stencil5Extra>(F, x_0, y_0) -
       F_xy(x_0, y_0));

  double difference_array[5] = {difference_x, difference_y, difference_xx,
                                difference_yy, difference_xy};
  std::string diff_string_array[5] = {"DIFF_X | ", "DIFF_Y | ", "DIFF_XX | ",
                                      "DIFF_YY | ", "DIFF_XY | "};

  for (int i = 0; i < 5; i++)
  {
    std::cout << diff_string_array[i] << "Diff: " << std::setprecision(10)
              << difference_array[i] << '\n';
  }
}

int main()
{
  double testing_values_x[2] = {0.01, 1.7};
  double testing_values_y[2] = {0.01, 0.7};

  std::cout << "!!!!!!!!!!!!!!!!!!!!!!STENCIL3!!!!!!!!!!!!!!!!!!!!!!" << '\n';
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      testing_stencil3(testing_values_x[i], testing_values_y[j]);
    }
  }
  std::cout << "!!!!!!!!!!!!!!!!!!!!!!STENCIL3!!!!!!!!!!!!!!!!!!!!!!" << '\n'
            << '\n';

  std::cout << "!!!!!!!!!!!!!!!!!!!!!!STENCIL3 EXTRA!!!!!!!!!!!!!!!!!!!!!!"
            << '\n';
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      testing_stencil3_extra(testing_values_x[i], testing_values_y[j]);
    }
  }
  std::cout << "!!!!!!!!!!!!!!!!!!!!!!STENCIL3 EXTRA!!!!!!!!!!!!!!!!!!!!!!"
            << '\n'
            << '\n';

  std::cout << "!!!!!!!!!!!!!!!!!!!!!!STENCIL5!!!!!!!!!!!!!!!!!!!!!!" << '\n';
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      testing_stencil5(testing_values_x[i], testing_values_y[j]);
    }
  }
  std::cout << "!!!!!!!!!!!!!!!!!!!!!!STENCIL5!!!!!!!!!!!!!!!!!!!!!!" << '\n'
            << '\n';

  std::cout << "!!!!!!!!!!!!!!!!!!!!!!STENCIL5 EXTRA!!!!!!!!!!!!!!!!!!!!!!"
            << '\n';
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      testing_stencil5_extra(testing_values_x[i], testing_values_y[j]);
    }
  }
  std::cout << "!!!!!!!!!!!!!!!!!!!!!!STENCIL5 EXTRA!!!!!!!!!!!!!!!!!!!!!!"
            << '\n';
}
