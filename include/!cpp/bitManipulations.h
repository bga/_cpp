#pragma once
#include <stdint.h>
#include <!cpp/common.h>

#ifndef _BV
  #define _BV(bitNoArg) (1 << (bitNoArg))
#endif

#define bitsCountToMask(bitsCountArg) ((1 << (bitsCountArg)) - 1)

#define hasBit(vArg, bitNumberArg) (((vArg) & _BV((bitNumberArg))))

#ifndef clearBit
  #define clearBit(vArg, bitNumberArg) (((vArg) &= ~_BV((bitNumberArg))), (vArg))
#endif // clearBit

#ifndef setBit
  #define setBit(vArg, bitNumberArg) (((vArg) |= _BV((bitNumberArg))), (vArg))
#endif // setBit

#define toggleBit(vArg, bitNumberArg) (((vArg) ^= _BV((bitNumberArg))), (vArg))

#define setBitValue(vArg, bitNumberArg, bitValueArg) ((bitValueArg) ? setBit((vArg), (bitNumberArg)) : clearBit((vArg), (bitNumberArg)))

#define setBitMaskedValues(destArg, destShiftArg, maskArg, srcArg) (destArg) = ((destArg) & ~(maskArg << (destShiftArg))) | (((srcArg) & (maskArg)) << (destShiftArg))

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
void cycleInc(IntArg& vArg, const MaxIntArg& maxVArg) {
  if(isPowerOf2(maxVArg)) {
    vArg += 1;
    vArg &= maxVArg - 1;
  }
  else {
    vArg += 1;
    if(vArg == maxVArg) {
      vArg = 0;
    }
    else {

    }
  }
}

template<typename IntArg>
void cycleDec(IntArg& vArg, const IntArg& maxVArg) {
  if(isPowerOf2(maxVArg)) {
    vArg -= 1;
    vArg &= maxVArg - 1;
  }
  else {
    if(vArg == 0) {
      vArg = maxVArg - 1;
    }
    else {
      vArg += 1;
    }
  }
}


template<uintmax_t x> struct IntToMaskHelperClass {
  #define GEN_SHIFT(aArg, bArg, shiftArg) static const uintmax_t CONCAT(x, bArg) = CONCAT(x, aArg) | (CONCAT(x, aArg) >> ((((shiftArg) / 4) <= sizeof(uintmax_t)) ? (shiftArg) : 0));

  static const uintmax_t x1 = x;

  GEN_SHIFT(1, 2, 32)
  GEN_SHIFT(2, 3, 16)
  GEN_SHIFT(3, 4,  8)
  GEN_SHIFT(4, 5,  4)
  GEN_SHIFT(5, 6,  2)
  GEN_SHIFT(6, 7,  1)

  #undef GEN_SHIFT

  static const uintmax_t result = x7;
};

#define intToMaskConstExpr(xArg) IntToMaskHelperClass<(xArg)>::result

#define intToMaskConstExpr(xArg) IntToMaskHelperClass<(xArg)>::result
