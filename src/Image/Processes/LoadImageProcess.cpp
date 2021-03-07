#include "LoadImageProcess.h"
#include <stdio.h>
#include <malloc.h>

#include "FreeImage.h"

namespace ImProc{
    u8 *ReadEntireFile(const char *FileName, u64 *NumBytes)
    {
        FILE *File = fopen(FileName, "rb");
        fseek (File, 0, SEEK_END);
        *NumBytes = ftell (File);
        fseek (File, 0, SEEK_SET);

        u8 *MemoryPointer = (u8*) malloc(*NumBytes * sizeof(u8));
        
        fread (MemoryPointer, sizeof(u8), *NumBytes, File);

        return MemoryPointer;
    }


    image ImageFromFile(const char *FileName) {
        image Image = {};

        FREE_IMAGE_FORMAT ImageFormat = FIF_UNKNOWN;
        ImageFormat = FreeImage_GetFileType(FileName, 0);
        
        u64 NumBytes=0;
        u8 *CompressedData = ReadEntireFile(FileName, &NumBytes);
        

        FreeImage_Initialise(); 
        FIBITMAP* Bitmap;
        FIBITMAP* Bitmap32Bits;
        FIMEMORY* MemoryHandle = FreeImage_OpenMemory((u8*)CompressedData, NumBytes);
        
        Bitmap = FreeImage_LoadFromMemory(ImageFormat, MemoryHandle, 0);
        
        if (Bitmap) {
            Bitmap32Bits = FreeImage_ConvertTo32Bits(Bitmap); 
 
            // Allocate a raw buffer
            Image.Width = FreeImage_GetWidth(Bitmap32Bits);
            Image.Height = FreeImage_GetHeight(Bitmap32Bits);
            Image.Pitch = FreeImage_GetPitch(Bitmap32Bits);
            Image.BytesPerPixel = Image.Pitch / Image.Width;
            Image.Data = (u8*)malloc(Image.Width * Image.Height * Image.BytesPerPixel * sizeof(u8));
            Image.Size = Image.Width * Image.Height * Image.BytesPerPixel;
            Image.NumChannels = Image.BytesPerPixel;

            FreeImage_ConvertToRawBits(Image.Data, Bitmap32Bits, Image.Pitch, 8 * Image.BytesPerPixel, FI_RGBA_BLUE_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_RED_MASK, false);
            
            FreeImage_Unload(Bitmap);
            FreeImage_Unload(Bitmap32Bits);
            FreeImage_CloseMemory(MemoryHandle);
            FreeImage_DeInitialise();

            free(CompressedData);

            SwapRedBlue(&Image);
        }
        else
        {
            FreeImage_CloseMemory(MemoryHandle);
            FreeImage_DeInitialise(); 
        }
        return Image;
    }


    //Add Image

    process *CreateAddImageProcess(const char *FileName, u32 Width, u32 Height, b32 empty)
    {
        process *Result = (process*)malloc(sizeof(process));
		add_image_process ImageProcess = {};
        
        if(empty)
        {
            ImageProcess.Fields.Addend = EmptyImage(Width, Height);
        }
        else
        {
		    ImageProcess.Fields.Addend = ImageFromFile(FileName);
        }
        ResizeImage(&ImageProcess.Fields.Addend, Width, Height);
        
		Result->Type = ADD_IMAGE_PROCESS;
        Result->AddImageProcess = ImageProcess;
        Result->Output = {};
        Result->ProcessFunction =  &AddImageProcess;
        Result->DeallocateFunction =  &DeallocateAddImageProcess;


        return Result;
    }

    
    void UpdateFileAddImageProcess(add_image_process *Process, const char* FileName, u32 Width, u32 Height)
    {
        DeallocateImage(&(Process->Fields.Addend));
        Process->Fields.Addend = ImageFromFile(FileName);
        ResizeImage(&(Process->Fields.Addend), Width, Height);
    }

    void AddImageProcess(image *In, image *Out, process *Process)
    {
        CopyImage(In, Out);
        *Out +=GET( Process, AddImageProcess).Addend;
    }    

    void DeallocateAddImageProcess(process *Process)
    {
        DeallocateImage(&GET(Process, AddImageProcess).Addend);
    }


    //Subtract image

    process *CreateSubtractImageProcess(const char *FileName, u32 Width, u32 Height, b32 empty)
    {
        process *Result = (process*)malloc(sizeof(process));
		subtract_image_process ImageProcess = {};
        
        if(empty)
        {
            ImageProcess.Fields.Subtractend = EmptyImage(Width, Height);
        }
        else
        {
		    ImageProcess.Fields.Subtractend = ImageFromFile(FileName);
        }
        ResizeImage(&ImageProcess.Fields.Subtractend, Width, Height);
        
		Result->Type = SUBTRACT_IMAGE_PROCESS;
        Result->SubtractImageProcess = ImageProcess;
        Result->Output = {};
        Result->ProcessFunction =  &SubtractImageProcess;
        Result->DeallocateFunction =  &DeallocateSubtractImageProcess;


        return Result;
    }

    
    void UpdateFileSubtractImageProcess(subtract_image_process *Process, const char* FileName, u32 Width, u32 Height)
    {
        DeallocateImage(&(Process->Fields.Subtractend));
        Process->Fields.Subtractend = ImageFromFile(FileName);
        ResizeImage(&(Process->Fields.Subtractend), Width, Height);
    }

    void SubtractImageProcess(image *In, image *Out, process *Process)
    {
        CopyImage(In, Out);
        *Out -= GET(Process, SubtractImageProcess).Subtractend;
    }    

    void DeallocateSubtractImageProcess(process *Process)
    {
        DeallocateImage(&GET(Process, SubtractImageProcess).Subtractend);
    }


    // Multiply image
    
    process *CreateMultiplyImageProcess(const char *FileName, u32 Width, u32 Height, b32 empty)
    {
        process *Result = (process*)malloc(sizeof(process));
		multiply_image_process ImageProcess = {};
        
        if(empty)
        {
            ImageProcess.Fields.Multiplier = EmptyImage(Width, Height);
        }
        else
        {
		    ImageProcess.Fields.Multiplier = ImageFromFile(FileName);
        }
        ResizeImage(&ImageProcess.Fields.Multiplier, Width, Height);
        
		Result->Type = MULTIPLY_IMAGE_PROCESS;
        Result->MultiplyImageProcess = ImageProcess;
        Result->Output = {};

        Result->ProcessFunction =  &MultiplyImageProcess;
        Result->DeallocateFunction =  &DeallocateMultiplyImageProcess;

        return Result;
    }

    
    void UpdateFileMultiplyImageProcess(multiply_image_process *Process, const char* FileName, u32 Width, u32 Height)
    {
        DeallocateImage(&(Process->Fields.Multiplier));
        Process->Fields.Multiplier = ImageFromFile(FileName);
        ResizeImage(&(Process->Fields.Multiplier), Width, Height);
    }

    void MultiplyImageProcess(image *In, image *Out, process *Process)
    {
        CopyImage(In, Out);
        *Out *= GET(Process, MultiplyImageProcess).Multiplier;
    }    

    void DeallocateMultiplyImageProcess(process *Process)
    {
        DeallocateImage(&GET(Process, MultiplyImageProcess).Multiplier);
    }

    

    // Divide image
    
    process *CreateDivideImageProcess(const char *FileName, u32 Width, u32 Height, b32 empty)
    {
        process *Result = (process*)malloc(sizeof(process));
		divide_image_process ImageProcess = {};
        
        if(empty)
        {
            ImageProcess.Fields.Divisor = EmptyImage(Width, Height);
        }
        else
        {
		    ImageProcess.Fields.Divisor = ImageFromFile(FileName);
        }
        ResizeImage(&ImageProcess.Fields.Divisor, Width, Height);
        
		Result->Type = DIVIDE_IMAGE_PROCESS;
        Result->DivideImageProcess = ImageProcess;
        Result->Output = {};
        Result->ProcessFunction =  &DivideImageProcess;
        Result->DeallocateFunction =  &DeallocateDivideImageProcess;


        return Result;
    }

    
    void UpdateFileDivideImageProcess(divide_image_process *Process, const char* FileName, u32 Width, u32 Height)
    {
        DeallocateImage(&(Process->Fields.Divisor));
        Process->Fields.Divisor = ImageFromFile(FileName);
        ResizeImage(&(Process->Fields.Divisor), Width, Height);
    }

    void DivideImageProcess(image *In, image *Out, process *Process)
    {
        CopyImage(In, Out);
        *Out /= GET(Process, DivideImageProcess).Divisor;
    }    

    void DeallocateDivideImageProcess(process *Process)
    {
        DeallocateImage(&GET(Process, DivideImageProcess).Divisor);
    }
    
    
    // Min image
    
    process *CreateMinImageProcess(const char *FileName, u32 Width, u32 Height, b32 empty)
    {
        process *Result = (process*)malloc(sizeof(process));
		min_image_process ImageProcess = {};
        
        if(empty)
        {
            ImageProcess.Fields.Image = EmptyImage(Width, Height);
        }
        else
        {
		    ImageProcess.Fields.Image = ImageFromFile(FileName);
        }
        ResizeImage(&ImageProcess.Fields.Image, Width, Height);
        
		Result->Type = MIN_IMAGE_PROCESS;
        Result->MinImageProcess = ImageProcess;
        Result->Output = {};
        Result->ProcessFunction =  &MinImageProcess;
        Result->DeallocateFunction =  &DeallocateMinImageProcess;

        return Result;
    }

    
    void UpdateFileMinImageProcess(min_image_process *Process, const char* FileName, u32 Width, u32 Height)
    {
        DeallocateImage(&(Process->Fields.Image));
        Process->Fields.Image = ImageFromFile(FileName);
        ResizeImage(&(Process->Fields.Image), Width, Height);
    }

    void MinImageProcess(image *In, image *Out, process *Process)
    {
        image Temp = Min(In, &GET(Process, MinImageProcess).Image);
        CopyImage(&Temp, Out); 
        DeallocateImage(&Temp);
    }    

    void DeallocateMinImageProcess(process *Process)
    {
        DeallocateImage(&GET(Process, MinImageProcess).Image);
    }

    
    // Max Image
    
    process *CreateMaxImageProcess(const char *FileName, u32 Width, u32 Height, b32 empty)
    {
        process *Result = (process*)malloc(sizeof(process));
		max_image_process ImageProcess = {};
        
        if(empty)
        {
            ImageProcess.Fields.Image = EmptyImage(Width, Height);
        }
        else
        {
		    ImageProcess.Fields.Image = ImageFromFile(FileName);
        }
        ResizeImage(&ImageProcess.Fields.Image, Width, Height);
        
		Result->Type = MAX_IMAGE_PROCESS;
        Result->MaxImageProcess = ImageProcess;
        Result->Output = {};
        Result->ProcessFunction =  &MaxImageProcess;
        Result->DeallocateFunction =  &DeallocateMaxImageProcess;


        return Result;
    }

    
    void UpdateFileMaxImageProcess(max_image_process *Process, const char* FileName, u32 Width, u32 Height)
    {
        DeallocateImage(&(Process->Fields.Image));
        Process->Fields.Image = ImageFromFile(FileName);
        ResizeImage(&(Process->Fields.Image), Width, Height);
    }

    void MaxImageProcess(image *In, image *Out, process *Process)
    {
        image Temp = Max(In, &GET(Process, MaxImageProcess).Image);
        CopyImage(&Temp, Out); 
        DeallocateImage(&Temp);
    }    

    void DeallocateMaxImageProcess(process *Process)
    {
        DeallocateImage(&GET(Process, MaxImageProcess).Image);
    }
}