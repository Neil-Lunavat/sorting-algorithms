# Contributing to Sorting Algorithm Visualizer

Thank you for your interest in contributing to this educational sorting algorithm visualizer! This project is designed to help students learn about sorting algorithms by implementing them in a simple, visual way.

## Quick Start

### Adding a New Sorting Algorithm

1. **Copy the template**: Copy `algorithms/template.cpp` to `algorithms/your_algorithm_name.cpp`
2. **Implement your algorithm**: Follow the simple function interface
3. **Test your implementation**: Build and run the visualizer
4. **Submit a pull request**: Share your algorithm with others!

## Algorithm Interface

All sorting algorithms must follow this simple interface:

```cpp
SwapResult yourAlgorithm(int array[], int size, int* state);
```

### Parameters

-   `array[]`: The array to sort (modify this directly)
-   `size`: Number of elements in the array
-   `state[]`: Your persistent variables (survives between function calls)

### Return Value

Return a `SwapResult` struct with:

-   `index1`, `index2`: Which elements were swapped (-1 if no swap)
-   `swapped`: `true` if a swap occurred this frame
-   `isComplete`: `true` if sorting is finished

### Key Rules

1. **One swap per call**: Each function call should perform at most one swap
2. **Use state array**: Store your loop counters and variables in the `state` array
3. **Return swap info**: Always return information about what happened

## Example: Bubble Sort

Here's a complete example of how to implement bubble sort:

```cpp
#include "algorithm_interface.h"
#include "algorithm_registry.h"

SwapResult bubbleSort(int array[], int size, int* state) {
    int& i = state[0];  // Outer loop counter
    int& j = state[1];  // Inner loop counter

    SwapResult result = {-1, -1, false, false};

    // Check if sorting is complete
    if (i >= size - 1) {
        result.isComplete = true;
        return result;
    }

    // Check if current pass is complete
    if (j >= size - 1 - i) {
        i++;  // Next pass
        j = 0;  // Reset inner loop
        return result;  // No swap this frame
    }

    // Compare adjacent elements
    if (array[j] > array[j + 1]) {
        // Swap them
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;

        // Report the swap
        result.index1 = j;
        result.index2 = j + 1;
        result.swapped = true;
    }

    j++;  // Next comparison
    return result;
}

// No registration needed in your algorithm file!
// Just implement the function and it will be registered automatically
// when you add it to register_algorithms.cpp
```

## Step-by-Step Implementation Guide

### 1. Plan Your Algorithm

-   Identify what variables you need (loop counters, temporary values, etc.)
-   Think about how your algorithm progresses step by step
-   Consider when swaps occur and when the algorithm is complete

### 2. Set Up State Variables

```cpp
int& i = state[0];     // First variable
int& j = state[1];     // Second variable
int& temp = state[2];  // Third variable (if needed)
```

### 3. Implement the Logic

-   Check if sorting is complete first
-   Perform your algorithm's next logical step
-   If a swap is needed, do it and report it
-   Update your state variables for the next call

### 4. Register Your Algorithm

To register your algorithm:

1. **Add a forward declaration** in `algorithms/register_algorithms.cpp`:

    ```cpp
    extern SwapResult yourAlgorithmName(int array[], int size, int* state);
    ```

2. **Add the registration call** in the `registerAllAlgorithms()` function:

    ```cpp
    registerAlgorithm("Your Algorithm Name", yourAlgorithmName, stateSize);
    ```

3. **Update the build script** to include your algorithm file in compilation.

That's it! No complex registration code needed in your algorithm file.

## Testing Your Algorithm

1. **Build the project**: Use the provided build system
2. **Run the visualizer**: Your algorithm should appear in the algorithm list
3. **Test step-by-step**: Use the pause and step functions to verify correctness
4. **Check edge cases**: Test with small arrays and different initial states

## Common Patterns

### Simple Comparison-Based Sorts

Most sorting algorithms follow this pattern:

1. Use outer loop for passes/positions
2. Use inner loop for comparisons
3. Swap when elements are out of order
4. Track completion when no more passes needed

### Multi-Phase Algorithms

Some algorithms have distinct phases:

1. Use a phase variable in state
2. Handle each phase separately
3. Transition between phases as needed

## Pull Request Guidelines

1. **Use descriptive names**: Name your file clearly (e.g., `quick_sort.cpp`)
2. **Add comments**: Explain your algorithm's approach
3. **Test thoroughly**: Ensure your algorithm works correctly
4. **Follow the template**: Use the provided structure

## Common Issues and Solutions

### Algorithm Never Completes

-   Make sure you set `result.isComplete = true` when done
-   Check that your loop counters eventually reach termination conditions

### No Swaps Visible

-   Ensure you're setting `result.swapped = true` when swapping
-   Set `result.index1` and `result.index2` to the swapped positions

### Algorithm Runs Too Fast

-   Remember: one swap per function call
-   Use state variables to track progress between calls

### State Variables Reset

-   Don't initialize state variables inside your function
-   Use references: `int& i = state[0];`

## Getting Help

-   Check existing algorithms for examples
-   Read the template file comments
-   Ask questions in GitHub issues
-   Review the project documentation

Happy coding! 🎉
