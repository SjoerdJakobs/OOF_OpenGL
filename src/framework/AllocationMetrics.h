#pragma once
#include <cstdint>
#include <iostream>

struct AllocationMetrics
{
	uint32_t TotalAllocated = 0;
	uint32_t TotalFreed = 0;

	uint32_t CurrentUsage() const { return TotalAllocated - TotalFreed; }
};

/**
 * MY MIIIIND IS TELLING ME NO..... but my body
 * this way of tracking/debugging memory is probably horrible but it does what i need it to do
 */
extern struct AllocationMetrics e_AllocationMetrics;

static void PrintMemoryUsage()
{
#ifdef _DEBUG
	std::cout << "Memory Usage: " << e_AllocationMetrics.CurrentUsage() << " bytes\n";
#endif
}

static void PrintMemoryUsage(const std::string place)
{
#ifdef _DEBUG
	std::cout << "Memory Usage " << place << ": " << e_AllocationMetrics.CurrentUsage() << " bytes\n";
#endif
}