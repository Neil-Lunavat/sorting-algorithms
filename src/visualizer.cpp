#include "visualizer.h"
#include "../algorithms/algorithm_registry.h"
#include <random>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstring>

const float SortingVisualizer::FRAME_DURATION = 1.0f / 60.0f;

SortingVisualizer::SortingVisualizer(sf::RenderWindow &win)
    : window(win), array(nullptr), originalArray(nullptr), arraySize(7),
      currentAlgorithm(nullptr), currentAlgorithmIndex(0),
      isPaused(true), stepCount(0), swapCount(0), highlightIndex1(-1), highlightIndex2(-1),
      sortingComplete(false), comparisonModeActive(false)
{
    // Allocate dynamic arrays
    array = new int[MAX_ARRAY_SIZE];
    originalArray = new int[MAX_ARRAY_SIZE];

    // Initialize array with simple values
    initializeArray();
}

SortingVisualizer::~SortingVisualizer()
{
    // Clean up dynamic arrays
    delete[] array;
    delete[] originalArray;
}

bool SortingVisualizer::initialize()
{
    // Initialize UI (always succeeds now)
    ui.initialize();

    // Initialize comparison mode
    comparisonMode.initialize();

    // Check if algorithms are registered
    int algorithmCount = getAlgorithmCount();

    if (algorithmCount > 0)
    {
        currentAlgorithm = getAlgorithmByIndex(0);
        if (currentAlgorithm)
        {
            resetAlgorithm();
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

void SortingVisualizer::initializeArray()
{
    // Create a simple array with values 1 to arraySize
    for (int i = 0; i < arraySize; i++)
    {
        array[i] = i + 1;
    }

    // Shuffle the array
    randomizeArray();

    // Save original for reset
    for (int i = 0; i < arraySize; i++)
    {
        originalArray[i] = array[i];
    }
}

void SortingVisualizer::randomizeArray()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(array, array + arraySize, gen);
}

void SortingVisualizer::resetAlgorithm()
{
    if (!currentAlgorithm)
        return;

    // Reset array to original state
    for (int i = 0; i < arraySize; i++)
    {
        array[i] = originalArray[i];
    }

    // Clear algorithm state
    std::memset(algorithmState, 0, sizeof(algorithmState));

    // Reset visualization state
    stepCount = 0;
    swapCount = 0;
    highlightIndex1 = -1;
    highlightIndex2 = -1;
    sortingComplete = false;

    // Update UI
    ui.updateAlgorithmName(currentAlgorithm->name);
    ui.updateInstructions(isPaused);
    ui.updateArrayDisplay(array, arraySize);
    ui.updateStepInfo(stepCount, sortingComplete);
    ui.updateSwapInfo(swapCount);
    ui.updateArraySize(arraySize);
    
    // Update algorithm-specific information
    updateAlgorithmInfo();
    updateArrayStats();
}

void SortingVisualizer::stepForward()
{
    if (!currentAlgorithm || sortingComplete)
        return;

    SwapResult result = currentAlgorithm->function(array, arraySize, algorithmState);

    if (result.swapped)
    {
        highlightIndex1 = result.index1;
        highlightIndex2 = result.index2;
        stepCount++;
        swapCount++;
    }
    else
    {
        highlightIndex1 = -1;
        highlightIndex2 = -1;
    }

    sortingComplete = result.isComplete;

    // Update UI
    ui.updateArrayDisplay(array, arraySize);
    ui.updateStepInfo(stepCount, sortingComplete);
    ui.updateSwapInfo(swapCount);
    updateArrayStats();
}

void SortingVisualizer::stepBackward()
{
    // TODO: Implement step backward functionality
    // This would require storing history of array states
}

void SortingVisualizer::nextAlgorithm()
{
    int algorithmCount = getAlgorithmCount();
    if (algorithmCount <= 1)
        return;

    currentAlgorithmIndex = (currentAlgorithmIndex + 1) % algorithmCount;
    currentAlgorithm = getAlgorithmByIndex(currentAlgorithmIndex);
    resetAlgorithm();
}

void SortingVisualizer::selectAlgorithm(int algorithmIndex)
{
    int algorithmCount = getAlgorithmCount();
    if (algorithmIndex >= 0 && algorithmIndex < algorithmCount)
    {
        currentAlgorithmIndex = algorithmIndex;
        currentAlgorithm = getAlgorithmByIndex(currentAlgorithmIndex);
        resetAlgorithm();
    }
}

void SortingVisualizer::increaseArraySize()
{
    if (arraySize < MAX_ARRAY_SIZE)
    {
        resizeArray(arraySize + 1);
    }
}

void SortingVisualizer::decreaseArraySize()
{
    if (arraySize > MIN_ARRAY_SIZE)
    {
        resizeArray(arraySize - 1);
    }
}

void SortingVisualizer::resizeArray(int newSize)
{
    if (newSize < MIN_ARRAY_SIZE || newSize > MAX_ARRAY_SIZE)
        return;

    arraySize = newSize;

    // Reinitialize array with new size
    initializeArray();

    // Reset algorithm with new array
    resetAlgorithm();
}

void SortingVisualizer::update()
{
    InputHandler::Action action = inputHandler.handleInput(window);

    switch (action)
    {
    case InputHandler::TOGGLE_PAUSE:
        if (comparisonModeActive)
        {
            comparisonMode.togglePause();
        }
        else
        {
            isPaused = !isPaused;
            ui.updateInstructions(isPaused);
        }
        break;

    case InputHandler::STEP_FORWARD:
        stepForward();
        break;

    case InputHandler::STEP_BACKWARD:
        stepBackward();
        break;

    case InputHandler::RESET:
        if (comparisonModeActive)
        {
            comparisonMode.reset();
        }
        else
        {
            randomizeArray();
            for (int i = 0; i < arraySize; i++)
            {
                originalArray[i] = array[i];
            }
            resetAlgorithm();
        }
        break;

    case InputHandler::NEXT_ALGORITHM:
        nextAlgorithm();
        break;

    case InputHandler::INCREASE_SIZE:
        increaseArraySize();
        break;

    case InputHandler::DECREASE_SIZE:
        decreaseArraySize();
        break;

    case InputHandler::SELECT_ALGORITHM_1:
        selectAlgorithm(0);
        break;

    case InputHandler::SELECT_ALGORITHM_2:
        selectAlgorithm(1);
        break;

    case InputHandler::SELECT_ALGORITHM_3:
        selectAlgorithm(2);
        break;

    case InputHandler::SELECT_ALGORITHM_4:
        selectAlgorithm(3);
        break;

    case InputHandler::SELECT_ALGORITHM_5:
        selectAlgorithm(4);
        break;
    case InputHandler::SELECT_ALGORITHM_6:
        selectAlgorithm(5);
        break;
    case InputHandler::SELECT_ALGORITHM_7:
        selectAlgorithm(6);
        break;
    case InputHandler::SELECT_ALGORITHM_8:
        selectAlgorithm(7);
        break;
    case InputHandler::SELECT_ALGORITHM_9:
        selectAlgorithm(8);
        break;
    case InputHandler::SELECT_ALGORITHM_10:
        selectAlgorithm(9);
        break;

    case InputHandler::TOGGLE_COMPARISON_MODE:
        comparisonModeActive = !comparisonModeActive;
        if (comparisonModeActive)
        {
            comparisonMode.reset();
        }
        break;

    case InputHandler::COMPARISON_STEP_FORWARD:
        if (comparisonModeActive)
        {
            comparisonMode.stepForward();
        }
        break;

    case InputHandler::COMPARISON_RESET:
        if (comparisonModeActive)
        {
            comparisonMode.reset();
        }
        break;

    case InputHandler::QUIT:
        window.close();
        break;

    default:
        break;
    }

    // Auto-step if not paused and frame time has elapsed
    if (frameClock.getElapsedTime().asSeconds() >= FRAME_DURATION)
    {
        if (comparisonModeActive)
        {
            if (!comparisonMode.isPausedState() && !comparisonMode.isComplete())
            {
                comparisonMode.stepForward();
            }
        }
        else if (!isPaused && !sortingComplete)
        {
            stepForward();
        }
        frameClock.restart();
    }
}

void SortingVisualizer::render()
{
    window.clear(sf::Color::Black);

    if (comparisonModeActive)
    {
        // Render comparison mode
        comparisonMode.render(window);
    }
    else
    {
        // Update and render bars
        barRenderer.updateBars(array, arraySize, highlightIndex1, highlightIndex2);
        barRenderer.render(window);

        // Render UI
        ui.render(window);
    }

    window.display();
}

void SortingVisualizer::updateAlgorithmInfo()
{
    if (!currentAlgorithm)
        return;

    const char* best = "O(n)";
    const char* avg = "O(n²)";
    const char* worst = "O(n²)";
    const char* description = "Basic comparison sort";

    // Set algorithm-specific information
    if (strcmp(currentAlgorithm->name, "Bubble Sort") == 0)
    {
        best = "O(n)";
        avg = "O(n²)";
        worst = "O(n²)";
        description = "Compares adjacent elements and swaps if in wrong order";
    }
    else if (strcmp(currentAlgorithm->name, "Selection Sort") == 0)
    {
        best = "O(n²)";
        avg = "O(n²)";
        worst = "O(n²)";
        description = "Finds minimum element and places at beginning";
    }
    else if (strcmp(currentAlgorithm->name, "Shell Sort") == 0)
    {
        best = "O(n log n)";
        avg = "O(n^1.5)";
        worst = "O(n²)";
        description = "Improved insertion sort with gap sequences";
    }
    else if (strcmp(currentAlgorithm->name, "Merge Sort") == 0)
    {
        best = "O(n log n)";
        avg = "O(n log n)";
        worst = "O(n log n)";
        description = "Divide and conquer with stable sorting";
    }
    else if (strcmp(currentAlgorithm->name, "Quick Sort") == 0)
    {
        best = "O(n log n)";
        avg = "O(n log n)";
        worst = "O(n²)";
        description = "Divide and conquer with pivot selection";
    }
    else if (strcmp(currentAlgorithm->name, "Radix Sort") == 0)
    {
        best = "O(nk)";
        avg = "O(nk)";
        worst = "O(nk)";
        description = "Non-comparison sort using digit distribution";
    }

    ui.updateComplexityInfo(best, avg, worst);
    ui.updateAlgorithmDescription(description);
}

void SortingVisualizer::updateArrayStats()
{
    if (arraySize <= 0)
        return;

    int min = array[0];
    int max = array[0];
    int sum = array[0];

    for (int i = 1; i < arraySize; i++)
    {
        if (array[i] < min) min = array[i];
        if (array[i] > max) max = array[i];
        sum += array[i];
    }

    // Calculate median (simplified - just middle element for odd size)
    int median = array[arraySize / 2];

    ui.updateArrayStats(min, max, median);
}

void SortingVisualizer::run()
{
    while (window.isOpen())
    {
        update();
        render();
    }
}
