#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

namespace GameAPI::RSDK
{
union FixedPoint {
    FixedPoint() { value = 0; }
    FixedPoint(int32 val) { value = val; }
    FixedPoint(uint32 val) { value = val; }

    RSDK_FORCE_INLINE FixedPoint &operator++()
    {
        this->whole++;
        return *this;
    }

    RSDK_FORCE_INLINE FixedPoint &operator--()
    {
        this->whole--;
        return *this;
    }

    RSDK_FORCE_INLINE FixedPoint operator++(int32)
    {
        FixedPoint ref(*this);
        this->whole++;
        return ref;
    }
    RSDK_FORCE_INLINE FixedPoint operator--(int32)
    {
        FixedPoint ref(*this);
        this->whole--;
        return ref;
    }

    RSDK_FORCE_INLINE FixedPoint &operator+=(FixedPoint &other)
    {
        this->value += other.value;
        return *this;
    }
    RSDK_FORCE_INLINE FixedPoint &operator+=(int32 other)
    {
        this->value += other;
        return *this;
    }

    RSDK_FORCE_INLINE FixedPoint &operator-=(FixedPoint &other)
    {
        this->value -= other.value;
        return *this;
    }
    RSDK_FORCE_INLINE FixedPoint &operator-=(int32 other)
    {
        this->value -= other;
        return *this;
    }

    RSDK_FORCE_INLINE FixedPoint &operator*=(FixedPoint &other)
    {
        this->value *= other.value;
        return *this;
    }
    RSDK_FORCE_INLINE FixedPoint &operator*=(int32 other)
    {
        this->value *= other;
        return *this;
    }

    RSDK_FORCE_INLINE FixedPoint &operator/=(FixedPoint &other)
    {
        this->value /= other.value;
        return *this;
    }
    RSDK_FORCE_INLINE FixedPoint &operator/=(int32 other)
    {
        this->value /= other;
        return *this;
    }

    RSDK_FORCE_INLINE FixedPoint &operator<<=(FixedPoint &other)
    {
        this->value <<= other.value;
        return *this;
    }
    RSDK_FORCE_INLINE FixedPoint &operator<<=(int32 other)
    {
        this->value <<= other;
        return *this;
    }

    RSDK_FORCE_INLINE FixedPoint &operator>>=(FixedPoint &other)
    {
        this->value >>= other.value;
        return *this;
    }
    RSDK_FORCE_INLINE FixedPoint &operator>>=(int32 other)
    {
        this->value >>= other;
        return *this;
    }

    RSDK_FORCE_INLINE FixedPoint &operator|=(int32 other)
    {
        this->value |= other;
        return *this;
    }

    RSDK_FORCE_INLINE FixedPoint &operator|=(FixedPoint &other)
    {
        this->value |= other.value;
        return *this;
    }

    RSDK_FORCE_INLINE FixedPoint &operator&=(int32 other)
    {
        this->value &= other;
        return *this;
    }

    RSDK_FORCE_INLINE FixedPoint &operator&=(FixedPoint &other)
    {
        this->value &= other.value;
        return *this;
    }

    RSDK_FORCE_INLINE FixedPoint &operator^=(int32 other)
    {
        this->value ^= other;
        return *this;
    }

    RSDK_FORCE_INLINE FixedPoint &operator^=(FixedPoint &other)
    {
        this->value ^= other.value;
        return *this;
    }

    friend RSDK_FORCE_INLINE FixedPoint operator+(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value + rhs.value); }
    friend RSDK_FORCE_INLINE FixedPoint operator-(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value - rhs.value); }
    friend RSDK_FORCE_INLINE FixedPoint operator*(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value * rhs.value); }
    friend RSDK_FORCE_INLINE FixedPoint operator/(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value / rhs.value); }
    friend RSDK_FORCE_INLINE FixedPoint operator<<(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value << rhs.value); }
    friend RSDK_FORCE_INLINE FixedPoint operator>>(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value >> rhs.value); }
    friend RSDK_FORCE_INLINE FixedPoint operator|(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value | rhs.value); }
    friend RSDK_FORCE_INLINE FixedPoint operator&(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value & rhs.value); }
    friend RSDK_FORCE_INLINE FixedPoint operator^(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value ^ rhs.value); }

    friend RSDK_FORCE_INLINE bool operator<(FixedPoint &lhs, FixedPoint &rhs) { return lhs.value < rhs.value; }
    friend RSDK_FORCE_INLINE bool operator>(FixedPoint &lhs, FixedPoint &rhs) { return lhs.value > rhs.value; }

    operator int32() const { return value; }

    struct {
        int16 fractional;
        int16 whole;
    };

private:
    int32 value;
};
} // namespace GameAPI::RSDK