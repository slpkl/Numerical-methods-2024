#ifndef __CHEBYSHEV_H__
#define __CHEBYSHEV_H__
namespace Storage_B
{
/*
 *  Functions calculate Chebyshev Polynomials Tn(x) and Un(x)
 */
  namespace Chebyshev
  {
    // Chebyshev Polynomials of the first kind: Tn(x)
    //
    // n = 0
    template <class T> inline auto T0(const T& x)
    {
      return static_cast<T>(1);
    }

    // n = 1
    template <class T> inline auto T1(const T& x)
    {
      return x;
    }

    // n = 2
    template <class T> inline auto T2(const T& x)
    {
      return (static_cast<T>(2) * x*x) - static_cast<T>(1);
    }

/*
 *  Tn(x)
 */
    template <class T> inline auto Tn(unsigned int n, const T& x)
    {
      switch(n)
      {
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

      for (auto l = 3u ; l <= n ; ++l)
      { 
        tn = (static_cast<T>(2) * x * tnm1) - tnm2;
        tnm2 = tnm1;
        tnm1 = tn;
      }

      return tn;
    }

    // Chebyshev Polynomials of the second kind: Un(x)
    //
    // n = 0
    template <class T> inline auto U0(const T& x)
    {
      return static_cast<T>(1);
    }

    // n = 1
    template <class T> inline auto U1(const T& x)
    {
      return static_cast<T>(2) * x;
    }

    // n = 2
    template <class T> inline auto U2(const T& x)
    {
      return (static_cast<T>(4) * x*x) - static_cast<T>(1);
    }

/*
 *  Un(x)
 */
    template <class T> inline auto Un(unsigned int n, const T& x)
    {
      switch(n)
      {
        case 0:
          return U0<T>(x);

        case 1: 
          return U1<T>(x);

        case 2: 
          return U2<T>(x);
   
        default:
          break;
      }

      //return (static_cast<T>(2) * x * Un<T>(n - 1, x)) - Un<T>(n - 2, x);

      auto unm1(U2<T>(x));
      auto unm2(U1<T>(x));
      auto un(unm1);

      for (auto l = 3u ; l <= n ; ++l)
      { 
        un = (static_cast<T>(2) * x * unm1) - unm2;
        unm2 = unm1;
        unm1 = un;
      }

      return un;
    }
  }
}
#endif  
