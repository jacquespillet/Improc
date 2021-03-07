#pragma once
#include <stdint.h>

namespace ImProc
{
    typedef uint8_t u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;

    typedef int8_t s8;
    typedef int16_t s16;
    typedef int32_t s32;
    typedef int64_t s64;

    typedef float f32;
    typedef double f64;

    typedef bool b32;

    struct color_u8
    {
        u8 r, g, b, a;
    };

    struct color_f32
    {
        f32 r, g, b, a;
    };

    struct color_s16
    {
        s16 r, g, b, a;
    };



    struct image
    {
        u8 *Data;
        u64 Size;

        u32 Width;
        u32 Height;
        u32 Pitch;
        u8 BytesPerPixel;
        u8 NumChannels;
    };


    #define PROCESS_MAX_SIZE 128

    enum process_type
    {
        ADD_COLOR_PROCESS,
        SUBTRACT_COLOR_PROCESS,
        MULTIPLY_COLOR_PROCESS,
        DIVIDE_COLOR_PROCESS,
        
        ADD_IMAGE_PROCESS,
        SUBTRACT_IMAGE_PROCESS,
        MULTIPLY_IMAGE_PROCESS,
        DIVIDE_IMAGE_PROCESS,
        
        MIN_IMAGE_PROCESS,
        MAX_IMAGE_PROCESS,

        NEGATE_PROCESS,
        LOGARITHM_PROCESS,
        POWER_PROCESS,
    };

    struct add_color_process
    {
        struct fields
        {
            color_u8 Addend;
        };
        fields Fields;
        u8 Raw[PROCESS_MAX_SIZE - sizeof(fields)];
    };

    struct subtract_color_process
    {
        struct fields
        {
            color_u8 Subtrahend;
        };
        fields Fields;
        u8 Raw[PROCESS_MAX_SIZE - sizeof(fields)];
    };

    struct multiply_color_process
    {
        struct fields
        {
            color_f32 Multiplier;
        };
        fields Fields;
        u8 Raw[PROCESS_MAX_SIZE - sizeof(fields)];
    };

    struct divide_color_process
    {
        struct fields
        {
            color_f32 Divisor;
        };
        fields Fields;
        u8 Raw[PROCESS_MAX_SIZE - sizeof(fields)];
    };



    struct add_image_process
    {
        struct fields
        {
            image Addend;
        };
        fields Fields;
        u8 Raw[PROCESS_MAX_SIZE - sizeof(fields)];
    };

    struct subtract_image_process
    {
        struct fields
        {
            image Subtractend;
        };
        fields Fields;
        u8 Raw[PROCESS_MAX_SIZE - sizeof(fields)];
    };

    struct multiply_image_process
    {
        struct fields
        {
            image Multiplier;
        };
        fields Fields;
        u8 Raw[PROCESS_MAX_SIZE - sizeof(fields)];
    };

    struct divide_image_process
    {
        struct fields
        {
            image Divisor;
        };
        fields Fields;
        u8 Raw[PROCESS_MAX_SIZE - sizeof(fields)];
    };

    struct min_image_process
    {
        struct fields{
            image Image;
        };
        fields Fields;
        u8 Raw[PROCESS_MAX_SIZE - sizeof(fields)];
    };

    struct max_image_process
    {
        struct fields{
            image Image;
        };
        fields Fields;
        u8 Raw[PROCESS_MAX_SIZE - sizeof(fields)];
    };



    struct negate_process
    {
        struct fields{};
        fields Fields;
        u8 Raw[PROCESS_MAX_SIZE - sizeof(fields)];
    };

    struct logarithm_process
    {
        struct fields{
            f32 ConstantTerm;
        };
        fields Fields;
        u8 Raw[PROCESS_MAX_SIZE - sizeof(fields)];
    };

    struct power_process
    {
        struct fields{
            f32 ConstantTerm;
            f32 ExponentTerm;
        };
        fields Fields;
        u8 Raw[PROCESS_MAX_SIZE - sizeof(fields)];
    };



    union process_abstraction
    {
        u8 Raw[PROCESS_MAX_SIZE];
        
        add_color_process AddColorProcess;   
        subtract_color_process SubtractColorProcess;   
        multiply_color_process MultiplyColorProcess;   
        divide_color_process DivideColorProcess;   

        add_image_process AddImageProcess;      
        subtract_image_process SubtractImageProcess;      
        multiply_image_process MultiplyImageProcess;      
        divide_image_process DivideImageProcess;   

        min_image_process MinImageProcess;   
        max_image_process MaxImageProcess;   

        negate_process NegateProcess;
        logarithm_process LogarithmProcess;
        power_process PowerProcess;
    };

    // #define GET(Abstract, Derived) Abstract->ProcessAbstraction.Derived.Fields
    #define GET(Abstract, Derived) Abstract->Derived.Fields

    struct process
    {
        process_type Type;
 
        // process_abstraction ProcessAbstraction;
        union
        {
            u8 Raw[PROCESS_MAX_SIZE];
            
            add_color_process AddColorProcess;   
            subtract_color_process SubtractColorProcess;   
            multiply_color_process MultiplyColorProcess;   
            divide_color_process DivideColorProcess;   

            add_image_process AddImageProcess;      
            subtract_image_process SubtractImageProcess;      
            multiply_image_process MultiplyImageProcess;      
            divide_image_process DivideImageProcess;   

            min_image_process MinImageProcess;   
            max_image_process MaxImageProcess;   

            negate_process NegateProcess;
            logarithm_process LogarithmProcess;
            power_process PowerProcess;
        };
        
        image Output;

        void (*ProcessFunction)(image *, image *, process *); 
        void (*DeallocateFunction)(process *); 
    };

    struct processes_stack
    {
        process *Processes;
        u32 NumProcesses;
    };
}
