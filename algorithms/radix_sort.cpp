#include "algorithm_interface.h"
#include "algorithm_registry.h"
#include <cmath>

/**
 * Radix Sort Algorithm (LSD - Least Significant Digit)
 * Sorts by processing digits from least to most significant
 *
 * State variables:
 * state[0] = current digit position (0=ones, 1=tens, 2=hundreds, etc.)
 * state[1] = current bucket index (0-9)
 * state[2] = array index for distribution
 * state[3] = phase (0=distribution, 1=collection)
 * state[4] = bucket array index for collection
 */
SwapResult radixSort(int array[], int size, int *state)
{
    int &digitPos = state[0];
    int &bucketIdx = state[1];
    int &arrayIdx = state[2];
    int &phase = state[3];
    int &bucketArrayIdx = state[4];

    SwapResult result = {-1, -1, false, false};

    // Static arrays for buckets and counts
    static int buckets[10][50]; // 10 buckets, max 50 elements each
    static int counts[10];      // Count of elements in each bucket

    // Initialize on first call
    if (digitPos == 0 && bucketIdx == 0 && arrayIdx == 0 && phase == 0)
    {
        // Clear counts
        for (int i = 0; i < 10; i++)
        {
            counts[i] = 0;
        }
    }

    // Check if sorting is complete (all digits processed)
    int maxValue = 0;
    for (int i = 0; i < size; i++)
    {
        if (array[i] > maxValue) maxValue = array[i];
    }
    
    int maxDigits = 1;
    while (maxValue /= 10) maxDigits++;

    if (digitPos >= maxDigits)
    {
        result.isComplete = true;
        return result;
    }

    // Handle different phases
    switch (phase)
    {
    case 0: // Distribution phase
        {
            if (arrayIdx >= size)
            {
                // Distribution complete, move to collection
                phase = 1;
                bucketIdx = 0;
                bucketArrayIdx = 0;
                arrayIdx = 0;
                return result;
            }

            // Get current digit
            int digit = (array[arrayIdx] / (int)pow(10, digitPos)) % 10;
            
            // Add to appropriate bucket
            buckets[digit][counts[digit]] = array[arrayIdx];
            counts[digit]++;
            
            arrayIdx++;
        }
        break;

    case 1: // Collection phase
        if (bucketIdx >= 10)
        {
            // All buckets collected, move to next digit
            digitPos++;
            phase = 0;
            arrayIdx = 0;
            bucketIdx = 0;
            
            // Clear counts for next iteration
            for (int i = 0; i < 10; i++)
            {
                counts[i] = 0;
            }
            return result;
        }

        if (bucketArrayIdx < counts[bucketIdx])
        {
            // Collect from current bucket
            array[arrayIdx] = buckets[bucketIdx][bucketArrayIdx];
            result.index1 = arrayIdx;
            result.index2 = bucketIdx;
            result.swapped = true;
            
            arrayIdx++;
            bucketArrayIdx++;
        }
        else
        {
            // Move to next bucket
            bucketIdx++;
            bucketArrayIdx = 0;
        }
        break;
    }

    return result;
} 