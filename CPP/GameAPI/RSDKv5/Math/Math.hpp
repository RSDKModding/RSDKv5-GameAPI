#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

#define MIN(a, b)                      ((a) < (b) ? (a) : (b))
#define MAX(a, b)                      ((a) > (b) ? (a) : (b))
#define CLAMP(value, minimum, maximum) (((value) < (minimum)) ? (minimum) : (((value) > (maximum)) ? (maximum) : (value)))
#define FABS(a)                        ((a) > 0 ? (a) : -(a))

#define SET_BIT(value, set, pos) ((value) ^= (-(int32)(set) ^ (value)) & (1 << (pos)))
#define GET_BIT(b, pos)          ((b) >> (pos)&1)

#define INT_TO_VOID(x)   (void *)(size_t)(x)
#define FLOAT_TO_VOID(x) INT_TO_VOID(*(int32 *)&(x))
#define VOID_TO_INT(x)   (int32)(size_t)(x)
#define VOID_TO_FLOAT(x) *(float *)&(x)

#define UNUSED(x) (void)x

// floating point variants
#define TO_FIXED_F(x)   ((x)*65536.0)
#define FROM_FIXED_F(x) ((x) / 65536.0)

#define TO_FIXED(x)   ((int)TO_FIXED_F(x))
#define FROM_FIXED(x) ((int)FROM_FIXED_F(x))

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
