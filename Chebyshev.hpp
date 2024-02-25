#ifndef __CHEBYSHEV_H__
#define __CHEBYSHEV_H__

/*
 *  Functions calculate Chebyshev Polynomial Tn(x)
 */
// Chebyshev Polynomials of the first kind: Tn(x)
//
// n = 0
template <class T>
inline auto T0(const T &x) {
  return static_cast<T>(1);
}

// n = 1
template <class T>
inline auto T1(const T &x) {
  return x;
}

// n = 2
template <class T>
inline auto T2(const T &x) {
  return (static_cast<T>(2) * x * x) - static_cast<T>(1);
}

template <class T>
inline auto Tn(unsigned int n, const T &x) {
  switch (n) {
    case 0:
      return T0<T>(x);

    case 1:
      return T1<T>(x);

    case 2:
      return T2<T>(x);

    default:
      break;
  }

  /*  We could simply do this:
        return (static_cast<T>(2) * x * Tn(n - 1, x)) - Tn(n - 2, x);
      but it could be slow for large n */

  auto tnm1(T2<T>(x));
  auto tnm2(T1<T>(x));
  auto tn(tnm1);

  for (auto l = 3u; l <= n; ++l) {
    tn = (static_cast<T>(2) * x * tnm1) - tnm2;
    tnm2 = tnm1;
    tnm1 = tn;
  }

  return tn;
}

#endif
