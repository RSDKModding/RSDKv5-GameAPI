#pragma once

#include "../Types.hpp"
#include "../EngineAPI.hpp"

namespace GameAPI::RSDK
{

struct Matrix {
    Matrix() : values() {}
    Matrix(const Matrix &other) = default;

    int32 values[4][4];

    RSDK_FORCE_INLINE void SetIdentity() { RSDKTable->SetIdentityMatrix(this); }
    RSDK_FORCE_INLINE void TranslateXYZ(int32 x, int32 y, int32 z, bool32 setIdentity = true) { RSDKTable->MatrixTranslateXYZ(this, x, y, z, setIdentity); }
    RSDK_FORCE_INLINE void ScaleXYZ(int32 x, int32 y, int32 z) { RSDKTable->MatrixScaleXYZ(this, x, y, z); }
    RSDK_FORCE_INLINE void RotateX(int32 angle) { RSDKTable->MatrixRotateX(this, angle); }
    RSDK_FORCE_INLINE void RotateY(int32 angle) { RSDKTable->MatrixRotateY(this, angle); }
    RSDK_FORCE_INLINE void RotateZ(int32 angle) { RSDKTable->MatrixRotateZ(this, angle); }
    RSDK_FORCE_INLINE void RotateXYZ(int32 x, int32 y, int32 z) { RSDKTable->MatrixRotateXYZ(this, x, y, z); }
    RSDK_FORCE_INLINE void Inverse() { RSDKTable->MatrixInverse(this, this); }

    static RSDK_FORCE_INLINE void Multiply(Matrix *dest, Matrix *matrixA, Matrix *matrixB) { RSDKTable->MatrixMultiply(dest, matrixA, matrixB); }
    static RSDK_FORCE_INLINE void Transpose(Matrix *matDest, Matrix *matSrc) { RSDKTable->MatrixTranspose(matDest, matSrc); }
    static RSDK_FORCE_INLINE void Inverse(Matrix *dest, Matrix *matrix) { RSDKTable->MatrixInverse(dest, matrix); }

    RSDK_FORCE_INLINE int32 *operator[](int32 index) { return values[index]; }
    RSDK_FORCE_INLINE const int32 *operator[](int32 index) const { return values[index]; }

    RSDK_FORCE_INLINE Matrix &operator*=(const Matrix &other)
    {
        Matrix temporary = { *this };
        Matrix::Multiply(this, &temporary, const_cast<Matrix *>(&other));
        return *this;
    }

    friend RSDK_FORCE_INLINE Matrix operator*(Matrix &lhs, Matrix &rhs)
    {
        Matrix dest;
        Matrix::Multiply(&dest, &lhs, &rhs);
        return dest;
    }
};

} // namespace GameAPI::RSDK
