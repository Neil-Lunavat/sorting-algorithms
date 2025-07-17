#include "algorithm_interface.h"
#include <vector>
#include <cstring>

static std::vector<AlgorithmInfo> registeredAlgorithms;

/**
 * Register a new sorting algorithm
 * Call this function to add your algorithm to the visualizer
 */
void registerAlgorithm(const char *name, SortingFunction function, int stateSize)
{
    AlgorithmInfo info;
    info.name = name;
    info.function = function;
    info.stateSize = stateSize;
    registeredAlgorithms.push_back(info);
}

/**
 * Get all registered algorithms
 */
std::vector<AlgorithmInfo> getRegisteredAlgorithms()
{
    return registeredAlgorithms;
}

/**
 * Get algorithm by name
 */
AlgorithmInfo *getAlgorithmByName(const char *name)
{
    for (auto &algo : registeredAlgorithms)
    {
        if (strcmp(algo.name, name) == 0)
        {
            return &algo;
        }
    }
    return nullptr;
}

/**
 * Get algorithm by index
 */
AlgorithmInfo *getAlgorithmByIndex(int index)
{
    if (index >= 0 && index < static_cast<int>(registeredAlgorithms.size()))
    {
        return &registeredAlgorithms[index];
    }
    return nullptr;
}

/**
 * Get number of registered algorithms
 */
int getAlgorithmCount()
{
    return registeredAlgorithms.size();
}
