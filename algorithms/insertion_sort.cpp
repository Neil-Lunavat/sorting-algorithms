#include "algorithm_interface.h"
#include "algorithm_registry.h"

/**
 * Insertion Sort Algorithm
 * Builds the sorted array one element at a time
 * 
 * State variables:
 * state[0] = i (current element being inserted)
 * state[1] = j (current comparison position)
 * state[2] = key (value being inserted)
 */
SwapResult insertionSort(int array[], int size, int* state) {
    int& i = state[0];    // Current element to insert
    int& j = state[1];    // Current comparison position
    int& key = state[2];  // Value being inserted
    
    SwapResult result = {-1, -1, false, false};
    
    // Check if sorting is complete
    if (i >= size) {
        result.isComplete = true;
        return result;
    }
    
    // Start inserting new element
    if (j == -1) {
        key = array[i];
        j = i - 1;
        
        // If already at beginning or already sorted
        if (j < 0 || array[j] <= key) {
            i++;
            j = -1;
            return result;  // No swap needed
        }
        
        return result;  // No swap this frame
    }
    
    // Continue moving element leftward
    if (j >= 0 && array[j] > key) {
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
    
    // Move to next element
    i++;
    j = -1;
    
    return result;
}

/**
 * Register the algorithm
 */
static bool registered = []() {
    registerAlgorithm("Insertion Sort", insertionSort, 3);
    return true;
}();
