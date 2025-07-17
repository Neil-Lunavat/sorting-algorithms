#pragma once
#include "algorithm_interface.h"
#include <vector>

/**
 * Algorithm registry functions
 * These functions manage the list of available sorting algorithms
 */

void registerAlgorithm(const char *name, SortingFunction function, int stateSize);
std::vector<AlgorithmInfo> getRegisteredAlgorithms();
AlgorithmInfo *getAlgorithmByName(const char *name);
AlgorithmInfo *getAlgorithmByIndex(int index);
int getAlgorithmCount();
