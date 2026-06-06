#pragma once

#include "../Types.hpp"

namespace RSDK
{

struct Matrix {
    Matrix() : values() {}
    Matrix(const Matrix &other) = default;

    int32 values[4][4];

    inline void SetIdentity() { RSDKTable->SetIdentityMatrix(this); }
    inline void TranslateXYZ(int32 x, int32 y, int32 z, bool32 setIdentity = true) { RSDKTable->MatrixTranslateXYZ(this, x, y, z, setIdentity); }
    inline void ScaleXYZ(int32 x, int32 y, int32 z) { RSDKTable->MatrixScaleXYZ(this, x, y, z); }
    inline void RotateX(int32 angle) { RSDKTable->MatrixRotateX(this, angle); }
    inline void RotateY(int32 angle) { RSDKTable->MatrixRotateY(this, angle); }
    inline void RotateZ(int32 angle) { RSDKTable->MatrixRotateZ(this, angle); }
    inline void RotateXYZ(int32 x, int32 y, int32 z) { RSDKTable->MatrixRotateXYZ(this, x, y, z); }
    inline void Inverse() { RSDKTable->MatrixInverse(this, this); }

    static inline void Multiply(Matrix *dest, Matrix *matrixA, Matrix *matrixB) { RSDKTable->MatrixMultiply(dest, matrixA, matrixB); }
    static inline void Transpose(Matrix *matDest, Matrix *matSrc) { RSDKTable->MatrixTranspose(matDest, matSrc); }
    static inline void Inverse(Matrix *dest, Matrix *matrix) { RSDKTable->MatrixInverse(dest, matrix); }

    inline int32 *operator[](int32 index) { return values[index]; }
    inline const int32 *operator[](int32 index) const { return values[index]; }

    inline Matrix &operator*=(const Matrix &other)
    {
        Matrix temporary = { *this };
        Matrix::Multiply(this, &temporary, const_cast<Matrix *>(&other));
        return *this;
    }

    friend inline Matrix operator*(Matrix &lhs, Matrix &rhs)
    {
        Matrix dest;
        Matrix::Multiply(&dest, &lhs, &rhs);
        return dest;
    }
};

} // namespace RSDK
