#include "algorithm_interface.h"
#include "algorithm_registry.h"

/**
 * Bubble Sort Algorithm
 * Compares adjacent elements and swaps them if they are in wrong order
 *
 * State variables:
 * state[0] = i (outer loop - current pass)
 * state[1] = j (inner loop - current comparison)
 */
SwapResult bubbleSort(int array[], int size, int *state)
{
    int &i = state[0]; // Current pass
    int &j = state[1]; // Current comparison position

    SwapResult result = {-1, -1, false, false};

    // Check if sorting is complete
    if (i >= size - 1)
    {
        result.isComplete = true;
        return result;
    }

    // Check if current pass is complete
    if (j >= size - 1 - i)
    {
        i++;           // Move to next pass
        j = 0;         // Reset inner loop
        return result; // No swap this frame
    }

    // Compare adjacent elements
    if (array[j] > array[j + 1])
    {
        // Swap elements
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;

        // Record the swap
        result.index1 = j;
        result.index2 = j + 1;
        result.swapped = true;
    }

    j++; // Move to next comparison
    return result;
}
