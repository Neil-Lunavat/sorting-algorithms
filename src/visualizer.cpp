#include "visualizer.h"
#include "../algorithms/algorithm_registry.h"
#include <random>
#include <algorithm>
#include <cstring>
#include <iostream>

const float SortingVisualizer::FRAME_DURATION = 1.0f / 60.0f;

SortingVisualizer::SortingVisualizer(sf::RenderWindow &win)
    : window(win), array(nullptr), originalArray(nullptr), arraySize(7),
      currentAlgorithm(nullptr), currentAlgorithmIndex(0),
      isPaused(true), stepCount(0), swapCount(0), highlightIndex1(-1), highlightIndex2(-1),
      sortingComplete(false)
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

    // Check if algorithms are registered
    int algorithmCount = getAlgorithmCount();
    std::cout << "Found " << algorithmCount << " algorithms registered." << std::endl;

    if (algorithmCount > 0)
    {
        currentAlgorithm = getAlgorithmByIndex(0);
        if (currentAlgorithm)
        {
            std::cout << "Using algorithm: " << currentAlgorithm->name << std::endl;
            resetAlgorithm();
        }
        else
        {
            std::cout << "Error: Failed to get algorithm by index 0" << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "Error: No algorithms registered!" << std::endl;
        std::cout << "Make sure algorithm files are compiled and linked." << std::endl;
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
        isPaused = !isPaused;
        ui.updateInstructions(isPaused);
        break;

    case InputHandler::STEP_FORWARD:
        stepForward();
        break;

    case InputHandler::STEP_BACKWARD:
        stepBackward();
        break;

    case InputHandler::RESET:
        randomizeArray();
        for (int i = 0; i < arraySize; i++)
        {
            originalArray[i] = array[i];
        }
        resetAlgorithm();
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

    case InputHandler::QUIT:
        window.close();
        break;

    default:
        break;
    }

    // Auto-step if not paused and frame time has elapsed
    if (!isPaused && !sortingComplete && frameClock.getElapsedTime().asSeconds() >= FRAME_DURATION)
    {
        stepForward();
        frameClock.restart();
    }
}

void SortingVisualizer::render()
{
    window.clear(sf::Color::Black);

    // Update and render bars
    barRenderer.updateBars(array, arraySize, highlightIndex1, highlightIndex2);
    barRenderer.render(window);

    // Render UI
    ui.render(window);

    window.display();
}

void SortingVisualizer::run()
{
    while (window.isOpen())
    {
        update();
        render();
    }
}
