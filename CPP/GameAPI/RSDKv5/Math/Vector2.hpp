#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

namespace GameAPI::RSDK
{
struct Vector2 {
    // FixedPoint x;
    // FixedPoint y;
    //
    // RSDK_FORCE_INLINE Vector2() : x(0), y(0){};
    // RSDK_FORCE_INLINE Vector2(FixedPoint X, FixedPoint Y) : x(X), y(Y){};

    int32 x;
    int32 y;

    RSDK_FORCE_INLINE Vector2() : x(0), y(0) {};
    RSDK_FORCE_INLINE Vector2(int32 X, int32 Y) : x(X), y(Y) {};

    RSDK_FORCE_INLINE Vector2 &operator+=(Vector2 other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }
    RSDK_FORCE_INLINE Vector2 &operator-=(Vector2 other)
    {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    friend RSDK_FORCE_INLINE Vector2 operator+(Vector2 lhs, Vector2 rhs)
    {
        lhs += rhs;
        return lhs;
    }
    friend RSDK_FORCE_INLINE Vector2 operator-(Vector2 lhs, Vector2 rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    RSDK_FORCE_INLINE bool32 CheckOnScreen(Vector2 *range) { return RSDKTable->CheckPosOnScreen(this, range); }
};
} // namespace GameAPI::RSDK
