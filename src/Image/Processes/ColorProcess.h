#pragma once
#include "../Image.h"

namespace ImProc
{
    //Add Color
    process *CreateAddColorProcess(color_u8 Addend);

    void AddColorProcess(image *In, image *Out, process *Process);
    
    //Subtract Color
    process *CreateSubtractColorProcess(color_u8 Subtractend);

    void SubtractColorProcess(image *In, image *Out, process *Process);
    
    //Multiply Color
    process *CreateMultiplyColorProcess(color_f32 Multiplier);

    void MultiplyColorProcess(image *In, image *Out, process *Process);
    
    //Divide Color
    process *CreateDivideColorProcess(color_f32 Divisor);

    void DivideColorProcess(image *In, image *Out, process *Process);
    
}