#pragma once
#include <cmath>
#include <type_traits>
#include <cfloat>

#define _USE_MATH_DEFINES

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
constexpr inline F Pi;

template < typename F >
constexpr inline F M_2_Pi;

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
constexpr inline float Pi <float> = M_PIf;
template <>
constexpr inline double Pi <double> = M_PI;
template <>
constexpr inline long double Pi  <long double> = M_PIl;

template <>
constexpr inline float M_2_Pi <float> = M_2_PIf;
template <>
constexpr inline double M_2_Pi <double> = M_2_PI;
template <>
constexpr inline long double M_2_Pi  <long double> = M_2_PIl;

}
