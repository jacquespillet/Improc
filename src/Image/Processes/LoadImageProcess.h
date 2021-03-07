#pragma once

#include "../Image.h"

namespace ImProc{
    u8 *ReadEntireFile(const char *FileName, u64 *NumBytes);
    image ImageFromFile(const char *FileName);


    //Add Image
    process *CreateAddImageProcess(const char *FileName, u32 Width, u32 Height, b32 empty=false);

    void AddImageProcess(image *In, image *Out, process *Process);
    
    void DeallocateAddImageProcess(process *Process);

    void UpdateFileAddImageProcess(add_image_process *Process, const char* FileName, u32 Width, u32 Height);
    

    //Subtract Image
    process *CreateSubtractImageProcess(const char *FileName, u32 Width, u32 Height, b32 empty=false);
    
    void SubtractImageProcess(image *In, image *Out, process *Process);
    
    void DeallocateSubtractImageProcess(process *Process);

    void UpdateFileSubtractImageProcess(subtract_image_process *Process, const char* FileName, u32 Width, u32 Height);

    //Multiply Image
    process *CreateMultiplyImageProcess(const char *FileName, u32 Width, u32 Height, b32 empty=false);
    
    void MultiplyImageProcess(image *In, image *Out, process *Process);
    
    void DeallocateMultiplyImageProcess(process *Process);

    void UpdateFileMultiplyImageProcess(multiply_image_process *Process, const char* FileName, u32 Width, u32 Height);
    
    //Divide Image
    process *CreateDivideImageProcess(const char *FileName, u32 Width, u32 Height, b32 empty=false);
    
    void DivideImageProcess(image *In, image *Out, process *Process);
    
    void DeallocateDivideImageProcess(process *Process);

    void UpdateFileDivideImageProcess(divide_image_process *Process, const char* FileName, u32 Width, u32 Height);

    
    //Min Image
    process *CreateMinImageProcess(const char *FileName, u32 Width, u32 Height, b32 empty=false);
    
    void MinImageProcess(image *In, image *Out, process *Process);
    
    void DeallocateMinImageProcess(process *Process);

    void UpdateFileMinImageProcess(min_image_process *Process, const char* FileName, u32 Width, u32 Height);

    
    //Min Image
    process *CreateMaxImageProcess(const char *FileName, u32 Width, u32 Height, b32 empty=false);
    
    void MaxImageProcess(image *In, image *Out, process *Process);
    
    void DeallocateMaxImageProcess(process *Process);

    void UpdateFileMaxImageProcess(max_image_process *Process, const char* FileName, u32 Width, u32 Height);
}