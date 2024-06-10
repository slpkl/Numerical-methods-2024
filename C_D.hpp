#include <cmath>
#include <iostream>
#include <unordered_map>

class C_D
{

  // class with computing C_d function

private:
public:
  std::unordered_map<double, double> CD_table;
  void fill_table(std::unordered_map<double, double> &CD_table)
  {
    CD_table[0.5] = 0.09;
    CD_table[0.6] = 0.1;
    CD_table[0.7] = 0.15;
    CD_table[0.8] = 0.175;
    CD_table[0.9] = 0.3;
    CD_table[1.0] = 0.4;
    CD_table[1.1] = 0.5;
    CD_table[1.2] = 0.6;
    CD_table[1.3] = 0.5;
    CD_table[1.4] = 0.4;
    CD_table[1.5] = 0.35;
    CD_table[1.6] = 0.3;
    CD_table[1.7] = 0.3;
    CD_table[1.8] = 0.28;
    CD_table[1.9] = 0.26;
    CD_table[2.0] = 0.25;
    CD_table[2.1] = 0.22;
    CD_table[2.2] = 0.25;
  }

  double compute_CD(double M)
  {
    if (M >= 0.5 && M < 0.6)
    {
      return CD_table[0.5];
    }
    else if (M >= 0.6 && M < 0.7)
    {
      return CD_table[0.6];
    }
    else if (M >= 0.7 && M < 0.8)
    {
      return CD_table[0.7];
    }
    else if (M >= 0.8 && M < 0.9)
    {
      return CD_table[0.8];
    }
    else if (M >= 0.9 && M < 1.0)
    {
      return CD_table[0.9];
    }
    else if (M >= 1.0 && M < 1.1)
    {
      return CD_table[1.0];
    }
    else if (M >= 1.1 && M < 1.2)
    {
      return CD_table[1.1];
    }
    else if (M >= 1.2 && M < 1.3)
    {
      return CD_table[1.2];
    }
    else if (M >= 1.3 && M < 1.4)
    {
      return CD_table[1.3];
    }
    else if (M >= 1.4 && M < 1.5)
    {
      return CD_table[1.4];
    }
    else if (M >= 1.5 && M < 1.6)
    {
      return CD_table[1.5];
    }
    else if (M >= 1.6 && M < 1.7)
    {
      return CD_table[1.6];
    }
    else if (M >= 1.7 && M < 1.8)
    {
      return CD_table[1.7];
    }
    else if (M >= 1.8 && M < 1.9)
    {
      return CD_table[1.8];
    }
    else if (M >= 1.9 && M < 2.0)
    {
      return CD_table[1.9];
    }
    else if (M >= 2.0 && M < 2.1)
    {
      return CD_table[2.0];
    }
    else if (M >= 2.1 && M < 2.2)
    {
      return CD_table[2.1];
    }
    else if (M >= 2.2 && M <= 2.3)
    {
      return CD_table[2.2];
    }
    else
    {

      return -1.0; // return error value
    }
  }
};
