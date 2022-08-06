#pragma once

#include "Types.hpp"

#define minVal(a, b)                      ((a) < (b) ? (a) : (b))
#define maxVal(a, b)                      ((a) > (b) ? (a) : (b))
#define clampVal(value, minimum, maximum) (((value) < (minimum)) ? (minimum) : (((value) > (maximum)) ? (maximum) : (value)))
#define fabs(a)                           ((a) > 0 ? (a) : -(a))

#define setBit(value, set, pos) ((value) ^= (-(int32)(set) ^ (value)) & (1 << (pos)))
#define getBit(b, pos)          ((b) >> (pos)&1)

#define intToVoid(x)   (void *)(size_t)(x)
#define floatToVoid(x) intToVoid(*(int32 *)&(x))
#define voidToInt(x)   (int32)(size_t)(x)
#define voidToFloat(x) *(float *)&(x)

#define unused(x) (void)x

namespace RSDK
{

namespace Math
{

inline int32 Sin1024(int32 angle) { return RSDKTable->Sin1024(angle); }
inline int32 Cos1024(int32 angle) { return RSDKTable->Cos1024(angle); }
inline int32 Tan1024(int32 angle) { return RSDKTable->Tan1024(angle); }
inline int32 ASin1024(int32 angle) { return RSDKTable->ASin1024(angle); }
inline int32 ACos1024(int32 angle) { return RSDKTable->ACos1024(angle); }
inline int32 Sin512(int32 angle) { return RSDKTable->Sin512(angle); }
inline int32 Cos512(int32 angle) { return RSDKTable->Cos512(angle); }
inline int32 Tan512(int32 angle) { return RSDKTable->Tan512(angle); }
inline int32 ASin512(int32 angle) { return RSDKTable->ASin512(angle); }
inline int32 ACos512(int32 angle) { return RSDKTable->ACos512(angle); }
inline int32 Sin256(int32 angle) { return RSDKTable->Sin256(angle); }
inline int32 Cos256(int32 angle) { return RSDKTable->Cos256(angle); }
inline int32 Tan256(int32 angle) { return RSDKTable->Tan256(angle); }
inline int32 ASin256(int32 angle) { return RSDKTable->ASin256(angle); }
inline int32 ACos256(int32 angle) { return RSDKTable->ACos256(angle); }

inline int32 Rand(int32 min, int32 max) { return RSDKTable->Rand(min, max); }
inline int32 RandSeeded(int32 min, int32 max, int32 *seed) { return RSDKTable->RandSeeded(min, max, seed); }
inline void SetRandSeed(int32 seed) { RSDKTable->SetRandSeed(seed); }

inline uint8 ATan2(int32 x, int32 y) { return RSDKTable->ATan2(x, y); }

} // namespace Math

} // namespace RSDK
