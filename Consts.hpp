#pragma once
#include <cmath>
#include <type_traits>
#include <cfloat>
#include <array>

namespace ADAAI {

template < typename F >
constexpr inline F Log2E;

template < typename F >
constexpr inline F Eps;

template < typename F >
constexpr inline F Sqrt2;

template < typename F >
constexpr inline F Inf;

template < typename F >
constexpr inline std::array<F, 7> Polynom;

template <>
constexpr inline float Log2E <float> = M_LOG2Ef;
template <>
constexpr inline double Log2E <double> = M_LOG2E;
template <>
constexpr inline long double Log2E  <long double> = M_LOG2El;

template <>
constexpr inline float Sqrt2 <float> = M_SQRT2f;
template <>
constexpr inline double Sqrt2 <double> = M_SQRT2;
template <>
constexpr inline long double Sqrt2 <long double> = M_SQRT2l;

template <>
constexpr inline float Eps <float> = FLT_EPSILON;
template <>
constexpr inline double Eps <double> = DBL_EPSILON;
template <>
constexpr inline long double Eps  <long double> = LDBL_EPSILON;

template <>
constexpr inline float Inf <float> = HUGE_VALF;
template <>
constexpr inline double Inf <double> = HUGE_VAL;
template <>
constexpr inline long double Inf  <long double> = HUGE_VALL;



template <>
constexpr inline std::array<float, 7> Polynom <std::array<float, 7>> = {0.008333333333333333333333333333, 0.1, 0.5, 0., 0., 0., 0.};
template <>
constexpr inline std::array<double, 7> Polynom <std::array<double, 7>> = {0.008333333333333333333333333333, 0.1, 0.5, 0., 0., 0., 0.};
template <>
constexpr inline long double Inf  <long double> = HUGE_VALL;

}
