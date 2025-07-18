#include "algorithm_interface.h"
#include "algorithm_registry.h"
#include <algorithm>

/**
 * Merge Sort Algorithm
 * Divide and conquer algorithm that recursively splits and merges arrays
 *
 * State variables:
 * state[0] = currentSize (current size of subarrays being merged)
 * state[1] = leftStart (start index of left subarray)
 * state[2] = mergeIndex (current index in merge process)
 * state[3] = leftIndex (current index in left subarray)
 * state[4] = rightIndex (current index in right subarray)
 * state[5] = phase (0 = setup, 1 = merging, 2 = copying back)
 * state[6] = tempArraySize (size of temporary array)
 * state[7-16] = tempArray (temporary storage for merging - limited to 10 elements)
 */
SwapResult mergeSort(int array[], int size, int *state)
{
    int &currentSize = state[0];
    int &leftStart = state[1];
    int &mergeIndex = state[2];
    int &leftIndex = state[3];
    int &rightIndex = state[4];
    int &phase = state[5];
    int &tempArraySize = state[6];
    int *tempArray = &state[7]; // Use state[7] onwards as temporary array

    SwapResult result = {-1, -1, false, false};

    // Initialize on first call
    if (currentSize == 0)
    {
        currentSize = 1;
        leftStart = 0;
        phase = 0;
    }

    // Check if sorting is complete
    if (currentSize >= size)
    {
        result.isComplete = true;
        return result;
    }

    // Setup phase - find next merge operation
    if (phase == 0)
    {
        if (leftStart >= size - 1)
        {
            currentSize *= 2;
            leftStart = 0;
            if (currentSize >= size)
            {
                result.isComplete = true;
                return result;
            }
        }

        int mid = std::min(leftStart + currentSize - 1, size - 1);
        int rightEnd = std::min(leftStart + 2 * currentSize - 1, size - 1);

        if (mid >= rightEnd)
        {
            leftStart += 2 * currentSize;
            return result;
        }

        // Setup merge
        leftIndex = leftStart;
        rightIndex = mid + 1;
        mergeIndex = 0;
        tempArraySize = rightEnd - leftStart + 1;
        phase = 1;
        return result;
    }

    // Merging phase
    if (phase == 1)
    {
        int mid = std::min(leftStart + currentSize - 1, size - 1);
        int rightEnd = std::min(leftStart + 2 * currentSize - 1, size - 1);

        if (leftIndex <= mid && rightIndex <= rightEnd)
        {
            if (array[leftIndex] <= array[rightIndex])
            {
                tempArray[mergeIndex] = array[leftIndex];
                result.index1 = leftIndex;
                result.index2 = leftStart + mergeIndex;
                leftIndex++;
            }
            else
            {
                tempArray[mergeIndex] = array[rightIndex];
                result.index1 = rightIndex;
                result.index2 = leftStart + mergeIndex;
                rightIndex++;
            }
            mergeIndex++;
            result.swapped = true;
        }
        else if (leftIndex <= mid)
        {
            tempArray[mergeIndex] = array[leftIndex];
            result.index1 = leftIndex;
            result.index2 = leftStart + mergeIndex;
            leftIndex++;
            mergeIndex++;
            result.swapped = true;
        }
        else if (rightIndex <= rightEnd)
        {
            tempArray[mergeIndex] = array[rightIndex];
            result.index1 = rightIndex;
            result.index2 = leftStart + mergeIndex;
            rightIndex++;
            mergeIndex++;
            result.swapped = true;
        }
        else
        {
            // Copy back to original array
            for (int i = 0; i < tempArraySize; i++)
            {
                array[leftStart + i] = tempArray[i];
            }
            leftStart += 2 * currentSize;
            phase = 0;
        }
    }

    return result;
}
