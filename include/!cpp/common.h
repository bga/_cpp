/*
  Copyright 2020 Bga <bga.email@gmail.com>

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#pragma once

#include <!cpp/common_macro.h>

#if defined(__IAR_SYSTEMS_ICC__ )
  #include "common.iar.before.h"
#endif

#if defined(__GNUC__ )
  #include "common.gcc.before.h"
#endif

#if defined(__clang__)
  #include "common.clang.before.h"
#endif

#if defined(_MSC_VER)
  #include "common.msvc.before.h"
#endif


#ifndef BGA__MAYBE_CONSTEXPR
  #define BGA__MAYBE_CONSTEXPR
#endif


#include <!cpp/shim/nullptr.h>

#include <!cpp/wrapper/cstdint>
#include <!cpp/wrapper/climits>
#include <!cpp/wrapper/cstddef>
#include <!cpp/wrapper/type_traits>

#ifndef BGA__ASSERT_EQ
  #define BGA__ASSERT_EQ(aArg, bArg) do { (void)aArg; (void)bArg; } while(0);
  #define BGA__ASSERT_NEQ(aArg, bArg) do { (void)aArg; (void)bArg; } while(0);
  #define BGA__ASSERT_LT(aArg, bArg) do { (void)aArg; (void)bArg; } while(0);
  #define BGA__ASSERT_LTE(aArg, bArg) do { (void)aArg; (void)bArg; } while(0);
  #define BGA__ASSERT_HAS_BIT_MASK(aArg, bArg) do { (void)aArg; (void)bArg; } while(0);
  #define BGA__ASSERT_NOT_HAS_BIT_MASK(aArg, bArg) do { (void)aArg; (void)bArg; } while(0);
  #define BGA__ASSERT_TEST(aArg, testExprArg) do { (void)aArg; } while(0);
#endif

//#define override

typedef char Char;
typedef signed char SChar;
typedef unsigned char UChar;

typedef int8_t I8;
typedef uint8_t U8;
typedef int16_t I16;
typedef uint16_t U16;
typedef int32_t I32;
typedef uint32_t U32;
#ifdef UINT64_MAX
  typedef int64_t I64;
  typedef uint64_t U64;
  typedef int64_t I64_or_void;
  typedef uint64_t U64_or_void;
#else
  typedef void I64_or_void;
  typedef void U64_or_void;
#endif

typedef int_least8_t LI8;
typedef uint_least8_t LU8;
typedef int_least16_t LI16;
typedef uint_least16_t LU16;
typedef int_least32_t LI32;
typedef uint_least32_t LU32;
#ifdef UINT64_MAX
  typedef int_least64_t LI64;
  typedef uint_least64_t LU64;
  typedef int_least64_t LI64_or_void;
  typedef uint_least64_t LU64_or_void;
#else
  typedef void LI64_or_void;
  typedef void LU64_or_void;
#endif

typedef int_fast8_t FI8;
typedef uint_fast8_t FU8;
typedef int_fast16_t FI16;
typedef uint_fast16_t FU16;
typedef int_fast32_t FI32;
typedef uint_fast32_t FU32;
#ifdef UINT64_MAX
  typedef int_fast64_t FI64;
  typedef uint_fast64_t FU64;
  typedef int_fast64_t FI64_or_void;
  typedef uint_fast64_t FU64_or_void;
#else
  typedef void FI64_or_void;
  typedef void FU64_or_void;
#endif

typedef int Z;
typedef int Int;
typedef unsigned int UInt;
typedef intmax_t IntMax;
typedef uintmax_t UIntMax;

typedef void Void;
typedef bool Bool;

//# missed in standard csdtint. Add for unification
#ifndef UINT8_MIN
  #define UINT8_MIN UINT8_C(0)
#endif
#ifndef UINT16_MIN
  #define UINT16_MIN UINT16_C(0)
#endif
#ifndef UINT32_MIN
  #define UINT32_MIN UINT32_C(0)
#endif
#ifdef UINT64_MAX
  #ifndef UINT64_MIN
    #define UINT64_MIN UINT64_C(0)
  #endif
#endif

namespace Bga {

#ifndef BGA__INSPECT_TYPE

namespace details {
template<class TArg>
struct static_inspect_type__impl {
	
};
} //# namespace

#define BGA__INSPECT_TYPE(TArg) \
	struct BGA__UNIQUE_NAME { void dummy() { const ::Bga::details::static_inspect_type__impl< TArg > x(1); (void)x; } } \
;
#endif

template<class TArg, class DefaultTArg>
struct void_to_default {
  typedef TArg type;
};
template<class DefaultTArg>
struct void_to_default<void, DefaultTArg> {
  typedef DefaultTArg type;
};


template<class T> 
struct int_type_traits;
#define BGA__GEN_INT_TYPE_TRAIT(intPrefixArg, intPrefixUpperArg, numArg) \
  template<> struct int_type_traits<intPrefixArg ## numArg ## _t> { \
    typedef typename ::std::make_signed<intPrefixArg ## numArg ## _t>::type signed_type; \
    typedef typename ::std::make_unsigned<intPrefixArg ## numArg ## _t>::type unsigned_type; \
    \
    typedef intPrefixArg ## _fast ## numArg ## _t fast_type; \
    typedef typename ::std::make_signed<fast_type>::type int_fast_type; \
    typedef typename ::std::make_unsigned<fast_type>::type uint_fast_type; \
    \
    typedef BGA__CONCAT4(intPrefixArg, _least, numArg, _t) least_type; \
    typedef typename ::std::make_signed<least_type>::type int_least_type; \
    typedef typename ::std::make_unsigned<least_type>::type uint_least_type; \
    \
    static const intPrefixArg ## numArg ## _t min_value =  intPrefixUpperArg ## numArg ## _MIN; \
    static const intPrefixArg ## numArg ## _t max_value =  intPrefixUpperArg ## numArg ## _MAX; \
    \
    static const int bit_width = sizeof(intPrefixArg ## numArg ## _t) * CHAR_BIT; \
  } \
;

#define BGA__GEN_INT_TYPE_TRAIT__I_AND_U(numArg) \
  BGA__GEN_INT_TYPE_TRAIT(int, INT, numArg) \
  BGA__GEN_INT_TYPE_TRAIT(uint, UINT, numArg) \
;

BGA__GEN_INT_TYPE_TRAIT__I_AND_U(8);
BGA__GEN_INT_TYPE_TRAIT__I_AND_U(16);
BGA__GEN_INT_TYPE_TRAIT__I_AND_U(32);
#ifdef UINT64_MAX
  BGA__GEN_INT_TYPE_TRAIT__I_AND_U(64);
#endif

#undef BGA__GEN_INT_TYPE_TRAIT__I_AND_U
#undef BGA__GEN_INT_TYPE_TRAIT



namespace details {
template<unsigned bitWidthArg>
struct make_signed_from_bit_width {
  typedef typename ::std::conditional<bitWidthArg <= 8, I8, 
    typename ::std::conditional<bitWidthArg <= 16, I16, 
      typename ::std::conditional<bitWidthArg <= 32, I32, 
        typename ::std::conditional<bitWidthArg <= 64, I64_or_void, 
          void
        >::type
      >::type
    >::type
  >::type type;
};
} //# namespace

template<unsigned bitWidthArg, class FailArg = void>
struct make_signed_from_bit_width {
  typedef typename ::Bga::void_to_default<typename details::make_signed_from_bit_width<bitWidthArg>::type, FailArg>::type type;
};
template<unsigned bitWidthArg, class FailArg = void>
struct make_unsigned_from_bit_width {
  typedef typename ::std::make_unsigned<typename make_signed_from_bit_width<bitWidthArg, FailArg>::type>::type type;
};
template<class IntArg, unsigned bitWidthArg, class FailArg = void>
struct make_int_from_bit_width {
  typedef typename ::std::conditional< 
    ::std::is_unsigned<IntArg>::value, 
    typename make_unsigned_from_bit_width<bitWidthArg, FailArg>::type, 
    typename make_signed_from_bit_width<bitWidthArg, FailArg>::type
  >::type type;
};

template<class IntArg>
struct make_signed_half_int_nocv {
  typedef typename make_signed_from_bit_width<int_type_traits<IntArg>::bit_width / 2>::type type;
};
template<class IntArg>
struct make_unsigned_half_int_nocv {
  typedef typename ::std::make_unsigned<typename make_signed_half_int_nocv<IntArg>::type>::type type;
};
template<class IntArg, class FailArg = void>
struct make_signed_double_int_nocv {
  typedef typename make_signed_from_bit_width<int_type_traits<IntArg>::bit_width * 2, FailArg>::type type;
};
template<class IntArg, class FailArg = void>
struct make_unsigned_double_int_nocv {
  typedef typename ::std::make_unsigned<typename make_signed_double_int_nocv<IntArg, FailArg>::type>::type type;
};

template<class IntArg>
struct make_half_int_nocv {
  typedef typename ::std::conditional< ::std::is_signed<IntArg>::value, 
    typename make_signed_half_int_nocv<IntArg>::type, 
    typename make_unsigned_half_int_nocv<IntArg>::type 
  >::type type;
};

template<class IntArg, class FailArg = void>
struct make_double_int_nocv {
  typedef typename ::std::conditional< ::std::is_signed<IntArg>::value, 
    typename make_signed_double_int_nocv<IntArg, FailArg>::type, 
    typename make_unsigned_double_int_nocv<IntArg, FailArg>::type 
  >::type type;
};

} //# namespace

#define BGA__GEN_STATIC_ASSERT_XX_HELPER(nameArg, exprArg) \
	template<IntMax a, IntMax b> struct nameArg { \
		struct _ {  }; \
		typedef typename std::conditional<(exprArg), int, _>::type type; \
	};
#define BGA__STATIC_ASSERT_XX(nameArg, aArg, bArg) \
	struct BGA__UNIQUE_NAME { typename nameArg<(aArg), (bArg)>::type dummy() { return 1; } }

BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_lt_helper, a < b)
#define static_assert_lt(aArg, bArg) BGA__STATIC_ASSERT_XX(static_assert_lt_helper, (aArg), (bArg))

BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_lte_helper, a <= b)
#define static_assert_lte(aArg, bArg) BGA__STATIC_ASSERT_XX(static_assert_lte_helper, (aArg), (bArg))

BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_gt_helper, b < a)
#define static_assert_gt(aArg, bArg) BGA__STATIC_ASSERT_XX(static_assert_gt_helper, (aArg), (bArg))

BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_gte_helper, b <= a)
#define static_assert_gte(aArg, bArg) BGA__STATIC_ASSERT_XX(static_assert_gte_helper, (aArg), (bArg))

BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_eq_helper, a == b)
#define static_assert_eq(aArg, bArg) BGA__STATIC_ASSERT_XX(static_assert_eq_helper, (aArg), (bArg))

BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_neq_helper, a != b)
#define static_assert_neq(aArg, bArg) BGA__STATIC_ASSERT_XX(static_assert_neq_helper, (aArg), (bArg))

BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_hasBit_helper, a & (UIntMax(1) << b))
#define static_assert_hasBit(aArg, bArg) BGA__STATIC_ASSERT_XX(static_assert_hasBit_helper, (aArg), (bArg))

#if 0
  static_assert_test(1, x == 1 || x == 2); //# OK
  static_assert_test(2, x == 1 || x == 2); //# OK
  static_assert_test(3, x == 1 || x == 2); //# FAIL
#endif
BGA__GEN_STATIC_ASSERT_XX_HELPER(static_assert_test_helper, !!b)
#define static_assert_test(aArg, testAExprArg) struct BGA__UNIQUE_NAME { static const IntMax x = (aArg); BGA__STATIC_ASSERT_XX(static_assert_test_helper, x, (testAExprArg)); }

#if 0
  static_assert_type_eq(void, void) //# OK 
  static_assert_type_eq(void, int) //# FAIL 
#endif
template<class AArg, class BArg> 
struct static_assert_type_eq_helper {

};
template<class AArg> 
struct static_assert_type_eq_helper<AArg, AArg> {
	static_assert_type_eq_helper(int) {  }
};

#define static_assert_type_eq(AArg, BArg) \
	struct BGA__UNIQUE_NAME { void dummy() { const static_assert_type_eq_helper< AArg, BArg > x(1); } } \
;

#if 0
  static_assert_type_neq(void, int) //# OK 
  static_assert_type_neq(void, void) //# FAIL 
#endif
template<class AArg, class BArg> 
struct static_assert_type_neq_helper {
	static_assert_type_neq_helper(int) {  }
};
template<class AArg> 
struct static_assert_type_neq_helper<AArg, AArg> {

};

#define static_assert_type_neq(AArg, BArg) \
	struct BGA__UNIQUE_NAME { void dummy() { const static_assert_type_neq_helper< AArg, BArg > x(1); } } \
;


template<typename TArg> BGA__MAYBE_CONSTEXPR TArg Math_abs(const TArg& x) {
  #define BGA__MATH__ABS(x) (((x) < 0) ? -(x) : (x))
  return BGA__MATH__ABS(x);
}
template<typename AArg, typename BArg> BGA__MAYBE_CONSTEXPR AArg Math_min(const AArg& a, const BArg& b) {
  #define BGA__MATH__MIN(a, b) (((a) < (b)) ? (a) : (b))
  return BGA__MATH__MIN(a, b);
}
template<typename AArg, typename BArg> BGA__MAYBE_CONSTEXPR AArg Math_max(const AArg& a, const BArg& b) {
  #define BGA__MATH__MAX(a, b) (((a) < (b)) ? (b) : (a))
  return BGA__MATH__MAX(a, b);
}
template<typename AArg, typename XArg, typename BArg> BGA__MAYBE_CONSTEXPR XArg Math_clamp(const AArg& a, const XArg& x, const BArg& b) {
  #define BGA__MATH__CLAMP(a, x, b) BGA__MATH__MIN(BGA__MATH__MAX(x, a), b)
  return Math_min(Math_max(x, a), b);
}
template<typename TArg, typename AArg, typename BArg> BGA__MAYBE_CONSTEXPR TArg Math_lerp(const TArg& t, const AArg& a, const BArg& b) {
  #define BGA__MATH__LERP(t, a, b) ((t) * ((b) - (a)) + (a))
  return BGA__MATH__LERP(t, a, b);
}
template<class XIntArg, class AlignIntArg> 
BGA__MAYBE_CONSTEXPR typename ::std::enable_if<(::std::is_integral<XIntArg>::value), XIntArg>::type 
Math_floor(XIntArg x, AlignIntArg align) {
	#define BGA__MATH__FLOOR_INT(x, align) ((x) / (align) * (align))
  return BGA__MATH__FLOOR_INT(x, align);
}
template<class XIntArg, class AlignIntArg> 
BGA__MAYBE_CONSTEXPR typename ::std::enable_if<(::std::is_integral<XIntArg>::value), XIntArg>::type 
Math_ceil(XIntArg x, AlignIntArg align) {
	// #define BGA__MATH__CEIL(x, align) ((x) + (((x) < 0) ? -(align) + 1 : (align) - 1)) / (align) * (align) 
	#define BGA__MATH__CEIL(x, align) ((((x) < 0) ? (x) - (align) + 1 : (x) + (align) - 1) / (align) * (align)) 
  return BGA__MATH__CEIL(x, align);
}


namespace Bga { 

namespace details {
template<IntMax nArg, unsigned powArg> struct Pow { static const IntMax value = nArg * Pow<nArg, powArg - 1>::value; };
template<IntMax nArg> struct Pow<nArg, 0> { static const IntMax value = 1; };
} //# namespace
#define BGA__MATH__POW_INT(nArg, powArg) ::Bga::details::Pow<(nArg), (powArg)>::value 

namespace details {
template<UIntMax nArg, unsigned powArg> struct PowU { static const UIntMax value = nArg * PowU<nArg, powArg - 1>::value; };
template<UIntMax nArg> struct PowU<nArg, 0> { static const UIntMax value = 1; };
} //# namespace
#define BGA__MATH__POW_UINT(nArg, powArg) ::Bga::details::PowU<(nArg), (powArg)>::value 

namespace details {
template<UIntMax x, UIntMax y, UIntMax n, bool cond = ((n) < (sizeof(UIntMax) * CHAR_BIT) && (y << (n)) <= x)> struct Log2FloorImpl;
template<UIntMax x, UIntMax y, UIntMax n> struct Log2FloorImpl<x, y, n, false> { static const UIntMax value = n - 1; };
template<UIntMax x, UIntMax y, UIntMax n> struct Log2FloorImpl<x, y, n, true>: public Log2FloorImpl<x, y, n + 1> {};
template<UIntMax x, UIntMax y, BGA__TEMPLATE__ENABLE_IF(0 < x)> struct Log2Floor: public Log2FloorImpl<x, y, 0> {};

//# find n where yArg * 2 ** (n - 1) <= xArg < yArg * 2 ** n
#define BGA__MATH__INT_LOG2_FLOOR2(xArg, yArg) ( ::Bga::details::Log2Floor<(xArg), (yArg)>::value)

//# find n where yArg * 2 ** (n - 1) <= xArg < yArg * 2 ** n
#define BGA__MATH__INT_LOG2_FLOOR(xArg) BGA__MATH__INT_LOG2_FLOOR2(xArg, 1)

#ifdef BGA__TESTRUNNER_ON
	static_assert_eq(BGA__MATH__INT_LOG2_FLOOR(1), 0);
	static_assert_eq(BGA__MATH__INT_LOG2_FLOOR(2), 1);
	static_assert_eq(BGA__MATH__INT_LOG2_FLOOR(3), 1);
	static_assert_eq(BGA__MATH__INT_LOG2_FLOOR(4), 2);
	static_assert_eq(BGA__MATH__INT_LOG2_FLOOR(15), 3);
	static_assert_eq(BGA__MATH__INT_LOG2_FLOOR(16), 4);
	static_assert_eq(BGA__MATH__INT_LOG2_FLOOR(17), 4);
	static_assert_eq(BGA__MATH__INT_LOG2_FLOOR2(100 * 17, 100), 4);
#endif // BGA__TESTRUNNER_ON
} //# namespace

namespace details {
template<UIntMax x, UIntMax y, UIntMax n, bool cond = ((n) < (sizeof(UIntMax) * CHAR_BIT) && (y << (n)) < x)> struct Log2CeilImpl;
template<UIntMax x, UIntMax y, UIntMax n> struct Log2CeilImpl<x, y, n, false> { static const UIntMax value = n; };
template<UIntMax x, UIntMax y, UIntMax n> struct Log2CeilImpl<x, y, n, true>: public Log2CeilImpl<x, y, n + 1> {};
template<UIntMax x, UIntMax y, BGA__TEMPLATE__ENABLE_IF(0 < x)> struct Log2Ceil: public Log2CeilImpl<x, y, 0> {};

//# find n where yArg * 2 ** (n - 1) < xArg <= yArg * 2 ** n
#define BGA__MATH__INT_LOG2_CEIL2(xArg, yArg) ( ::Bga::details::Log2Ceil<(xArg), (yArg)>::value)

//# find n where 2 ** (n - 1) < xArg <= 2 ** n
#define BGA__MATH__INT_LOG2_CEIL(xArg) BGA__MATH__INT_LOG2_CEIL2(xArg, 1)

#ifdef BGA__TESTRUNNER_ON
	static_assert_eq(BGA__MATH__INT_LOG2_CEIL(1), 0);
	static_assert_eq(BGA__MATH__INT_LOG2_CEIL(2), 1);
	static_assert_eq(BGA__MATH__INT_LOG2_CEIL(3), 2);
	static_assert_eq(BGA__MATH__INT_LOG2_CEIL(4), 2);
	static_assert_eq(BGA__MATH__INT_LOG2_CEIL(15), 4);
	static_assert_eq(BGA__MATH__INT_LOG2_CEIL(16), 4);
	static_assert_eq(BGA__MATH__INT_LOG2_CEIL(17), 5);
	static_assert_eq(BGA__MATH__INT_LOG2_CEIL2(100 * 17, 100), 5);
#endif // BGA__TESTRUNNER_ON
} //# namespace

} //# namespace

#if 0
#include <!cpp/wrapper/cstdlib>
Int randomInt(Int a,  Int b) {
  return a + rand() % (b - a + 1);
}
#endif

typedef ptrdiff_t SSize;
typedef typename ::std::make_unsigned<SSize>::type Size;

template<class Type, Size n>
BGA__MAYBE_CONSTEXPR Size arraySize( Type (&)[n] ) {
  return n;
}
#if !BGA__IS_EMPTY_MACRO(BGA__MAYBE_CONSTEXPR)
  #define BGA__ARRAY_SIZE(arrayArg) arraySize( (arrayArg) )
#else
  #define BGA__ARRAY_SIZE(arrayArg) (sizeof((arrayArg)) / sizeof((arrayArg)[0]))
#endif

template<class DataArg, Size alignArg> struct AlignSize: public DataArg {
	Char BGA__UNIQUE_NAME[BGA__MATH__CEIL(sizeof(DataArg), alignArg) - sizeof(DataArg)];
};

#ifndef nop
  inline void nop() {

  }
#endif

#if 0
int x;
BGA__RUN {
  std::cout << "BGA__RUN" << std::endl;
}
#endif
#define BGA__RUN BGA__RUN_ID_IMPL(BGA__UNIQUE_ID)

#define BGA__RUN_ID_IMPL(idArg) BGA__RUN_IMPL(BGA__CONCAT(Run, idArg), BGA__CONCAT(runMethod, idArg), BGA__CONCAT(runInstance, idArg))
#define BGA__RUN_IMPL(_classNameArg, _methodNameArg, _instanceNameArg) \
void _methodNameArg(); \
class _classNameArg { \
  public: \
  _classNameArg() { \
    _methodNameArg(); \
  } \
} _instanceNameArg; \
void _methodNameArg()

//# macro for inspecting constant expr at compile time. Still produces error
//# TODO use warning
#if 0
  static_print(F_CPU / (1 << adcPrescaler))
#endif
/* BGA__PRAGMA(message(__FILE__ ":" BGA__STR(__LINE__) " " BGA__STR(exprArg) " =")) */ \
#ifdef BGA__ENABLE_STATIC_PRINT
  #define static_print(constExpr) \
    char (*BGA__CONCAT(__inspectInt_, BGA__UNIQUE_ID))[constExpr] = 1;
#else
  #define static_print(constExpr)
#endif
