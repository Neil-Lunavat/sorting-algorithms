#include "sorting_algorithms.h"
#include <algorithm>

// Bubble Sort - performs one comparison and potential swap per frame
bool BubbleSort::performOneStep(std::vector<int> &array, SortState &state)
{
    if (state.isComplete)
        return false;

    int n = array.size();
    bool swapped = false;

    // If we've completed a full pass without swaps, we're done
    if (state.i >= n - 1)
    {
        state.isComplete = true;
        return false;
    }

    // Perform one comparison
    if (state.j < n - state.i - 1)
    {
        if (array[state.j] > array[state.j + 1])
        {
            std::swap(array[state.j], array[state.j + 1]);
            swapped = true;
            state.swapped = true;
        }
        state.j++;
    }
    else
    {
        // End of current pass
        state.j = 0;
        state.i++;
        if (!state.swapped)
        {
            state.isComplete = true;
        }
        state.swapped = false;
    }

    return swapped;
}

void BubbleSort::reset(SortState &state)
{
    state.i = 0;
    state.j = 0;
    state.swapped = false;
    state.isComplete = false;
}

// Selection Sort - finds minimum and swaps at end of each pass
bool SelectionSort::performOneStep(std::vector<int> &array, SortState &state)
{
    if (state.isComplete)
        return false;

    int n = array.size();

    // Start new pass
    if (state.j == state.i)
    {
        minIndex = state.i;
        state.j++;
    }

    // Find minimum in remaining array
    if (state.j < n)
    {
        if (array[state.j] < array[minIndex])
        {
            minIndex = state.j;
        }
        state.j++;
    }
    else
    {
        // End of pass - perform swap if needed
        bool swapped = false;
        if (minIndex != state.i)
        {
            std::swap(array[state.i], array[minIndex]);
            swapped = true;
        }

        state.i++;
        if (state.i >= n - 1)
        {
            state.isComplete = true;
        }
        else
        {
            state.j = state.i;
        }
        return swapped;
    }

    return false;
}

void SelectionSort::reset(SortState &state)
{
    state.i = 0;
    state.j = 0;
    state.swapped = false;
    state.isComplete = false;
    minIndex = 0;
}

// Insertion Sort - inserts one element at a time
bool InsertionSort::performOneStep(std::vector<int> &array, SortState &state)
{
    if (state.isComplete)
        return false;

    int n = array.size();

    // Start with second element
    if (state.i == 0)
    {
        state.i = 1;
        if (state.i >= n)
        {
            state.isComplete = true;
            return false;
        }
        key = array[state.i];
        state.j = state.i - 1;
    }

    // Shift elements
    if (state.j >= 0 && array[state.j] > key)
    {
        array[state.j + 1] = array[state.j];
        state.j--;
        return true; // Animation step
    }
    else
    {
        // Place the key in correct position
        array[state.j + 1] = key;
        state.i++;

        if (state.i >= n)
        {
            state.isComplete = true;
        }
        else
        {
            key = array[state.i];
            state.j = state.i - 1;
        }
        return false; // No visual change this frame
    }
}

void InsertionSort::reset(SortState &state)
{
    state.i = 0;
    state.j = 0;
    state.swapped = false;
    state.isComplete = false;
    key = 0;
}
