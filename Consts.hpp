#pragma once
#include <cfloat>
#include <cmath>
#include <type_traits>

namespace ADAAI
{

template <typename F>
constexpr inline F Log2E;

template <typename F>
constexpr inline F Eps;

template <typename F>
constexpr inline F Sqrt2;

template <typename F>
constexpr inline F Inf;

template <>
constexpr inline float Log2E<float> = M_LOG2Ef;
template <>
constexpr inline double Log2E<double> = M_LOG2E;
template <>
constexpr inline long double Log2E<long double> = M_LOG2El;

template <>
constexpr inline float Sqrt2<float> = M_SQRT2f;
template <>
constexpr inline double Sqrt2<double> = M_SQRT2;
template <>
constexpr inline long double Sqrt2<long double> = M_SQRT2l;

template <>
constexpr inline float Eps<float> = FLT_EPSILON;
template <>
constexpr inline double Eps<double> = DBL_EPSILON;
template <>
constexpr inline long double Eps<long double> = LDBL_EPSILON;

template <>
constexpr inline float Inf<float> = HUGE_VALF;
template <>
constexpr inline double Inf<double> = HUGE_VAL;
template <>
constexpr inline long double Inf<long double> = HUGE_VALL;

} // namespace ADAAI
