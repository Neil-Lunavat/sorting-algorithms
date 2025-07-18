#include "algorithm_interface.h"
#include "algorithm_registry.h"

/**
 * Insertion Sort Algorithm
 * Builds the sorted array one element at a time, starting from the second element
 *
 * State variables:
 * state[0] = i (current element being inserted, starts at 1)
 * state[1] = j (current comparison position, -1 means start new element)
 * state[2] = key (value being inserted)
 */
SwapResult insertionSort(int array[], int size, int *state)
{
    int &i = state[0];   // Current element to insert
    int &j = state[1];   // Current comparison position
    int &key = state[2]; // Value being inserted

    SwapResult result = {-1, -1, false, false};

    // Initialize i to start from the second element (index 1)
    if (i == 0)
    {
        i = 1;
        j = -1; // Flag to indicate we need to start a new element
    }

    // Check if sorting is complete
    if (i >= size)
    {
        result.isComplete = true;
        return result;
    }

    // Start inserting new element
    if (j == -1)
    {
        key = array[i];
        j = i - 1;

        // If we're at the beginning or element is already in correct position
        if (j < 0 || array[j] <= key)
        {
            i++;
            j = -1;
            return result; // No swap needed, element is already sorted
        }

        // We need to start shifting, so return without doing anything this frame
        return result;
    }

    // Shift elements to the right while they're greater than key
    if (j >= 0 && array[j] > key)
    {
        // Shift element to the right
        array[j + 1] = array[j];

        result.index1 = j;
        result.index2 = j + 1;
        result.swapped = true;

        j--;
        return result;
    }

    // Found correct position, insert the key
    array[j + 1] = key;

    // Only show this as a swap if we actually moved the key to a different position
    if (j + 1 != i)
    {
        result.index1 = j + 1;
        result.index2 = i;
        result.swapped = true;
    }

    // Move to next element
    i++;
    j = -1;

    return result;
}
