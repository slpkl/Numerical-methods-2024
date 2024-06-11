#include "Numerical_coeffs.hpp"
#include <fftw3.h>

using namespace ADAAI;

const int N = 20;
const int num_N = 20;

long double coeffs_arr[N];
long double x_i[N];

void x_calc()
{
  for (int i = 0; i < N; i++)
  {
    x_i[i] = (Pi<long double> * i) / (N + 1);
  }
}

long double my_abs(long double x) { return (x > 0) ? x : -x; }

void coeffs()
{
  for (int i = 0; i < N; i++)
  {
    coeffs_arr[i] = numerical_coefs<long double>(num_N, i);
  }
}

long double f(long double x)
{
  coeffs();
  long double function_res = coeffs_arr[0] / 2;
  for (int i = 1; i < N; i++)
  {
    function_res += coeffs_arr[i] * cos(i * x);
  }
  return function_res;
}

namespace ADAAI
{
void fourie(int N)
{
  fftw_complex *in, *out;
  fftw_plan p;

  in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * (2 * N + 1));
  out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * (2 * N + 1));
  p = fftw_plan_dft_1d((2 * N + 1), in, out, FFTW_FORWARD, FFTW_ESTIMATE);

  for (int k = 0; k < 2 * N + 1; k++)
  {
    double a_k = numerical_coefs<long double>(10000, k);
    in[k][0] = a_k;
  }

  fftw_execute(p);
  // ответ в out
  x_calc();
  // set precision 30 + diff
  for (int k = 0; k < N; k++)
  {
    double answer = out[k][0] - in[0][0] / 2;
    double diff = my_abs(f(x_i[k]) - answer);
    std::cout << in[k][0] << " answer: " << answer << " "
              << "x_i = " << x_i[k] << ", "
              << "f(x) = " << f(x_i[k]) << " "
              << "diff: " << diff << "\n";
  }

  fftw_destroy_plan(p);
  fftw_free(in);
  fftw_free(out);
}
} // namespace ADAAI

int main() { ADAAI::fourie(N); }
