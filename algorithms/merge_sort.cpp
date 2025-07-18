#include "algorithm_interface.h"
#include "algorithm_registry.h"
#include <algorithm>

/**
 * Simplified Merge Sort Algorithm
 * Bottom-up merge sort implementation
 *
 * State variables:
 * state[0] = currentSize (current size of subarrays being merged)
 * state[1] = leftStart (start index of current merge)
 * state[2] = step (current step in merge process)
 * state[3] = leftIndex (current index in left subarray)
 * state[4] = rightIndex (current index in right subarray)
 * state[5] = mid (middle point of current merge)
 * state[6] = rightEnd (end of right subarray)
 */
SwapResult mergeSort(int array[], int size, int *state)
{
    int &currentSize = state[0];
    int &leftStart = state[1];
    int &step = state[2];
    int &leftIndex = state[3];
    int &rightIndex = state[4];
    int &mid = state[5];
    int &rightEnd = state[6];

    SwapResult result = {-1, -1, false, false};

    // Initialize on first call
    if (currentSize == 0)
    {
        currentSize = 1;
        leftStart = 0;
        step = 0;
    }

    // Check if sorting is complete
    if (currentSize >= size)
    {
        result.isComplete = true;
        return result;
    }

    // If we've processed all subarrays of current size, move to next size
    if (leftStart >= size)
    {
        currentSize *= 2;
        leftStart = 0;
        step = 0;
        if (currentSize >= size)
        {
            result.isComplete = true;
        }
        return result;
    }

    // Calculate bounds for current merge
    if (step == 0)
    {
        mid = std::min(leftStart + currentSize - 1, size - 1);
        rightEnd = std::min(leftStart + 2 * currentSize - 1, size - 1);

        // Skip if no merge needed
        if (mid >= rightEnd || mid >= size - 1)
        {
            leftStart += 2 * currentSize;
            return result;
        }

        leftIndex = leftStart;
        rightIndex = mid + 1;
        step = 1;
        return result;
    }

    // Perform one merge step
    if (step == 1)
    {
        // Find the smaller element and move it to correct position
        if (leftIndex <= mid && rightIndex <= rightEnd)
        {
            if (array[leftIndex] <= array[rightIndex])
            {
                leftIndex++;
            }
            else
            {
                // Move right element to left position
                int temp = array[rightIndex];
                for (int i = rightIndex; i > leftIndex; i--)
                {
                    array[i] = array[i - 1];
                }
                array[leftIndex] = temp;

                result.index1 = rightIndex;
                result.index2 = leftIndex;
                result.swapped = true;

                leftIndex++;
                mid++;
                rightIndex++;
            }
        }
        else
        {
            // Merge complete for this subarray
            leftStart += 2 * currentSize;
            step = 0;
        }
    }

    return result;
}