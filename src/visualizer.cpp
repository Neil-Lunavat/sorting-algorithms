#include "visualizer.h"
#include "../algorithms/algorithm_registry.h"
#include <random>
#include <algorithm>
#include <cstring>

const float SortingVisualizer::FRAME_DURATION = 1.0f / 60.0f;

SortingVisualizer::SortingVisualizer(sf::RenderWindow& win) 
    : window(win), isPaused(true), stepCount(0), highlightIndex1(-1), highlightIndex2(-1), 
      sortingComplete(false), currentAlgorithm(nullptr), currentAlgorithmIndex(0) {
    
    // Initialize array with simple values
    initializeArray();
}

bool SortingVisualizer::initialize() {
    // Initialize UI
    if (!ui.initialize()) {
        return false;
    }
    
    // Get first algorithm
    if (getAlgorithmCount() > 0) {
        currentAlgorithm = getAlgorithmByIndex(0);
        resetAlgorithm();
    } else {
        return false;  // No algorithms registered
    }
    
    return true;
}

void SortingVisualizer::initializeArray() {
    // Create a simple array with values 1 to ARRAY_SIZE
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;
    }
    
    // Shuffle the array
    randomizeArray();
    
    // Save original for reset
    std::memcpy(originalArray, array, sizeof(array));
}

void SortingVisualizer::randomizeArray() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(array, array + ARRAY_SIZE, gen);
}

void SortingVisualizer::resetAlgorithm() {
    if (!currentAlgorithm) return;
    
    // Reset array to original state
    std::memcpy(array, originalArray, sizeof(array));
    
    // Clear algorithm state
    std::memset(algorithmState, 0, sizeof(algorithmState));
    
    // Reset visualization state
    stepCount = 0;
    highlightIndex1 = -1;
    highlightIndex2 = -1;
    sortingComplete = false;
    
    // Update UI
    ui.updateAlgorithmName(currentAlgorithm->name);
    ui.updateInstructions(isPaused);
    ui.updateArrayDisplay(array, ARRAY_SIZE);
    ui.updateStepInfo(stepCount, sortingComplete);
}

void SortingVisualizer::stepForward() {
    if (!currentAlgorithm || sortingComplete) return;
    
    SwapResult result = currentAlgorithm->function(array, ARRAY_SIZE, algorithmState);
    
    if (result.swapped) {
        highlightIndex1 = result.index1;
        highlightIndex2 = result.index2;
        stepCount++;
    } else {
        highlightIndex1 = -1;
        highlightIndex2 = -1;
    }
    
    sortingComplete = result.isComplete;
    
    // Update UI
    ui.updateArrayDisplay(array, ARRAY_SIZE);
    ui.updateStepInfo(stepCount, sortingComplete);
}

void SortingVisualizer::stepBackward() {
    // TODO: Implement step backward functionality
    // This would require storing history of array states
}

void SortingVisualizer::nextAlgorithm() {
    int algorithmCount = getAlgorithmCount();
    if (algorithmCount <= 1) return;
    
    currentAlgorithmIndex = (currentAlgorithmIndex + 1) % algorithmCount;
    currentAlgorithm = getAlgorithmByIndex(currentAlgorithmIndex);
    resetAlgorithm();
}

void SortingVisualizer::update() {
    InputHandler::Action action = inputHandler.handleInput(window);
    
    switch (action) {
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
            std::memcpy(originalArray, array, sizeof(array));
            resetAlgorithm();
            break;
            
        case InputHandler::NEXT_ALGORITHM:
            nextAlgorithm();
            break;
            
        case InputHandler::QUIT:
            window.close();
            break;
            
        default:
            break;
    }
    
    // Auto-step if not paused and frame time has elapsed
    if (!isPaused && !sortingComplete && frameClock.getElapsedTime().asSeconds() >= FRAME_DURATION) {
        stepForward();
        frameClock.restart();
    }
}

void SortingVisualizer::render() {
    window.clear(sf::Color::Black);
    
    // Update and render bars
    barRenderer.updateBars(array, ARRAY_SIZE, highlightIndex1, highlightIndex2);
    barRenderer.render(window);
    
    // Render UI
    ui.render(window);
    
    window.display();
}

void SortingVisualizer::run() {
    while (window.isOpen()) {
        update();
        render();
    }
}
