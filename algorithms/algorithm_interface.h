#pragma once

/**
 * Simple interface for sorting algorithms
 * This is the only header file algorithm developers need to understand
 */

struct SwapResult
{
    int index1;      // First element that was swapped (-1 if no swap)
    int index2;      // Second element that was swapped (-1 if no swap)
    bool swapped;    // True if a swap occurred this frame
    bool isComplete; // True if sorting is finished
};

/**
 * Function signature for sorting algorithms
 * @param array: Array to sort (modify in place)
 * @param size: Number of elements in array
 * @param state: Your algorithm's state variables (persistent across calls)
 * @return: Information about what happened this frame
 */
typedef SwapResult (*SortingFunction)(int array[], int size, int *state);

/**
 * Information about a registered algorithm
 */
struct AlgorithmInfo
{
    const char *name;
    SortingFunction function;
    int stateSize; // Number of integers needed for state
};
