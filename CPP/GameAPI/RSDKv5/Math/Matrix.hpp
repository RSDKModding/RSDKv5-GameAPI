#pragma once

#include "Types.hpp"

namespace RSDK
{

struct Matrix {
    Matrix() {}
    Matrix(Matrix &other) { Matrix::Copy(this, &other); }

    int32 values[4][4];

    inline void SetIdentity() { RSDKTable->SetIdentityMatrix(this); }
    inline void TranslateXYZ(int32 x, int32 y, int32 z, bool32 setIdentity = true) { RSDKTable->MatrixTranslateXYZ(x, y, z, setIdentity); }
    inline void ScaleXYZ(int32 scaleX, int32 scaleY, int32 scaleZ) { RSDKTable->MatrixScaleXYZ(this, scaleX, scaleY, scaleZ); }
    inline void RotateX(int32 angle) {RSDKTable->MatrixRotateX(this, angle); }
    inline void RotateY(int32 angle) {RSDKTable->MatrixRotateX(this, angle); }
    inline void RotateZ(int32 angle) {RSDKTable->MatrixRotateX(this, angle); }
    inline void RotateXYZ(int32 angleX, int32 angleY, int32 angleZ) { RSDKTable->MatrixRotateXYZ(this, angleX, angleY, angleZ); }
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
