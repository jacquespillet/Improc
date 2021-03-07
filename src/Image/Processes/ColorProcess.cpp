#include "ColorProcess.h"
#include <malloc.h>

namespace ImProc
{
    void AddColorProcess(image *In, image *Out, process *Process)
    {
        CopyImage(In, Out);
        *Out += GET(Process,AddColorProcess).Addend;
    }   

    //Add Color
    process *CreateAddColorProcess(color_u8 Addend)
    {
        process *Result = (process*)malloc(sizeof(process));
        add_color_process NewAddColorProcess;
        NewAddColorProcess.Fields.Addend = Addend;
        Result->Type = ADD_COLOR_PROCESS;
        Result->AddColorProcess = NewAddColorProcess;
        Result->Output = {};
        Result->ProcessFunction =  &AddColorProcess;
        return Result;
    }

    //Subtract Color
    process *CreateSubtractColorProcess(color_u8 Subtrahend)
    {
        process *Result = (process*)malloc(sizeof(process));
        subtract_color_process NewSubtractColorProcess;
        NewSubtractColorProcess.Fields.Subtrahend = Subtrahend;
        Result->Type = SUBTRACT_COLOR_PROCESS;
        Result->SubtractColorProcess = NewSubtractColorProcess;
        Result->Output = {};
        Result->ProcessFunction =  &SubtractColorProcess;
        return Result;
    }

    void SubtractColorProcess(image *In, image *Out, process *Process)
    {
        CopyImage(In, Out);
        *Out -= GET(Process, SubtractColorProcess).Subtrahend;
    }   

    //Multiply Color
    process *CreateMultiplyColorProcess(color_f32 Multiplier)
    {
        process *Result = (process*)malloc(sizeof(process));
        multiply_color_process NewMultiplyColorProcess;
        NewMultiplyColorProcess.Fields.Multiplier = Multiplier;
        Result->Type = MULTIPLY_COLOR_PROCESS;
        Result->MultiplyColorProcess = NewMultiplyColorProcess;
        Result->Output = {};
        Result->ProcessFunction =  &MultiplyColorProcess;
        return Result;
    }

    void MultiplyColorProcess(image *In, image *Out, process *Process)
    {
        CopyImage(In, Out);
        *Out *= GET(Process, MultiplyColorProcess).Multiplier;
    }   
    
    //Subtract Color
    process *CreateDivideColorProcess(color_f32 Divisor)
    {
        process *Result = (process*)malloc(sizeof(process));
        divide_color_process NewDivideColorProcess;
        NewDivideColorProcess.Fields.Divisor = Divisor;
        Result->Type = DIVIDE_COLOR_PROCESS;
        Result->DivideColorProcess = NewDivideColorProcess;
        Result->Output = {};
        Result->ProcessFunction =  &DivideColorProcess;
        return Result;
    }

    void DivideColorProcess(image *In, image *Out, process *Process)
    {
        CopyImage(In, Out);
        *Out /= GET(Process,DivideColorProcess).Divisor;
    }   
}