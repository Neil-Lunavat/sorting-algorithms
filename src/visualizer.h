#pragma once
#include <SFML/Graphics.hpp>
#include "../algorithms/algorithm_interface.h"
#include "ui/simple_ui.h"
#include "ui/bar_renderer.h"
#include "ui/input_handler.h"
#include "ui/algorithm_comparison.h"

/**
 * Main sorting visualizer class
 * Manages the overall application state and coordinates between components
 */
class SortingVisualizer
{
private:
    static const int MIN_ARRAY_SIZE = 3;
    static const int MAX_ARRAY_SIZE = 50;
    static const int MAX_STATE_SIZE = 20;

    // Window reference (needs to be first for initialization order)
    sf::RenderWindow &window;

    // Core data - now dynamic
    int *array;
    int *originalArray;
    int arraySize;
    int algorithmState[MAX_STATE_SIZE];

    // Current algorithm
    AlgorithmInfo *currentAlgorithm;
    int currentAlgorithmIndex;

    // Visualization state
    bool isPaused;
    int stepCount;
    int swapCount;
    int highlightIndex1, highlightIndex2;
    bool sortingComplete;
    bool comparisonModeActive;

    // Frame timing
    sf::Clock frameClock;
    static const float FRAME_DURATION; // 1/60 second

    // UI Components
    SimpleUI ui;
    BarRenderer barRenderer;
    InputHandler inputHandler;
    AlgorithmComparison comparisonMode;

public:
    SortingVisualizer(sf::RenderWindow &win);
    ~SortingVisualizer(); // Destructor to clean up dynamic arrays
    bool initialize();
    void run();

private:
    void initializeArray();
    void resetAlgorithm();
    void stepForward();
    void stepBackward(); // For future implementation
    void nextAlgorithm();
    void selectAlgorithm(int algorithmIndex);
    void increaseArraySize();
    void decreaseArraySize();
    void resizeArray(int newSize);
    void update();
    void render();
    void randomizeArray();
    
private:
    void updateAlgorithmInfo();
    void updateArrayStats();
};
