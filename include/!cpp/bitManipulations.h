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
#include <!cpp/wrapper/cstdint>
#include <!cpp/common.h>

#ifdef _BV
  #undef _BV
#endif
#if !BGA__IS_EMPTY_MACRO(BGA__MAYBE_CONSTEXPR)
  constexpr inline UIntMax _BV(unsigned bitNo) {
    return UIntMax(1) << bitNo;
  }
#else
  #define _BV(bitNoArg) (UIntMax(1) << (bitNoArg))
#endif

#define bitsCountToMask(bitsCountArg) ((UIntMax(1) << (bitsCountArg)) - 1)
#define hasBit(vArg, bitNumberArg) (((vArg) & _BV((bitNumberArg))))
#define hasBitMask(vArg, bitNumberArg) (((vArg) & (bitNumberArg)))

template<class TArg>
inline TArg clearBit(TArg& vArg, unsigned bitNumberArg) {
  vArg &= ~(TArg(1) << bitNumberArg);
  return vArg;
}
template<class TArg, class T2Arg>
inline TArg clearBitMask(TArg& vArg, T2Arg maskArg) {
  vArg &= ~maskArg;
  return vArg;
}

template<class TArg>
inline TArg setBit(TArg& vArg, unsigned bitNumberArg) {
  vArg |= (TArg(1) << bitNumberArg);
  return vArg;
}
template<class TArg, class T2Arg>
inline TArg setBitMask(TArg& vArg, T2Arg maskArg) {
  vArg |= maskArg;
  return vArg;
}

template<class TArg>
inline TArg toggleBit(TArg& vArg, unsigned bitNumberArg) {
  return (vArg ^= (TArg(1) << bitNumberArg));
}
template<class TArg, class T2Arg>
TArg toggleBitMask(TArg& vArg, T2Arg maskArg) {
  vArg ^= maskArg;
  return vArg;
}

template<class TArg>
inline TArg setBitValue(TArg& vArg, unsigned bitNumberArg, bool isSet) {
  return (isSet) ? setBit(vArg, bitNumberArg) : clearBit(vArg, bitNumberArg);
}
template<class TArg, class T2Arg>
inline TArg setBitMaskValueDirect(TArg& vArg, T2Arg maskArg, T2Arg setMaskArg) {
  vArg &= ~maskArg;
  vArg |= setMaskArg;
  return vArg;
}
template<class TArg, class T2Arg>
inline TArg setBitMaskValue(TArg& vArg, T2Arg maskArg, bool isSet) {
  return (isSet) ? setBitMask(vArg, maskArg) : clearBitMask(vArg, maskArg);
}

template<class TArg, class T2Arg, class T3Arg>
inline TArg setBitMaskedValues(TArg& destArg, unsigned destShiftArg, T2Arg maskArg, T3Arg srcArg) {
  destArg &= ~(maskArg << destShiftArg);
  destArg |= ((srcArg & maskArg) << destShiftArg);
  return destArg;
}

#define makeU32leFrom4U8(b3, b2, b1, b0) (((FU32)(b0)) | (((FU32)(b1)) << 8) | (((FU32)(b2)) << 16) | (((FU32)(b3)) << 24))
#define makeU32beFrom4U8(b3, b2, b1, b0) (((FU32)(b3)) | (((FU32)(b2)) << 8) | (((FU32)(b1)) << 16) | (((FU32)(b0)) << 24))
#define makeU32leFrom2U16le(b1, b0) (((FU32)(b1)) | (((FU32)(b0)) << 16))
#define makeU32leFrom2U16be(b1, b0) (((FU32)(staticSwapBytes16(b1))) | (((FU32)(staticSwapBytes16(b0))) << 16))
#define makeU32beFrom2U16be(b1, b0) (((FU32)(b0)) | (((FU32)(b1)) << 16))
#define makeU32beFrom2U16le(b1, b0) (((FU32)(staticSwapBytes16(b0))) | (((FU32)(staticSwapBytes16(b1))) << 16))

namespace BitRotate {
  template<typename TArg> struct getTotalBitsCount;
  template<> struct getTotalBitsCount<uint8_t> {
    static const int value = 8;
  };
  template<> struct getTotalBitsCount<uint16_t> {
    static const int value = 16;
  };
  template<> struct getTotalBitsCount<uint32_t> {
    static const int value = 32;
  };
  #ifdef UINT64_MAX
		template<> struct getTotalBitsCount<uint64_t> {
			static const int value = 64;
		};
	#endif
} // namespace BitRotate

template<typename TArg> inline TArg bitRotateLeft(TArg v, unsigned int n) {
  using namespace BitRotate;
  const int totalBitsCount = getTotalBitsCount<TArg>::value;
  return (v << n) | (v >> (totalBitsCount - n));
}
template<typename TArg> inline TArg bitRotateRight(TArg v, unsigned int n) {
  using namespace BitRotate;
  const int totalBitsCount = getTotalBitsCount<TArg>::value;
  return (v >> n) | (v << (totalBitsCount - n));
}

//# [https://stackoverflow.com/a/776523]
#if defined(__x86_64__) || defined(__i386__)
#ifdef _MSC_VER
  #include <intrin.h>
#else
  #include <x86intrin.h>  // Not just <immintrin.h> for compilers other than icc
#endif


template<> inline uint32_t bitRotateLeft(uint32_t v, unsigned int n) {
  return _rotl(v, n);  // gcc, icc, msvc.  Intel-defined.
}
template<> inline uint32_t bitRotateRight(uint32_t v, unsigned int n) {
  return _rotr(v, n);  // gcc, icc, msvc.  Intel-defined.
}

#if 0
#ifdef UINT64_MAX
  template<> inline uint64_t bitRotateLeft(uint64_t v, unsigned int n) {
    return _rotl64(v, n);  // gcc, icc, msvc.  Intel-defined.
  }
  template<> inline uint64_t bitRotateRight(uint64_t v, unsigned int n) {
    return _rotr64(v, n);  // gcc, icc, msvc.  Intel-defined.
  }
#endif
#endif
#endif

template<typename TArg> inline TArg bitRotate(TArg v, int n) {
  using namespace BitRotate;
  return (n < 0) ? bitRotateRight(v, -n) : bitRotateLeft(v, n);
}

template<typename IntArg>
IntArg changeByteEndian(IntArg x);

#define staticSwapBytes16(x) ((U16(U8((x) >> 0)) << 8) | (U16(U8((x) >> 8)) << 8))

inline uint16_t changeByteEndian(uint16_t x) {
  return staticSwapBytes16(x);
}

#define staticSwapBytes32(x) ((U32(U8((x) >> 0)) << 24) | (U32(U8((x) >> 8)) << 16) | (U32(U8((x) >> 16)) << 8) | (U32(U8((x) >> 24)) << 0))
inline uint32_t changeByteEndian(uint32_t x) {
  return staticSwapBytes32(x);
}

#ifdef UINT64_MAX
  #define staticSwapBytes64(x) (U64(U8((x) >> 0)) << 56) | (U64(U8((x) >> 8)) << 48) | (U64(U8((x) >> 16)) << 40) | (U64(U8((x) >> 24)) << 32) | (U64(U8((x) >> 32)) << 24) | (U64(U8((x) >> 40)) << 16) | (U64(U8((x) >> 48)) << 8) | (U64(U8((x) >> 56)) << 0);
  inline uint64_t changeByteEndian(uint64_t x) {
    return staticSwapBytes64(x);
  }
#endif


#define isPowerOf2(vArg) (((vArg) & ((vArg) - 1)) == 0)
template<typename IntArg, typename MaxIntArg>
inline IntArg cycleInc(IntArg& vArg, const MaxIntArg& maxVArg) {
  if(isPowerOf2(maxVArg)) {
    vArg += 1;
    vArg &= maxVArg - 1;
  }
  else {
    vArg += 1;
    if(maxVArg <= vArg) {
      vArg = 0;
    }
    else {

    }
  }
  return vArg;
}

template<typename IntArg>
inline void cycleDec(IntArg& vArg, const IntArg& maxVArg) {
  if(isPowerOf2(maxVArg)) {
    vArg -= 1;
    vArg &= maxVArg - 1;
  }
  else {
    if(vArg <= 0) {
      vArg = maxVArg - 1;
    }
    else {
      vArg -= 1;
    }
  }
}


namespace Bga { namespace details { 
template<UIntMax x> struct IntToMaskHelperClass {
  #define BGA__INT_TO_MASK__GEN_SHIFT(aArg, bArg, shiftArg) static const UIntMax BGA__CONCAT(x, bArg) = BGA__CONCAT(x, aArg) | (BGA__CONCAT(x, aArg) >> ((((shiftArg) * 2 / CHAR_BIT) <= sizeof(UIntMax)) ? (shiftArg) : 0));

  static const UIntMax x1 = x;

  BGA__INT_TO_MASK__GEN_SHIFT(1, 2, 32)
  BGA__INT_TO_MASK__GEN_SHIFT(2, 3, 16)
  BGA__INT_TO_MASK__GEN_SHIFT(3, 4,  8)
  BGA__INT_TO_MASK__GEN_SHIFT(4, 5,  4)
  BGA__INT_TO_MASK__GEN_SHIFT(5, 6,  2)
  BGA__INT_TO_MASK__GEN_SHIFT(6, 7,  1)

  #undef BGA__INT_TO_MASK__GEN_SHIFT

  static const UIntMax result = x7;
};
} } //# namespace

#define intToMaskConstExpr(xArg) (::Bga::details::IntToMaskHelperClass<(xArg)>::result)

#ifdef BGA__TESTRUNNER_ON
  static_assert_eq(intToMaskConstExpr(0), 0);
  static_assert_eq(intToMaskConstExpr(1), 1);
  static_assert_eq(intToMaskConstExpr(2), 3);
  static_assert_eq(intToMaskConstExpr(3), 3);
  static_assert_eq(intToMaskConstExpr(4), 7);
  static_assert_eq(intToMaskConstExpr(6), 7);
  static_assert_eq(intToMaskConstExpr(7), 7);
  static_assert_eq(intToMaskConstExpr(8), 15);
#endif
