#include "Image.h"
#include "Maths.h"
#include "malloc.h"

namespace ImProc
{

    image EmptyImage(u32 Width, u32 Height)
    {
        image Result = {};
        Result.Width = Width; 
        Result.Height = Height;
        Result.BytesPerPixel = 4;
        Result.Pitch = Result.BytesPerPixel * Result.Width;
        Result.NumChannels = 4;
        Result.Size = Result.Width * Result.Height * Result.BytesPerPixel;
        Result.Data = (u8*)malloc(Result.Size * sizeof(u8));
        
        color_u8* Pixel = (color_u8*)Result.Data;
        for(int Index=0; Index<Result.Width * Result.Height; Index++)
        {
            Pixel->r = 0;
            Pixel->g = 0;
            Pixel->b = 0;
            Pixel->a = 0;
            Pixel++;
        }
        return Result;
    }

    image DuplicateImage(image *In)
    {
        image Result = {};
        Result.Width = In->Width; 
        Result.Height = In->Height;
        Result.BytesPerPixel = In->BytesPerPixel;
        Result.Pitch = Result.BytesPerPixel * Result.Width;
        Result.NumChannels = In->NumChannels;
        Result.Size = Result.Width * Result.Height * Result.BytesPerPixel;
        Result.Data = (u8*)malloc(Result.Size * sizeof(u8));
        
        color_u8* OutPixel = (color_u8*)Result.Data;
        color_u8* InPixel = (color_u8*)In->Data;
        for(int Index=0; Index<Result.Width * Result.Height; Index++)
        {
            OutPixel->r = InPixel->r ;
            OutPixel->g = InPixel->g ;
            OutPixel->b = InPixel->b ;
            OutPixel->a = InPixel->a ;
            
            InPixel++;
            OutPixel++;
        }
        return Result;        
    }

    void CopyImage(image *In, image *Out)
    {
        if(Out->Data != nullptr) free(Out->Data);

        Out->Width = In->Width; 
        Out->Height = In->Height;
        Out->BytesPerPixel = In->BytesPerPixel;
        Out->Pitch = Out->BytesPerPixel * Out->Width;
        Out->NumChannels = In->NumChannels;
        Out->Size = Out->Width * Out->Height * Out->BytesPerPixel;
        Out->Data = (u8*)malloc(Out->Size * sizeof(u8));
        
        color_u8* OutPixel = (color_u8*)Out->Data;
        color_u8* InPixel = (color_u8*)In->Data;
        for(int Index=0; Index<Out->Width * Out->Height; Index++)
        {
            OutPixel->r = InPixel->r ;
            OutPixel->g = InPixel->g ;
            OutPixel->b = InPixel->b ;
            OutPixel->a = InPixel->a ;
            
            InPixel++;
            OutPixel++;
        }
    }

    void DeallocateImage(image *Image)
    {
        if(Image->Data == NULL) return;

        free(Image->Data);
    }


    void ResizeImage(image *In, u32 Width, u32 Height)
    {
        image Temp = EmptyImage(Width, Height);
        color_u8 *OutPixel = (color_u8*)Temp.Data;

        f32 xf=0;
        f32 yf=0;
        u32 OutIndex=0;

        //Loop through all the output pixels
        for(u32 y = 0; y < Height; y++)
        {
            yf = (f32)y / (f32)Height;
            for(u32 x = 0; x < Width; x++)
            {
                xf = (f32)x / (f32)Width;

                u32 SampleX = (u32)(xf * In->Width);
                u32 SampleY = (u32)(yf * In->Height);
                u32 InIndex = In->BytesPerPixel * (SampleY * In->Width + SampleX);

                *OutPixel = *((color_u8*)&In->Data[InIndex]);
                
                OutPixel++;
                OutIndex++;
            }
        }

        CopyImage(&Temp, In);
        DeallocateImage(&Temp);
    }    

    void SwapRedBlue(image *Image)
    {
        color_u8* Pixel = (color_u8*)Image->Data;
        for(int Index=0; Index<Image->Width * Image->Height; Index++)
        {
            u8 tmp = Pixel->r;
            Pixel->r = Pixel->b;
            Pixel->b = tmp;
            Pixel++;
        }        
    }

    
    color_u8 Clamp(color_u8 Value)
    {
        color_u8 Result = {};
        Result.r = Min(255, Max(0, Value.r));
        Result.g = Min(255, Max(0, Value.g));
        Result.b = Min(255, Max(0, Value.b));
        Result.a = Min(255, Max(0, Value.a));
        return Result;
    }
    
    color_u8 ColorU8(u8 r, u8 g, u8 b, u8 a)
    {
        color_u8 Result = {
            r, g, b, a
        };
        return Result;
    }
    
    color_s16 ColorS16(s16 r, s16 g, s16 b, s16 a)
    {
        color_s16 Result = {
            r, g, b, a
        };
        return Result;
    }
    
    color_f32 ColorF32(f32 r, f32 g, f32 b, f32 a)
    {
        color_f32 Result = {
            r, g, b, a
        };
        return Result;
    }

    color_f32 ColorF32FromColorU8(color_u8 Color)
    {
        color_f32 Result = {};
        Result.r = (f32) Color.r / (f32)255;
        Result.g = (f32) Color.g / (f32)255;
        Result.b = (f32) Color.b / (f32)255;
        Result.a = (f32) Color.a / (f32)255;
        return Result;    
    }

    
    color_u8 operator+(color_u8 &A, color_u8 B)
    {
        color_u8 Result = A;
        Result.r = (u8)Min((u16)255, ((u16)A.r + (u16)B.r));   
        Result.g = (u8)Min((u16)255, ((u16)A.g + (u16)B.g));   
        Result.b = (u8)Min((u16)255, ((u16)A.b + (u16)B.b));   
        Result.a = (u8)Min((u16)255, ((u16)A.a + (u16)B.a));
        return Result;
    }
    
    color_u8 operator-(color_u8 &A, color_u8 B)
    {
        color_u8 Result = A;
        Result.r = (u8)Max(0, Min((s16)255, ((s16)A.r - (s16)B.r)));
        Result.g = (u8)Max(0, Min((s16)255, ((s16)A.g - (s16)B.g)));
        Result.b = (u8)Max(0, Min((s16)255, ((s16)A.b - (s16)B.b)));
        Result.a = (u8)Max(0, Min((s16)255, ((s16)A.a - (s16)B.a)));
        return Result;
    }
    
    color_u8 &operator+=(color_u8 &ColorA, color_u8 ColorB)
    {
        ColorA = ColorA + ColorB;
        return ColorA;
    }
    
    color_u8 &operator-=(color_u8 &ColorA, color_u8 ColorB)
    {
        ColorA = ColorA - ColorB;
        return ColorA;
    }

    
    color_u8 operator*(color_u8 &A, color_f32 B)
    {
        color_u8 Result = A;

        Result.r = (u8)Max((s16)0, Min((s16)255, (s16)((float)A.r * B.r)));
        Result.g = (u8)Max((s16)0, Min((s16)255, (s16)((float)A.g * B.g)));
        Result.b = (u8)Max((s16)0, Min((s16)255, (s16)((float)A.b * B.b)));
        Result.a = (u8)Max((s16)0, Min((s16)255, (s16)((float)A.a * B.a)));
        return Result;
    }
    
    color_u8 &operator*=(color_u8 &ColorA, color_f32 ColorB)
    {
        ColorA = ColorA * ColorB;
        return ColorA;
    }
    
    color_u8 operator/(color_u8 &A, color_f32 B)
    {
        color_u8 Result = A;

        Result.r = (B.r != 0) ? (u8)Max((s16)0, Min((s16)255, (s16)((float)A.r / B.r))) : 0;
        Result.g = (B.g != 0) ? (u8)Max((s16)0, Min((s16)255, (s16)((float)A.g / B.g))) : 0;
        Result.b = (B.b != 0) ? (u8)Max((s16)0, Min((s16)255, (s16)((float)A.b / B.b))) : 0;
        Result.a = (B.a != 0) ? (u8)Max((s16)0, Min((s16)255, (s16)((float)A.a / B.a))) : 0;
        
        return Result;
    }
    
    color_u8 &operator/=(color_u8 &ColorA, color_f32 ColorB)
    {
        ColorA = ColorA / ColorB;
        return ColorA;
    }

    color_u8 operator*(color_u8 &A, color_u8 B)
    {
        color_f32 ColorF32B = ColorF32FromColorU8(B);
        color_u8 Result = A * ColorF32B;
        return Result; 
    }

    color_u8 &operator*=(color_u8 &ColorA, color_u8 ColorB)
    {
        color_f32 ColorF32B = ColorF32FromColorU8(ColorB);
        ColorA = ColorA * ColorF32B;
        return ColorA; 
    }

    color_u8 operator/(color_u8 &A, color_u8 B)
    {
        color_f32 ColorF32B = ColorF32FromColorU8(B);
        color_u8 result = A * ColorF32B;
        return result; 
    }

    color_u8 &operator/=(color_u8 &ColorA, color_u8 ColorB)
    {
        color_f32 ColorF32B = ColorF32FromColorU8(ColorB);
        ColorA = ColorA * ColorF32B;
        return ColorA; 
    }

    
    color_u8 Min(color_u8 A, color_u8 B)
    {
        color_u8 Result = {};
        
        Result.r = Min(A.r, B.r);
        Result.g = Min(A.g, B.g);
        Result.b = Min(A.b, B.b);
        Result.a = Min(A.a, B.a);

        return Result;
    }
    
    color_u8 Max(color_u8 A, color_u8 B)
    {
        color_u8 Result = {};
        
        Result.r = Max(A.r, B.r);
        Result.g = Max(A.g, B.g);
        Result.b = Max(A.b, B.b);
        Result.a = Max(A.a, B.a);

        return Result;
    }

    image operator+(image &Image, color_u8 Color)
    {
        color_u8* Pixel = (color_u8*)Image.Data;
        for(int Index=0; Index<Image.Width * Image.Height; Index++)
        {
            Pixel->r += Color.r;
            Pixel->g += Color.g;
            Pixel->b += Color.b;
            Pixel->a += Color.a;
            Pixel++;
        }

        return Image;
    }

    
    image &operator+=(image &Image, color_u8 Color)
    {   
        color_u8* Pixel = (color_u8*)Image.Data;

        for(int Index=0; Index<Image.Width * Image.Height; Index++)
        {
            Pixel->r = (u8)Min((u16)255, ((u16)Pixel->r + (u16)Color.r));
            Pixel->g = (u8)Min((u16)255, ((u16)Pixel->g + (u16)Color.g));
            Pixel->b = (u8)Min((u16)255, ((u16)Pixel->b + (u16)Color.b));
            Pixel->a = (u8)Min((u16)255, ((u16)Pixel->a + (u16)Color.a));
            Pixel++;
        }

        return Image;
    }

    image operator-(image &Image, color_u8 Color)
    {
        color_u8* Pixel = (color_u8*)Image.Data;
        for(int Index=0; Index<Image.Width * Image.Height; Index++)
        {
            *Pixel -= Color;
            Pixel++;
        }

        return Image;
    }

    
    image &operator-=(image &Image, color_u8 Color)
    {   
        Image = Image - Color;
        return Image;
    }

    image operator*(image &Image, color_f32 Color)
    {
        color_u8* Pixel = (color_u8*)Image.Data;
        for(int Index=0; Index<Image.Width * Image.Height; Index++)
        {
            *Pixel *= Color;
            Pixel++;
        }

        return Image;
    }
    image &operator*=(image &Image, color_f32 Color)
    {   
        Image = Image * Color;
        return Image;
    }
    

    image operator/(image &Image, color_f32 Color)
    {
        color_u8* Pixel = (color_u8*)Image.Data;
        for(int Index=0; Index<Image.Width * Image.Height; Index++)
        {
            *Pixel /= Color;
            Pixel++;
        }

        return Image;
    }
    image &operator/=(image &Image, color_f32 Color)
    {   
        Image = Image / Color;
        return Image;
    }
    
    image &operator+=(image &Image, color_s16 Color)
    {   
        color_u8* Pixel = (color_u8*)Image.Data;

        for(int Index=0; Index<Image.Width * Image.Height; Index++)
        {
            Pixel->r = (u8)Max((s16)0, Min((s16)255, ((s16)Pixel->r + Color.r)));
            Pixel->g = (u8)Max((s16)0, Min((s16)255, ((s16)Pixel->g + Color.g)));
            Pixel->b = (u8)Max((s16)0, Min((s16)255, ((s16)Pixel->b + Color.b)));
            Pixel->a = (u8)Max((s16)0, Min((s16)255, ((s16)Pixel->a + Color.a)));
            Pixel++;
        }

        return Image;
    }
    
    image &operator+=(image &Image,  s16 Value)
    {   
        color_u8* Pixel = (color_u8*)Image.Data;

        for(int Index=0; Index<Image.Width * Image.Height; Index++)
        {
            Pixel->r = (u8)Max((s16)0, Min((s16)255, ((s16)Pixel->r + Value)));
            Pixel->g = (u8)Max((s16)0, Min((s16)255, ((s16)Pixel->g + Value)));
            Pixel->b = (u8)Max((s16)0, Min((s16)255, ((s16)Pixel->b + Value)));
            Pixel->a = (u8)Max((s16)0, Min((s16)255, ((s16)Pixel->a + Value)));
            Pixel++;
        }

        return Image;
    }

    image &operator*(image &Image, f32 Value)
    {
        color_u8* Pixel = (color_u8*)Image.Data;

        for(int Index=0; Index<Image.Width * Image.Height; Index++)
        {
            Pixel->r = (u8)Max((s16)0, Min((s16)255, ((s16)((f32)Pixel->r * Value))));
            Pixel->g = (u8)Max((s16)0, Min((s16)255, ((s16)((f32)Pixel->g * Value))));
            Pixel->b = (u8)Max((s16)0, Min((s16)255, ((s16)((f32)Pixel->b * Value))));
            Pixel->a = (u8)Max((s16)0, Min((s16)255, ((s16)((f32)Pixel->a * Value))));
            Pixel++;
        }
        return Image;
    }


    image &operator+=(image &ImageA, image ImageB)
    {
        color_u8* ColorA = (color_u8*)ImageA.Data;
        color_u8* ColorB = (color_u8*)ImageB.Data;

        for(int Index=0; Index<ImageA.Width * ImageA.Height; Index++)
        {
            *ColorA += *ColorB;
            ColorA++;
            ColorB++;
        }
        return ImageA;        
    }


    image &operator-=(image &ImageA, image ImageB)
    {
        color_u8* ColorA = (color_u8*)ImageA.Data;
        color_u8* ColorB = (color_u8*)ImageB.Data;

        for(int Index=0; Index<ImageA.Width * ImageA.Height; Index++)
        {
            *ColorA -= *ColorB;
            ColorA++;
            ColorB++;
        }
        return ImageA;        
    }

    image &operator*=(image &ImageA, image ImageB)
    {
        color_u8* ColorA = (color_u8*)ImageA.Data;
        color_u8* ColorB = (color_u8*)ImageB.Data;

        for(int Index=0; Index<ImageA.Width * ImageA.Height; Index++)
        {
            *ColorA *= *ColorB;
            ColorA++;
            ColorB++;
        }
        return ImageA;        
    }


    image &operator/=(image &ImageA, image ImageB)
    {
        color_u8* ColorA = (color_u8*)ImageA.Data;
        color_u8* ColorB = (color_u8*)ImageB.Data;

        for(int Index=0; Index<ImageA.Width * ImageA.Height; Index++)
        {
            *ColorA /= *ColorB;
            ColorA++;
            ColorB++;
        }
        return ImageA;        
    }

    
    image Min(image *ImageA, image *ImageB)
    {
        image Image = DuplicateImage(ImageA);
        
        color_u8* ColorA = (color_u8*)ImageA->Data;
        color_u8* ColorB = (color_u8*)ImageB->Data;
		color_u8* ColorOutput = (color_u8*)(Image.Data);
			
        for(int Index=0; Index<ImageA->Width * ImageA->Height; Index++)
        {
            *ColorOutput = Min(*ColorA, *ColorB);
            ColorA++;
            ColorB++;
            ColorOutput++;
        }

        return Image;
    }
    
    image Max(image *ImageA, image *ImageB)
    {
        image Image = DuplicateImage(ImageA);
        
        color_u8* ColorA = (color_u8*)ImageA->Data;
        color_u8* ColorB = (color_u8*)ImageB->Data;
        color_u8* ColorOutput = (color_u8*)(Image.Data);

        for(int Index=0; Index<ImageA->Width * ImageA->Height; Index++)
        {
            *ColorOutput = Max(*ColorA, *ColorB);
            ColorA++;
            ColorB++;
            ColorOutput++;
        }

        return Image;
    }
    
}