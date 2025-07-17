#pragma once
#include <vector>

// Structure to hold the current state of sorting
struct SortState
{
    int i = 0;               // Current position in outer loop
    int j = 0;               // Current position in inner loop
    bool swapped = false;    // Track if a swap occurred this frame
    bool isComplete = false; // Track if sorting is complete
};

// Base class for sorting algorithms
class SortingAlgorithm
{
public:
    virtual ~SortingAlgorithm() = default;
    virtual bool performOneStep(std::vector<int> &array, SortState &state) = 0;
    virtual void reset(SortState &state) = 0;
    virtual const char *getName() const = 0;
};

// Bubble Sort implementation
class BubbleSort : public SortingAlgorithm
{
public:
    bool performOneStep(std::vector<int> &array, SortState &state) override;
    void reset(SortState &state) override;
    const char *getName() const override { return "Bubble Sort"; }
};

// Selection Sort implementation
class SelectionSort : public SortingAlgorithm
{
private:
    int minIndex = 0;

public:
    bool performOneStep(std::vector<int> &array, SortState &state) override;
    void reset(SortState &state) override;
    const char *getName() const override { return "Selection Sort"; }
};

// Insertion Sort implementation
class InsertionSort : public SortingAlgorithm
{
private:
    int key = 0;

public:
    bool performOneStep(std::vector<int> &array, SortState &state) override;
    void reset(SortState &state) override;
    const char *getName() const override { return "Insertion Sort"; }
};
