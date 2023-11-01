#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

namespace RSDK
{
struct Vector2 {
    // FixedPoint x;
    // FixedPoint y;
    //
    // inline Vector2() : x(0), y(0){};
    // inline Vector2(FixedPoint X, FixedPoint Y) : x(X), y(Y){};

    int32 x;
    int32 y;

    inline Vector2() : x(0), y(0){};
    inline Vector2(int32 X, int32 Y) : x(X), y(Y){};

    inline bool32 CheckOnScreen(Vector2 *range) { return RSDKTable->CheckPosOnScreen(this, range); }
};
} // namespace RSDK
