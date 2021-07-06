#pragma once
#include "AllocationMetrics.h"

AllocationMetrics e_AllocationMetrics;

void* operator new(size_t size)
{
	/*if(size > 24)
	{
		std::cout << "allocating " << size << " bytes\n";		
	}*/
    e_AllocationMetrics.TotalAllocated += size;
    return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	/*if (size > 24)
	{
		std::cout << "deleting " << size << " bytes\n";
	}*/
    e_AllocationMetrics.TotalFreed += size;
    return free(memory);
}