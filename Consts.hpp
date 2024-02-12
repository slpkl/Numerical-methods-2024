#pragma once
#include <array>
#include <cfloat>
#include <cmath>
#include <type_traits>

namespace ADAAI {

template <typename F>
constexpr inline F Log2E;

template <typename F>
constexpr inline F Eps;

template <typename F>
constexpr inline F Sqrt2;

template <typename F>
constexpr inline F Inf;

// Array Polynom contains coefficients of the polynomial in the numerator
template <typename F>
constexpr inline std::array<F, 7> Polynom = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

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

// Utilizing PadeApproximant[Exp[x], {x,0,{3,3}}] approximation method for float
// data type
template <>
constexpr inline std::array<float, 7> Polynom<std::array<float, 7>> = {
    0.5, 0.1, 0.008333333333333333333333333333, 0., 0., 0., 0.};

// Utilizing PadeApproximant[Exp[x], {x,0,{6,6}}] approximation method for double
// data type
template <>
constexpr inline std::array<double, 7> Polynom<std::array<double, 7>> = {
    0.5,
    0.11363636363636363636363636363,
    0.01515151515151515151515,
    0.001262626262626262626262,
    0.0000631313131313131313131313131313131,
    0.000001503126503126503126503126503126,
    0};

// Utilizing PadeApproximant[Exp[x], {x,0,{7,7}}] approximation method for long-double
// data type.
template <>
constexpr inline std::array<long double, 7>
    Polynom<std::array<long double, 7>> = {
        1 / 2.0l,     3 / 26.0l,     5 / 312.0l,     5 / 3432.0l,
        1 / 11440.0l, 1 / 308880.0l, 1 / 17297280.0l};

}  // namespace ADAAI
