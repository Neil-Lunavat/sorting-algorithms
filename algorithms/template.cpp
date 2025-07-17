#include "algorithm_interface.h"
#include "algorithm_registry.h"

/**
 * TEMPLATE FOR NEW SORTING ALGORITHMS
 *
 * Copy this file and rename it to your_algorithm_name.cpp
 * Follow the example below to implement your sorting algorithm
 *
 * Remember: Each call to your function should perform ONE swap operation
 * The visualizer will call your function repeatedly until sorting is complete
 */

/**
 * Your sorting algorithm implementation
 *
 * @param array: The array to sort (modify this directly)
 * @param size: Number of elements in the array
 * @param state: Your persistent variables (use these to track progress)
 * @return: SwapResult indicating what happened this frame
 */
SwapResult yourAlgorithmName(int array[], int size, int *state)
{
    // Example state variables (adjust based on your algorithm needs):
    // int& i = state[0];      // Outer loop counter
    // int& j = state[1];      // Inner loop counter
    // int& phase = state[2];  // Algorithm phase/step

    SwapResult result = {-1, -1, false, false};

    // YOUR ALGORITHM LOGIC HERE
    //
    // Example structure:
    // 1. Check if sorting is complete
    // 2. Find the next pair of elements to compare
    // 3. If they need to be swapped:
    //    - Swap them in the array
    //    - Set result.index1 and result.index2
    //    - Set result.swapped = true
    // 4. Update your state variables for next frame
    // 5. If sorting is complete, set result.isComplete = true

    return result;
}

/**
 * REGISTRATION: To register your algorithm, add it to register_algorithms.cpp
 *
 * Example:
 * 1. Add a forward declaration: extern SwapResult yourAlgorithmName(int array[], int size, int* state);
 * 2. Add the registration call: registerAlgorithm("Your Algorithm Name", yourAlgorithmName, 3);
 */
