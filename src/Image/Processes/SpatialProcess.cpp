#include "SpatialProcess.h"
#include <malloc.h>
#include "../Maths.h"

namespace ImProc
{

//Negate
process *CreateNegateProcess()
{
    process *Result = (process*)malloc(sizeof(process));
    Result->Type = NEGATE_PROCESS;
    Result->Output = {};
    Result->ProcessFunction =  &NegateProcess;
    return Result;
}

void NegateProcess(image *In, image *Out, process *Process)
{
    color_u8* OutPixel = (color_u8*)Out->Data;
    color_u8* InPixel = (color_u8*)In->Data;
    for(int Index=0; Index< Out->Width * Out->Height; Index++)
    {
        OutPixel->r = Clamp((u8)255 - InPixel->r, (u8)0, (u8)255);
        OutPixel->g = Clamp((u8)255 - InPixel->g, (u8)0, (u8)255);
        OutPixel->b = Clamp((u8)255 - InPixel->b, (u8)0, (u8)255);
        OutPixel->a = Clamp((u8)255 - InPixel->a, (u8)0, (u8)255);
        
        InPixel++;
        OutPixel++;
    }
}


//Logarithm
process *CreateLogarithmProcess(f32 ConstantTerm)
{
    process *Result = (process*)malloc(sizeof(process));
    Result->Type = LOGARITHM_PROCESS;
    Result->Output = {};
    GET(Result, LogarithmProcess).ConstantTerm = ConstantTerm;
    Result->ProcessFunction =  &LogarithmProcess;
    return Result;
}

void LogarithmProcess(image *In, image *Out, process *Process)
{
    color_u8* OutPixel = (color_u8*)Out->Data;
    color_u8* InPixel = (color_u8*)In->Data;
    
    f32 ConstantTerm = GET(Process, LogarithmProcess).ConstantTerm;

    for(int Index=0; Index< Out->Width * Out->Height; Index++)
    {
		f32 r = ConstantTerm * Log(1.0f + (f32)InPixel->r / 255.0f);
		f32 g = ConstantTerm * Log(1.0f + (f32)InPixel->g / 255.0f);
		f32 b = ConstantTerm * Log(1.0f + (f32)InPixel->b / 255.0f);
		f32 a = ConstantTerm * Log(1.0f + (f32)InPixel->a / 255.0f);

		OutPixel->r = (u8)(Clamp(r * 255.0f, 0.0f, 255.0f));
		OutPixel->g = (u8)(Clamp(g * 255.0f, 0.0f, 255.0f));
		OutPixel->b = (u8)(Clamp(b * 255.0f, 0.0f, 255.0f));
		OutPixel->a = (u8)(Clamp(a * 255.0f, 0.0f, 255.0f));

        InPixel++;
        OutPixel++;
    }
}


//Power
process *CreatePowerProcess(f32 Constant, f32 Exponent)
{
    process *Result = (process*)malloc(sizeof(process));
    Result->Type = POWER_PROCESS;
    Result->Output = {};
    GET(Result, PowerProcess).ConstantTerm = Constant;
    GET(Result, PowerProcess).ExponentTerm = Exponent;
    Result->ProcessFunction =  &PowerProcess;
    return Result;    
}

void PowerProcess(image *In, image *Out, process *Process)
{
    color_u8* OutPixel = (color_u8*)Out->Data;
    color_u8* InPixel = (color_u8*)In->Data;
    
    f32 Constant = GET(Process, PowerProcess).ConstantTerm;
    f32 Exponent = GET(Process, PowerProcess).ExponentTerm;

    for(int Index=0; Index< Out->Width * Out->Height; Index++)
    {
        f32 r = Pow( (f32)InPixel->r / 255.0f, Exponent );
        f32 g = Pow( (f32)InPixel->g / 255.0f, Exponent );
        f32 b = Pow( (f32)InPixel->b / 255.0f, Exponent );
        f32 a = Pow( (f32)InPixel->a / 255.0f, Exponent );

        OutPixel->r = (u8)(Clamp(r * 255.0f, 0.0f, 255.0f));
        OutPixel->g = (u8)(Clamp(g * 255.0f, 0.0f, 255.0f));
        OutPixel->b = (u8)(Clamp(b * 255.0f, 0.0f, 255.0f));
        OutPixel->a = (u8)(Clamp(a * 255.0f, 0.0f, 255.0f));

        InPixel++;
        OutPixel++;
    }
}


}