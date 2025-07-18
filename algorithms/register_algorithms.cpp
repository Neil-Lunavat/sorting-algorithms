#include "algorithm_registry.h"

// Forward declarations of algorithm functions
extern SwapResult bubbleSort(int array[], int size, int *state);
extern SwapResult selectionSort(int array[], int size, int *state);
extern SwapResult shellSort(int array[], int size, int *state);
extern SwapResult mergeSort(int array[], int size, int *state);
extern SwapResult quickSort(int array[], int size, int *state);
extern SwapResult radixSort(int array[], int size, int *state);

/**
 * Register all algorithms explicitly
 * This function is called at startup to ensure all algorithms are registered
 */
void registerAllAlgorithms()
{
    registerAlgorithm("Bubble Sort", bubbleSort, 2);
    registerAlgorithm("Selection Sort", selectionSort, 3);
    registerAlgorithm("Shell Sort", shellSort, 5);
    registerAlgorithm("Merge Sort", mergeSort, 7);
    registerAlgorithm("Quick Sort", quickSort, 8);
    registerAlgorithm("Radix Sort", radixSort, 5);
}
