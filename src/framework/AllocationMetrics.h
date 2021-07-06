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
 * this way of tracking/debugging memory is probably horrible
 */
extern struct AllocationMetrics e_AllocationMetrics;

static void PrintMemoryUsage()
{
    std::cout << "Memory Usage: " << e_AllocationMetrics.CurrentUsage() << " bytes\n";
}

static void PrintMemoryUsage(const std::string place)
{
    std::cout << "Memory Usage " << place << ": " << e_AllocationMetrics.CurrentUsage() << " bytes\n";
}