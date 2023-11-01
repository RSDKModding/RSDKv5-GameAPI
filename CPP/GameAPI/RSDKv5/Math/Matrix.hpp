#pragma once

#include "../Types.hpp"

namespace RSDK
{

struct Matrix {
    Matrix() {}
    Matrix(Matrix &other) { Matrix::Copy(this, &other); }

    int32 values[4][4];

    inline void SetIdentity() { RSDKTable->SetIdentityMatrix(this); }
    inline void TranslateXYZ(int32 x, int32 y, int32 z, bool32 setIdentity = true) { RSDKTable->MatrixTranslateXYZ(this, x, y, z, setIdentity); }
    inline void ScaleXYZ(int32 x, int32 y, int32 z) { RSDKTable->MatrixScaleXYZ(this, x, y, z); }
    inline void RotateX(int32 angle) { RSDKTable->MatrixRotateX(this, angle); }
    inline void RotateY(int32 angle) { RSDKTable->MatrixRotateX(this, angle); }
    inline void RotateZ(int32 angle) { RSDKTable->MatrixRotateX(this, angle); }
    inline void RotateXYZ(int32 x, int32 y, int32 z) { RSDKTable->MatrixRotateXYZ(this, x, y, z); }
    inline void Inverse() { RSDKTable->MatrixInverse(this, this); }

    static inline void Multiply(Matrix *dest, Matrix *matrixA, Matrix *matrixB) { RSDKTable->MatrixMultiply(dest, matrixA, matrixB); }
    static inline void Copy(Matrix *matDest, Matrix *matSrc) { RSDKTable->MatrixCopy(matDest, matSrc); }
    static inline void Inverse(Matrix *dest, Matrix *matrix) { RSDKTable->MatrixInverse(dest, matrix); }

    inline Matrix &operator*=(Matrix &other)
    {
        Matrix::Multiply(this, this, &other);
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
