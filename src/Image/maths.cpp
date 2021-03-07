#include "Maths.h"

namespace ImProc
{
    u8 Min(u8 A, u8 B)
    {
        return A < B ? A : B;
    }

    u16 Min(u16 A, u16 B)
    {
        return A < B ? A : B;
    }

    s16 Min(s16 A, s16 B)
    {
        return A < B ? A : B;
    }

    u32 Min(u32 A, u32 B)
    {
        return A < B ? A : B;
    }

    f32 Min(f32 A, f32 B)
    {
        return A < B ? A : B;
    }

    u8 Max(u8 A, u8 B)
    {
        return A > B ? A : B;
    }

    u16 Max(u16 A, u16 B)
    {
        return A > B ? A : B;
    }

    s16 Max(s16 A, s16 B)
    {
        return A > B ? A : B;
    }

    u32 Max(u32 A, u32 B)
    {
        return A > B ? A : B;
    }

    f32 Max(f32 A, f32 B)
    {
        return A > B ? A : B;
    }

    u8 Clamp(u8 Value, u8 MinValue, u8 MaxValue)
    {
        return Min(MaxValue, Max(MinValue, Value));
    }

    f32 Clamp(f32 Value, f32 MinValue, f32 MaxValue)
    {
        return Min(MaxValue, Max(MinValue, Value));
    }

    #include <math.h>
    f32 Log(f32 Value)
    {
        f32 Result = log(Value);
        return Result;
    }

    
    f32 Pow(f32 Value, f32 Exponent)
    {
        f32 Result = pow(Value, Exponent);
        return Result;
    }
}