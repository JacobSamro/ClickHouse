#pragma once

#include <type_traits>

#include <base/types.h>
#include <base/wide_integer.h>
#include <base/BFloat16.h>


using Int128 = wide::integer<128, signed>;
using UInt128 = wide::integer<128, unsigned>;
using Int256 = wide::integer<256, signed>;
using UInt256 = wide::integer<256, unsigned>;

static_assert(sizeof(Int256) == 32);
static_assert(sizeof(UInt256) == 32);

/// The standard library type traits, such as std::is_arithmetic, with one exception
/// (std::common_type), are "set in stone". Attempting to specialize them causes undefined behavior.
/// So instead of using the std type_traits, we use our own version which allows extension.
template <typename T>
struct is_signed // NOLINT(readability-identifier-naming)
{
    static constexpr bool value = std::is_signed_v<T>;
};

template <> struct is_signed<Int128> { static constexpr bool value = true; };
template <> struct is_signed<Int256> { static constexpr bool value = true; };
template <> struct is_signed<BFloat16> { static constexpr bool value = true; };

template <typename T>
inline constexpr bool is_signed_v = is_signed<T>::value;

template <typename T>
struct is_unsigned // NOLINT(readability-identifier-naming)
{
    static constexpr bool value = std::is_unsigned_v<T>;
};

template <> struct is_unsigned<UInt128> { static constexpr bool value = true; };
template <> struct is_unsigned<UInt256> { static constexpr bool value = true; };

template <typename T>
inline constexpr bool is_unsigned_v = is_unsigned<T>::value;

template <class T> concept is_integer =
    std::is_integral_v<T>
    || std::is_same_v<T, Int128>
    || std::is_same_v<T, UInt128>
    || std::is_same_v<T, Int256>
    || std::is_same_v<T, UInt256>;

template <typename T>
struct is_arithmetic // NOLINT(readability-identifier-naming)
{
    static constexpr bool value = std::is_arithmetic_v<T>;
};

template <> struct is_arithmetic<Int128> { static constexpr bool value = true; };
template <> struct is_arithmetic<UInt128> { static constexpr bool value = true; };
template <> struct is_arithmetic<Int256> { static constexpr bool value = true; };
template <> struct is_arithmetic<UInt256> { static constexpr bool value = true; };
template <> struct is_arithmetic<BFloat16> { static constexpr bool value = true; };

template <typename T>
inline constexpr bool is_arithmetic_v = is_arithmetic<T>::value;


template <typename T>
struct is_floating_point // NOLINT(readability-identifier-naming)
{
    static constexpr bool value = std::is_floating_point_v<T>;
};

template <> struct is_floating_point<BFloat16> { static constexpr bool value = true; };

template <typename T>
inline constexpr bool is_floating_point_v = is_floating_point<T>::value;


template <typename T>
struct make_unsigned // NOLINT(readability-identifier-naming)
{
    using type = std::make_unsigned_t<T>;
};

template <> struct make_unsigned<Int128> { using type = UInt128; };
template <> struct make_unsigned<UInt128> { using type = UInt128; };
template <> struct make_unsigned<Int256>  { using type = UInt256; };
template <> struct make_unsigned<UInt256> { using type = UInt256; };

template <typename T> using make_unsigned_t = typename make_unsigned<T>::type;

template <typename T>
struct make_signed // NOLINT(readability-identifier-naming)
{
    using type = std::make_signed_t<T>;
};

template <> struct make_signed<Int128>  { using type = Int128; };
template <> struct make_signed<UInt128> { using type = Int128; };
template <> struct make_signed<Int256>  { using type = Int256; };
template <> struct make_signed<UInt256> { using type = Int256; };

template <typename T> using make_signed_t = typename make_signed<T>::type;

template <typename T>
struct is_big_int // NOLINT(readability-identifier-naming)
{
    static constexpr bool value = false;
};

template <> struct is_big_int<Int128> { static constexpr bool value = true; };
template <> struct is_big_int<UInt128> { static constexpr bool value = true; };
template <> struct is_big_int<Int256> { static constexpr bool value = true; };
template <> struct is_big_int<UInt256> { static constexpr bool value = true; };

template <typename T>
inline constexpr bool is_big_int_v = is_big_int<T>::value;
