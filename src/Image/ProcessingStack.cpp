#include "ProcessingStack.h"
#include "malloc.h"

#include "Processes/ColorProcess.h"
#include "Processes/LoadImageProcess.h"

namespace ImProc{
    void Process(image *In, image *Out, process *Process)
    {
        (*Process->ProcessFunction)(In, Out, Process);
    }



    void DeallocateProcess(process *Process)
    {
        DeallocateImage(&Process->Output);
        (*Process->DeallocateFunction)(Process);
        free(Process);
    }

    process* AddProcess(processes_stack *Stack, process *Process)
    {
        Stack->NumProcesses++;
        Stack->Processes = (process *) realloc(Stack->Processes, Stack->NumProcesses * sizeof(process));
        memcpy(&Stack->Processes[Stack->NumProcesses-1], Process, sizeof(process));
        free(Process);

        return &Stack->Processes[Stack->NumProcesses-1];
    }

    void ClearStack(processes_stack *Stack)
    {
        free(Stack->Processes);
        Stack->NumProcesses=0;
    }

    void ProcessStack(image *In, image *Out, processes_stack Stack)
    {
        image Tmp = EmptyImage(In->Width, In->Height);

        if(Stack.NumProcesses==1)
        {
            Process(In, Out, &Stack.Processes[0]);
        }
        else
        {
            for(int i=0; i<Stack.NumProcesses; i++)
            {
                if(i == Stack.NumProcesses-1)
                {
                    if(Stack.NumProcesses % 2 ==0) Process(&Tmp, Out, &Stack.Processes[i]);
                    else Process(In, Out, &Stack.Processes[i]);
                }
                else if(i % 2 == 0)
                {
                    Process(In, &Tmp, &Stack.Processes[i]);
                } 
                else
                {
                    Process(&Tmp, In, &Stack.Processes[i]);
                }
            }
        }

        DeallocateImage(&Tmp);

        u8 t = 0;
    }


    void RemoveProcessFromStack(processes_stack *Stack, u32 Index)
    {
        u32 NumToCopy = Stack->NumProcesses - Index - 1;
        memcpy(&Stack->Processes[Index], &Stack->Processes[Index+1], NumToCopy * sizeof(process));
        Stack->NumProcesses--;
        Stack->Processes = (process *)realloc(Stack->Processes, Stack->NumProcesses * sizeof(process));
    }
}