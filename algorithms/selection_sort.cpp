#include "algorithm_interface.h"
#include "algorithm_registry.h"

/**
 * Selection Sort Algorithm
 * Finds the minimum element and places it at the beginning
 *
 * State variables:
 * state[0] = i (current position being filled)
 * state[1] = j (current search position)
 * state[2] = minIndex (index of minimum element found so far)
 */
SwapResult selectionSort(int array[], int size, int *state)
{
    int &i = state[0];        // Current position to fill
    int &j = state[1];        // Current search position
    int &minIndex = state[2]; // Index of minimum element

    SwapResult result = {-1, -1, false, false};

    // Check if sorting is complete
    if (i >= size - 1)
    {
        result.isComplete = true;
        return result;
    }

    // Start new pass: initialize search
    if (j == i)
    {
        minIndex = i;
        j++;
        return result; // No swap this frame
    }

    // Continue searching for minimum
    if (j < size)
    {
        if (array[j] < array[minIndex])
        {
            minIndex = j;
        }
        j++;
        return result; // No swap this frame
    }

    // End of pass: perform swap if needed
    if (minIndex != i)
    {
        int temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;

        result.index1 = i;
        result.index2 = minIndex;
        result.swapped = true;
    }

    // Move to next position
    i++;
    j = i;

    return result;
}
