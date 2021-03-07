#include "VectorMaths.h"




//TODO(Jacques) : Implement that
#include "math.h"
f32 Cosine(f32 Input)
{
    return cos(Input);
}

f32 Sine(f32 Input)
{
    return sin(Input);
}

f32 Tangent(f32 Input)
{
    return tan(Input);
}



v2f V2F(f32 x, f32 y)
{
    v2f Result = {};
    Result.x = x;
    Result.y = y;
    return Result;
}

v3f V3F(f32 x, f32 y, f32 z)
{
    v3f Result = {};
    Result.x = x;
    Result.y = y;
    Result.z = z;
    return Result;
}

f32 Dot(v2f A, v2f B)
{
    f32 Result=0;
    Result = A.x * B.x + A.y * B.y;
    return Result;
}

f32 Dot(v3f A, v3f B)
{
    f32 Result=0;
    Result = A.x * B.x + A.y * B.y + A.z * B.z;
    return Result;
}



v2f operator+(v2f &A, v2f &B)
{
    v2f Result = A;
    Result.x += B.x;
    Result.y += B.y;
    return Result;
}

v3f operator+(v3f &A, v3f &B)
{
    v3f Result = A;
    Result.x += B.x;
    Result.y += B.y;
    Result.z += B.z;
    return Result;
}


v2f operator-(v2f &A, v2f &B)
{
    v2f Result = A;
    Result.x -= B.x;
    Result.y -= B.y;
    return Result;
}

v3f operator-(v3f &A, v3f &B)
{
    v3f Result = A;
    Result.x -= B.x;
    Result.y -= B.y;
    Result.z -= B.z;
    return Result;
}


v2f operator*(v2f &A, v2f &B)
{
    v2f Result = A;
    Result.x *= B.x;
    Result.y *= B.y;
    return Result;
}

v3f operator*(v3f &A, v3f &B)
{
    v3f Result = A;
    Result.x *= B.x;
    Result.y *= B.y;
    Result.z *= B.z;
    return Result;
}


v2f operator/(v2f &A, v2f &B)
{
    v2f Result = A;
    Result.x /= B.x;
    Result.y /= B.y;
    return Result;
}

v3f operator/(v3f &A, v3f &B)
{
    v3f Result = A;
    Result.x /= B.x;
    Result.y /= B.y;
    Result.z /= B.z;
    return Result;
}

v2f operator+(v2f &A, f32 &B)
{
    v2f Result = A;
    Result.x += B;
    Result.y += B;
    return Result;
}

v3f operator+(v3f &A, f32 &B)
{
    v3f Result = A;
    Result.x += B;
    Result.y += B;
    Result.z += B;
    return Result;
}

v2f operator-(v2f &A, f32 &B)
{
    v2f Result = A;
    Result.x -= B;
    Result.y -= B;
    return Result;
}

v3f operator-(v3f &A, f32 &B)
{
    v3f Result = A;
    Result.x -= B;
    Result.y -= B;
    Result.z -= B;
    return Result;
}

v2f operator*(v2f &A, f32 &B)
{
    v2f Result = A;
    Result.x *= B;
    Result.y *= B;
    return Result;
}

v3f operator*(v3f &A, f32 &B)
{
    v3f Result = A;
    Result.x *= B;
    Result.y *= B;
    Result.z *= B;
    return Result;
}

v2f operator/(v2f &A, f32 &B)
{
    v2f Result = A;
    Result.x /= B;
    Result.y /= B;
    return Result;
}

v3f operator/(v3f &A, f32 &B)
{
    v3f Result = A;
    Result.x /= B;
    Result.y /= B;
    Result.z /= B;
    return Result;
}


v2f &operator+=(v2f &A, v2f &B)
{
    v2f Result = A + B;
    return Result;
}

v3f &operator+=(v3f &A, v3f &B)
{
    v3f Result = A + B;
    return Result;
}

v2f &operator-=(v2f &A, v2f &B)
{
    v2f Result = A - B;
    return Result;
}

v3f &operator-=(v3f &A, v3f &B)
{
    v3f Result = A - B;
    return Result;
}

v2f &operator*=(v2f &A, v2f &B)
{
    v2f Result = A * B;
    return Result;
}

v3f &operator*=(v3f &A, v3f &B)
{
    v3f Result = A * B;
    return Result;
}

v2f &operator/=(v2f &A, v2f &B)
{
    v2f Result = A / B;
    return Result;
}

v3f &operator/=(v3f &A, v3f &B)
{
    v3f Result = A / B;
    return Result;
}

v2f &operator+=(v2f &A, f32 &B)
{
    v2f Result = A + B;
    return Result;
}

v3f &operator+=(v3f &A, f32 &B)
{
    v3f Result = A + B;
    return Result;
}

v2f &operator-=(v2f &A, f32 &B)
{
    v2f Result = A - B;
    return Result;
}

v3f &operator-=(v3f &A, f32 &B)
{
    v3f Result = A - B;
    return Result;
}

v2f &operator*=(v2f &A, f32 &B)
{
    v2f Result = A * B;
    return Result;
}

v3f &operator*=(v3f &A, f32 &B)
{
    v3f Result = A * B;
    return Result;
}

v2f &operator/=(v2f &A, f32 &B)
{
    v2f Result = A / B;
    return Result;
}

v3f &operator/=(v3f &A, f32 &B)
{
    v3f Result = A / B;
    return Result;
}


mat2f operator*(mat2f &Matrix, f32 &Value)
{
    mat2f Result = {};
    for(u8 Index=0; Index<4; Index++)
    {
        Result.Elements[Index] = Value * Matrix.Elements[Index];
    }
    return Result;
}

mat2f operator*(f32 &Value, mat2f &Matrix)
{
    mat2f Result = Matrix * Value;
    return Result;
}

mat3f operator*(mat3f &Matrix, f32 &Value)
{
    mat3f Result = {};
    for(u8 Index=0; Index<4; Index++)
    {
        Result.Elements[Index] = Value * Matrix.Elements[Index];
    }
    return Result;
}

mat3f operator*(f32 &Value, mat3f &Matrix)
{
    mat3f Result = Matrix * Value;
    return Result;
}


f32 GetMatrixElement(mat2f Matrix, s32 Row, s32 Column)
{
    s32 Index = 2 * Row + Column;
    return Matrix.Elements[Index];
}

f32 GetMatrixElement(mat3f Matrix, s32 Row, s32 Column)
{
    s32 Index = 3 * Row + Column;
    return Matrix.Elements[Index];
}

void SetMatrixElement(mat2f *Matrix, s32 Row, s32 Column, f32 Value)
{
    s32 Index = 2 * Row + Column;
    Matrix->Elements[Index] = Value;
}

void SetMatrixElement(mat3f *Matrix, s32 Row, s32 Column, f32 Value)
{
    s32 Index = 3 * Row + Column;
    Matrix->Elements[Index] = Value;
}

mat2f Mat2F(f32 Value)
{
    mat2f Result ={};
    SetMatrixElement(&Result, 0, 0, Value);
    SetMatrixElement(&Result, 1, 1, Value);
    return Result;
}

mat3f Mat3F(f32 Value)
{
    mat3f Result ={};
    SetMatrixElement(&Result, 0, 0, Value);
    SetMatrixElement(&Result, 1, 1, Value);
    SetMatrixElement(&Result, 2, 2, Value);
    return Result;
}

mat2f SubMatrix(mat3f Matrix, u8 Row, u8 Column)
{
    mat2f Result = {};
    u8 RowIndices[2] = {};
    u8 ColumnIndices[2] = {};
    u8 runningRow=0;
    u8 runningColumn=0;
    for(u8 Index=0; Index<3; Index++)
    {
        if(Index != Row)
        {
            RowIndices[runningRow++] = Index;
        }
        if(Index != Column)
        {
            ColumnIndices[runningColumn++] = Index;
        }
    }

    for(u8 RowIndex=0; RowIndex < 2; RowIndex++)
    {
        for(u8 ColumnIndex=0; ColumnIndex < 2; ColumnIndex++)
        {
            f32 Value = GetMatrixElement(Matrix, RowIndices[RowIndex], ColumnIndices[ColumnIndex]);
            SetMatrixElement(&Result, RowIndex, ColumnIndex, Value);
        }     
    }
    return Result;
}

mat2f operator*(mat2f &A, mat2f &B)

{
    mat2f Result = {};

    for(u8 RowIndex=0; RowIndex<2; RowIndex++)
    {
        for(u8 ColumnIndex=0; ColumnIndex<2; ColumnIndex++)
        {
            f32 Value =   GetMatrixElement(A, RowIndex, 0) * GetMatrixElement(B, 0, ColumnIndex) 
                        + GetMatrixElement(A, RowIndex, 1) * GetMatrixElement(B, 1, ColumnIndex);

            SetMatrixElement(&Result, RowIndex, ColumnIndex, Value);
        }
    }
    return Result;
}

mat3f operator*(mat3f &A, mat3f &B)

{
    mat3f Result = {};

    for(u8 RowIndex=0; RowIndex<3; RowIndex++)
    {
        for(u8 ColumnIndex=0; ColumnIndex<3; ColumnIndex++)
        {
            f32 Value =   GetMatrixElement(A, RowIndex, 0) * GetMatrixElement(B, 0, ColumnIndex) 
                        + GetMatrixElement(A, RowIndex, 1) * GetMatrixElement(B, 1, ColumnIndex) 
                        + GetMatrixElement(A, RowIndex, 2) * GetMatrixElement(B, 2, ColumnIndex);
            SetMatrixElement(&Result, RowIndex, ColumnIndex, Value);
        }
    }

    return Result;
}


v2f operator*(mat2f &Matrix, v2f &Vector)
{
    v2f Result = {};

    Result.x = GetMatrixElement(Matrix, 0, 0) * Vector.x + GetMatrixElement(Matrix, 0, 1) * Vector.y;
    Result.y = GetMatrixElement(Matrix, 1, 0) * Vector.x + GetMatrixElement(Matrix, 1, 1) * Vector.y;

    return Result;
}

v3f operator*(mat3f &Matrix, v3f &Vector)
{
    v3f Result = {};

    Result.x = GetMatrixElement(Matrix, 0, 0) * Vector.x + GetMatrixElement(Matrix, 0, 1) * Vector.y + GetMatrixElement(Matrix, 0, 2) * Vector.z;
    Result.y = GetMatrixElement(Matrix, 1, 0) * Vector.x + GetMatrixElement(Matrix, 1, 1) * Vector.y + GetMatrixElement(Matrix, 1, 2) * Vector.z;
    Result.z = GetMatrixElement(Matrix, 2, 0) * Vector.x + GetMatrixElement(Matrix, 2, 1) * Vector.y + GetMatrixElement(Matrix, 2, 2) * Vector.z;

    return Result;
}

f32 Determinant(mat2f Input)
{
    f32 Result = 0;

    f32 a = GetMatrixElement(Input, 0, 0);
    f32 b = GetMatrixElement(Input, 0, 1);
    f32 c = GetMatrixElement(Input, 1, 0);
    f32 d = GetMatrixElement(Input, 1, 1);

    Result = a * d - b * c;
    return Result;
}

f32 Determinant(mat3f Input)
{
   //Find cofactors
    f32 DetA = Determinant(SubMatrix(Input, 0, 0));
    f32 DetB = Determinant(SubMatrix(Input, 0, 1));
    f32 DetC = Determinant(SubMatrix(Input, 0, 2));

    //Find determinant
    f32 Result = GetMatrixElement(Input, 0, 0) * DetA - GetMatrixElement(Input, 0, 1) * DetB + GetMatrixElement(Input, 0, 2) * DetC;
    return Result;
}

mat2f Inverse(mat2f Input)
{
    mat2f Result = {};

    f32 OneOverDet = 1.0f / Determinant(Input);
    
    
    mat2f SwappedMatrix = {};
    
    f32 a = GetMatrixElement(Input, 0, 0);
    f32 b = GetMatrixElement(Input, 0, 1);
    f32 c = GetMatrixElement(Input, 1, 0);
    f32 d = GetMatrixElement(Input, 1, 1);

    SetMatrixElement(&SwappedMatrix, 0, 0,  d);
    SetMatrixElement(&SwappedMatrix, 0, 1, -b);
    SetMatrixElement(&SwappedMatrix, 1, 0, -c);
    SetMatrixElement(&SwappedMatrix, 1, 1,  a);

    Result = OneOverDet * SwappedMatrix;
    return Result;
}

mat3f Inverse(mat3f Input)
{
    //Find cofactors
    f32 DetA = Determinant(SubMatrix(Input, 0, 0));
    f32 DetB = Determinant(SubMatrix(Input, 0, 1));
    f32 DetC = Determinant(SubMatrix(Input, 0, 2));

    //Find determinant
    f32 MatrixDeterminant = GetMatrixElement(Input, 0, 0) * DetA - GetMatrixElement(Input, 0, 1) * DetB + GetMatrixElement(Input, 0, 2) * DetC;
    f32 OneOverDeterminant = 1.0f / MatrixDeterminant;
    //Build cofactor matrix
    mat3f CofactorMatrix =  {};

	mat3f CofactorSigns = 
	{
		{
			 1.0f, -1.0f, 1.0f, 
		    -1.0f,  1.0f,-1.0f, 
			 1.0f, -1.0f, 1.0f, 
		}
	};

    for(u8 RowIndex=0; RowIndex < 3; RowIndex++)
    {
        for(u8 ColumnIndex=0; ColumnIndex < 3; ColumnIndex++)
        {
            f32 Cofactor = 0;
            if(RowIndex==0 && ColumnIndex==0) Cofactor = DetA;
            if(RowIndex==0 && ColumnIndex==1) Cofactor = DetB;
            if(RowIndex==0 && ColumnIndex==2) Cofactor = DetC;
            else Cofactor = Determinant(SubMatrix(Input, RowIndex, ColumnIndex));
            
            
            f32 Sign = GetMatrixElement(CofactorSigns, RowIndex, ColumnIndex);
            Cofactor *= Sign;

            Cofactor *= OneOverDeterminant;

            //Transposing in place!
            SetMatrixElement(&CofactorMatrix, ColumnIndex, RowIndex, Cofactor);
        }        
    }

    return CofactorMatrix;
}


mat3f Translate(v2f Translation) 
{
    mat3f Result = Mat3F(1.0f);
    SetMatrixElement(&Result, 0, 2, Translation.x);
    SetMatrixElement(&Result, 1, 2, Translation.y);
    return Result;
}

mat3f Scale(v2f Size) 
{
    mat3f Result = Mat3F(1.0f);
    SetMatrixElement(&Result, 0, 0, Size.x);
    SetMatrixElement(&Result, 1, 1, Size.y);
    return Result;
}

mat3f Rotate(f32 Angle) 
{
    mat3f Result = Mat3F(1.0f);
    SetMatrixElement(&Result, 0, 0, Cosine(Angle));
    SetMatrixElement(&Result, 0, 1, Sine(Angle));
    SetMatrixElement(&Result, 1, 0, -Sine(Angle));
    SetMatrixElement(&Result, 1, 1, Cosine(Angle));
    return Result;
}
