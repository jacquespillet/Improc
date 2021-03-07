#ifndef MATHS
#define MATHS 1

#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef float f32;
typedef double f64;

typedef bool b32;

//TODO(Jacques)
// Test Matrix / Vector multiplication

//Write matrix transpose
//Write Translate()
//Write RotateX()
//Write RotateY()
//Write Scale()
//Write Cross()
//Write Reflect()

f32 Cosine(f32 Input);
f32 Sine(f32 Input);
f32 Tangent(f32 Input);

struct v2f
{
    f32 x, y;
};

struct v3f
{
    f32 x, y, z;
};

v2f V2F(f32 x, f32 y);

v3f V3F(f32 x, f32 y, f32 z);

f32 Dot(v2f A, v2f B);

f32 Dot(v3f A, v3f B);



v2f operator+(v2f &A, v2f &B);

v3f operator+(v3f &A, v3f &B);


v2f operator-(v2f &A, v2f &B);

v3f operator-(v3f &A, v3f &B);


v2f operator*(v2f &A, v2f &B);

v3f operator*(v3f &A, v3f &B);


v2f operator/(v2f &A, v2f &B);

v3f operator/(v3f &A, v3f &B);

v2f operator+(v2f &A, f32 &B);

v3f operator+(v3f &A, f32 &B);

v2f operator-(v2f &A, f32 &B);

v3f operator-(v3f &A, f32 &B);

v2f operator*(v2f &A, f32 &B);

v3f operator*(v3f &A, f32 &B);

v2f operator/(v2f &A, f32 &B);

v3f operator/(v3f &A, f32 &B);


v2f &operator+=(v2f &A, v2f &B);

v3f &operator+=(v3f &A, v3f &B);

v2f &operator-=(v2f &A, v2f &B);

v3f &operator-=(v3f &A, v3f &B);

v2f &operator*=(v2f &A, v2f &B);

v3f &operator*=(v3f &A, v3f &B);

v2f &operator/=(v2f &A, v2f &B);

v3f &operator/=(v3f &A, v3f &B);

v2f &operator+=(v2f &A, f32 &B);

v3f &operator+=(v3f &A, f32 &B);

v2f &operator-=(v2f &A, f32 &B);

v3f &operator-=(v3f &A, f32 &B);

v2f &operator*=(v2f &A, f32 &B);

v3f &operator*=(v3f &A, f32 &B);

v2f &operator/=(v2f &A, f32 &B);

v3f &operator/=(v3f &A, f32 &B);



//Row major.
//In the memory, first come the individual Rows
struct mat2f
{
    f32 Elements[4];
};

struct mat3f
{
    f32 Elements[9];
};


mat2f operator*(mat2f &Matrix, f32 &Value);

mat2f operator*(f32 &Value, mat2f &Matrix);

mat3f operator*(mat3f &Matrix, f32 &Value);

mat3f operator*(f32 &Value, mat3f &Matrix);


f32 GetMatrixElement(mat2f Matrix, s32 Row, s32 Column);

f32 GetMatrixElement(mat3f Matrix, s32 Row, s32 Column);

void SetMatrixElement(mat2f *Matrix, s32 Row, s32 Column, f32 Value);

void SetMatrixElement(mat3f *Matrix, s32 Row, s32 Column, f32 Value);

mat2f Mat2F(f32 Value=1);

mat3f Mat3F(f32 Value=1);

mat2f SubMatrix(mat3f Matrix, u8 Row, u8 Column);

mat2f operator*(mat2f &A, mat2f &B);

mat3f operator*(mat3f &A, mat3f &B);

v2f operator*(mat2f &Matrix, v2f &Vector);

v3f operator*(mat3f &Matrix, v3f &Vector);

f32 Determinant(mat2f Input);

f32 Determinant(mat3f Input);

mat2f Inverse(mat2f Input);

mat3f Inverse(mat3f Input);

mat3f Translate(v2f Translation);

mat3f Scale(v2f Size);

mat3f Rotate(f32 Angle);

#endif