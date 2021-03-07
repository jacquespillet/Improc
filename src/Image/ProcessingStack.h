#pragma once

#include "Image.h"
#include <string>

#include <iostream>
#include "Processes/ColorProcess.h"
#include "Processes/LoadImageProcess.h"
#include "Processes/SpatialProcess.h"

namespace ImProc{

    void Process(image *In, image *Out, process *Process);

    void DeallocateProcess(process *Process);

    process *AddProcess(processes_stack *Stack, process *Process);

    void ClearStack(processes_stack *Stack);

    void ProcessStack(image *In, image *Out, processes_stack Stack);

    void RemoveProcessFromStack(processes_stack *Stack, u32 Index);

}