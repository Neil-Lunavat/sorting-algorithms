#include "algorithm_interface.h"
#include "algorithm_registry.h"

/**
 * Shell Sort Algorithm
 * Uses a sequence of gaps to sort elements at different intervals
 *
 * State variables:
 * state[0] = gap (current gap size)
 * state[1] = i (current element being processed)
 * state[2] = j (position for insertion)
 * state[3] = temp (temporary value for insertion)
 * state[4] = phase (0 = start gap, 1 = insertion phase, 2 = gap reduction)
 */
SwapResult shellSort(int array[], int size, int *state)
{
    int &gap = state[0];
    int &i = state[1];
    int &j = state[2];
    int &temp = state[3];
    int &phase = state[4];

    SwapResult result = {-1, -1, false, false};

    // Initialize gap on first call
    if (gap == 0)
    {
        gap = size / 2;
        i = gap;
        phase = 0;
    }

    // Check if sorting is complete
    if (gap == 0)
    {
        result.isComplete = true;
        return result;
    }

    // Start new gap sequence
    if (phase == 0)
    {
        if (i >= size)
        {
            gap = gap / 2;
            i = gap;
            if (gap == 0)
            {
                result.isComplete = true;
                return result;
            }
        }
        temp = array[i];
        j = i;
        phase = 1;
        return result;
    }

    // Insertion phase
    if (phase == 1)
    {
        if (j >= gap && array[j - gap] > temp)
        {
            array[j] = array[j - gap];
            result.index1 = j - gap;
            result.index2 = j;
            result.swapped = true;
            j -= gap;
        }
        else
        {
            array[j] = temp;
            if (j != i)
            {
                result.index1 = j;
                result.index2 = i;
                result.swapped = true;
            }
            i++;
            phase = 0;
        }
    }

    return result;
}
