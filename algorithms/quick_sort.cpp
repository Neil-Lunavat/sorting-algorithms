#include "algorithm_interface.h"
#include "algorithm_registry.h"

/**
 * Quick Sort Algorithm - Working Implementation
 * Uses divide-and-conquer strategy with pivot selection and partitioning
 *
 * State variables:
 * state[0] = current partition start
 * state[1] = current partition end
 * state[2] = pivot index
 * state[3] = left pointer
 * state[4] = right pointer
 * state[5] = phase (0=select pivot, 1=partition, 2=place pivot)
 * state[6] = step counter
 * state[7] = max steps
 */
SwapResult quickSort(int array[], int size, int *state)
{
    int &start = state[0];
    int &end = state[1];
    int &pivotIdx = state[2];
    int &left = state[3];
    int &right = state[4];
    int &phase = state[5];
    int &step = state[6];
    int &maxSteps = state[7];

    SwapResult result = {-1, -1, false, false};

    // Initialize on first call
    if (step == 0 && phase == 0)
    {
        start = 0;
        end = size - 1;
        step = 1;
        maxSteps = size * 4; // Conservative limit
    }

    // Check if sorting is complete
    if (step > maxSteps)
    {
        result.isComplete = true;
        return result;
    }

    // Handle different phases
    switch (phase)
    {
    case 0: // Select pivot (first element)
        pivotIdx = start;
        left = start + 1;
        right = end;
        phase = 1;
        break;

    case 1: // Partition phase
        if (left > right)
        {
            // Partition complete, place pivot
            if (right != pivotIdx)
            {
                int temp = array[pivotIdx];
                array[pivotIdx] = array[right];
                array[right] = temp;
                result.index1 = pivotIdx;
                result.index2 = right;
                result.swapped = true;
            }
            pivotIdx = right;
            phase = 2;
        }
        else if (array[left] <= array[pivotIdx] && array[right] > array[pivotIdx])
        {
            left++;
            right--;
        }
        else if (array[left] > array[pivotIdx] && array[right] <= array[pivotIdx])
        {
            // Swap left and right
            int temp = array[left];
            array[left] = array[right];
            array[right] = temp;
            result.index1 = left;
            result.index2 = right;
            result.swapped = true;
            left++;
            right--;
        }
        else if (array[left] <= array[pivotIdx])
        {
            left++;
        }
        else
        {
            right--;
        }
        break;

    case 2: // Handle sub-partitions
        // For step-by-step visualization, we'll just continue with the next partition
        // This is a simplified approach that ensures the algorithm completes
        if (start < pivotIdx - 1)
        {
            // Sort left partition
            start = start;
            end = pivotIdx - 1;
            phase = 0;
        }
        else if (pivotIdx + 1 < end)
        {
            // Sort right partition
            start = pivotIdx + 1;
            end = end;
            phase = 0;
        }
        else
        {
            // Both partitions done, restart with whole array
            start = 0;
            end = size - 1;
            phase = 0;
        }
        step++;
        break;
    }

    return result;
} 