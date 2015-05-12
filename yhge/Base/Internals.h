#ifndef YH_BASE_INTERNALS_H_
#define YH_BASE_INTERNALS_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"


NS_CC_YHGE_BEGIN

////////////////////////////////////////////////////////////////////////////////////
//大端小端定义
////////////////////////////////////////////////////////////////////////////////////

enum Endianness {
  kLittleEndian,  // _Not_ LITTLE_ENDIAN, clashes with endian.h.
  kBigEndian
};

static inline enum Endianness getEndianness() {
  // Constant-folded by the compiler.
  const union {
    uint8_t u8[2];
    uint16_t u16;
  } u = {
    { 1, 0 }
  };
  return u.u16 == 1 ? kLittleEndian : kBigEndian;
}

static inline bool isLittleEndian() {
  return getEndianness() == kLittleEndian;
}

static inline bool isBigEndian() {
  return getEndianness() == kBigEndian;
}

////////////////////////////////////////////////////////////////////////////////////
//浮点转换
////////////////////////////////////////////////////////////////////////////////////
typedef unsigned char byte_t;

//反向字节序
static inline void swizzle(byte_t* start, unsigned int len) {
    byte_t* end = start + len - 1;
    while (start < end) {
        byte_t tmp = *start;
        *start++ = *end;
        *end-- = tmp;
    }
}

template <typename T>
union _FloatConvertUnion {
    T val;
    byte_t bytes[sizeof(T)];
};

//字节转成浮点
template <typename T, enum Endianness endianness>
static inline T byteToFloat(byte_t* buf) {
    
    union _FloatConvertUnion<T> na;
    memcpy(na.bytes, buf, sizeof(na.bytes));
    if (endianness != getEndianness())
        swizzle(na.bytes, sizeof(na.bytes));
    
    return na.val;
}

//浮点转成字节
template <typename T, enum Endianness endianness>
static inline size_t floatToByte(T val,byte_t* buf) {
    
    union _FloatConvertUnion<T> na = { val };
    if (endianness != getEndianness())
        swizzle(na.bytes, sizeof(na.bytes));
    memcpy(buf, na.bytes, sizeof(na.bytes));
    return sizeof(na.bytes);
}


//类型转换，主要是整型，浮点之间的转换
template <typename From, typename To>
union _TypeConvertUnion{
    From from;
    To to;
};

template <typename From, typename To>
static inline To bitwise_cast(From from) {
    CCAssert((sizeof(From) == sizeof(To)), "TypeSizeNotEqual");
    
    union _TypeConvertUnion<From,To> u;
    u.from = from;
    return u.to;
}

NS_CC_YHGE_END

#endif //YH_BASE_INTERNALS_H_