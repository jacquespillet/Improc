#pragma once

#include "../Image.h"

namespace ImProc{
    //Negate
    process *CreateNegateProcess();

    void NegateProcess(image *In, image *Out, process *Process);
    
    //Log
    process *CreateLogarithmProcess(f32 ConstantTerm);

    void LogarithmProcess(image *In, image *Out, process *Process);
    
    //Power
    process *CreatePowerProcess(f32 ConstantTerm, f32 Exponent);

    void PowerProcess(image *In, image *Out, process *Process);
}