#pragma once
#include "ImProcTypes.h"

namespace ImProc
{
    u8 Min(u8 A, u8 B);

    u16 Min(u16 A, u16 B);

    s16 Min(s16 A, s16 B);

    u32 Min(u32 A, u32 B);

    f32 Min(f32 A, f32 B);

    u8 Max(u8 A, u8 B);

    u16 Max(u16 A, u16 B);

    s16 Max(s16 A, s16 B);

    u32 Max(u32 A, u32 B);

    f32 Max(f32 A, f32 B);

    u8 Clamp(u8 Value, u8 MinValue, u8 MaxValue);
    
    f32 Clamp(f32 Value, f32 MinValue, f32 MaxValue);

    f32 Log(f32 Value);

    f32 Pow(f32 Value, f32 Exponent);
}