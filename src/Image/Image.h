#pragma once
#include "ImProcTypes.h"

namespace ImProc
{

    color_u8 ColorU8(u8 r, u8 g, u8 b, u8 a);
    color_s16 ColorS16(s16 r, s16 g, s16 b, s16 a);
    color_f32 ColorF32(f32 r, f32 g, f32 b, f32 a);
    
    color_f32 ColorF32FromColorU8(color_u8 Color);

    image EmptyImage(u32 Width, u32 Height);

    void DeallocateImage(image *Image);
    
    image DuplicateImage(image *In);

    void CopyImage(image *In, image *Out);

    void ResizeImage(image *In, u32 Width, u32 Height);

    void SwapRedBlue(image *In);

    color_u8 Clamp(color_u8 Value);

    color_u8 operator+(color_u8 &A, color_u8 B);
    color_u8 &operator+=(color_u8 &ColorA, color_u8 ColorB);
    
    color_u8 operator-(color_u8 &A, color_u8 B);
    color_u8 &operator-=(color_u8 &ColorA, color_u8 ColorB);
    
    color_u8 operator*(color_u8 &A, color_f32 B);
    color_u8 &operator*=(color_u8 &ColorA, color_f32 ColorB);
    
    color_u8 operator/(color_u8 &A, color_f32 B);
    color_u8 &operator/=(color_u8 &ColorA, color_f32 ColorB);
    
    color_u8 operator*(color_u8 &A, color_u8 B);
    color_u8 &operator*=(color_u8 &ColorA, color_u8 ColorB);
    
    color_u8 operator/(color_u8 &A, color_u8 B);
    color_u8 &operator/=(color_u8 &ColorA, color_u8 ColorB);

    color_u8 Min(color_u8 A, color_u8 B);
    color_u8 Max(color_u8 A, color_u8 B);
    
    //
    image operator+(image &Image, color_u8 Color);
    image &operator+=(image &Image, color_u8 Color);
    image &operator+=(image &Image, color_s16 Color);


    image operator-(image &Image, color_u8 Color);
    image &operator-=(image &Image, color_u8 Color);


    image operator*(image &Image, color_f32 Color);
    image &operator*=(image &Image, color_f32 Color);

    image operator/(image &Image, color_f32 Color);
    image &operator/=(image &Image, color_f32 Color);

    image &operator*(image &Image, f32 Value);

    image &operator+=(image &ImageA, image ImageB);

    image &operator-=(image &ImageA, image ImageB);

    image &operator*=(image &ImageA, image ImageB);
    
    image &operator/=(image &ImageA, image ImageB);

    image Min(image *A, image *B);
    image Max(image *A, image *B);
    
}