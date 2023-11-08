#pragma once

#include "../Types.hpp"

namespace RSDK
{
union FixedPoint {
    FixedPoint() { value = 0; }
    FixedPoint(int32 val) { value = val; }
    FixedPoint(uint32 val) { value = val; }

    inline FixedPoint &operator++()
    {
        this->whole++;
        return *this;
    }

    inline FixedPoint &operator--()
    {
        this->whole--;
        return *this;
    }

    inline FixedPoint operator++(int32)
    {
        FixedPoint ref(*this);
        this->whole++;
        return ref;
    }
    inline FixedPoint operator--(int32)
    {
        FixedPoint ref(*this);
        this->whole--;
        return ref;
    }

    inline FixedPoint &operator+=(FixedPoint &other)
    {
        this->value += other.value;
        return *this;
    }
    inline FixedPoint &operator+=(int32 other)
    {
        this->value += other;
        return *this;
    }

    inline FixedPoint &operator-=(FixedPoint &other)
    {
        this->value -= other.value;
        return *this;
    }
    inline FixedPoint &operator-=(int32 other)
    {
        this->value -= other;
        return *this;
    }

    inline FixedPoint &operator*=(FixedPoint &other)
    {
        this->value *= other.value;
        return *this;
    }
    inline FixedPoint &operator*=(int32 other)
    {
        this->value *= other;
        return *this;
    }

    inline FixedPoint &operator/=(FixedPoint &other)
    {
        this->value /= other.value;
        return *this;
    }
    inline FixedPoint &operator/=(int32 other)
    {
        this->value /= other;
        return *this;
    }

    inline FixedPoint &operator<<=(FixedPoint &other)
    {
        this->value <<= other.value;
        return *this;
    }
    inline FixedPoint &operator<<=(int32 other)
    {
        this->value <<= other;
        return *this;
    }

    inline FixedPoint &operator>>=(FixedPoint &other)
    {
        this->value >>= other.value;
        return *this;
    }
    inline FixedPoint &operator>>=(int32 other)
    {
        this->value >>= other;
        return *this;
    }

    inline FixedPoint &operator|=(int32 other)
    {
        this->value |= other;
        return *this;
    }

    inline FixedPoint &operator|=(FixedPoint &other)
    {
        this->value |= other.value;
        return *this;
    }

    inline FixedPoint &operator&=(int32 other)
    {
        this->value &= other;
        return *this;
    }

    inline FixedPoint &operator&=(FixedPoint &other)
    {
        this->value &= other.value;
        return *this;
    }

    inline FixedPoint &operator^=(int32 other)
    {
        this->value ^= other;
        return *this;
    }

    inline FixedPoint &operator^=(FixedPoint &other)
    {
        this->value ^= other.value;
        return *this;
    }

    friend inline FixedPoint operator+(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value + rhs.value); }
    friend inline FixedPoint operator-(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value - rhs.value); }
    friend inline FixedPoint operator*(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value * rhs.value); }
    friend inline FixedPoint operator/(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value / rhs.value); }
    friend inline FixedPoint operator<<(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value << rhs.value); }
    friend inline FixedPoint operator>>(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value >> rhs.value); }
    friend inline FixedPoint operator|(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value | rhs.value); }
    friend inline FixedPoint operator&(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value & rhs.value); }
    friend inline FixedPoint operator^(FixedPoint &lhs, FixedPoint &rhs) { return FixedPoint(lhs.value ^ rhs.value); }

    friend inline bool operator<(FixedPoint &lhs, FixedPoint &rhs) { return lhs.value < rhs.value; }
    friend inline bool operator>(FixedPoint &lhs, FixedPoint &rhs) { return lhs.value > rhs.value; }

    operator int32() const { return value; }

    struct {
        int16 fractional;
        int16 whole;
    };

private:
    int32 value;
};
} // namespace RSDK