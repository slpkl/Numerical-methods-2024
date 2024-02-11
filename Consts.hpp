#pragma once
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

struct SelectArray {
    static constexpr inline std::array<long double, 3> Array = {
        1.0L, 2.0L, 3.0L};
};

template <>
struct SelectArray<float> {
    static constexpr inline std::array<float, 3> Array = {1.0f, 2.0f, 3.0f};
};

template <>
struct SelectArray<double> {
    static constexpr inline std::array<double, 3> Array = {1.0, 2.0, 3.0};
};

template <>
struct SelectArray<long double> {
    static constexpr inline std::array<long double, 3> Array = {
        1.0L, 2.0L, 3.0L};
};

}  // namespace ADAAI
