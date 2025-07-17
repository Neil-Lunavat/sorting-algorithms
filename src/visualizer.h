#pragma once
#include <SFML/Graphics.hpp>
#include "../algorithms/algorithm_interface.h"
#include "ui/simple_ui.h"
#include "ui/bar_renderer.h"
#include "ui/input_handler.h"

/**
 * Main sorting visualizer class
 * Manages the overall application state and coordinates between components
 */
class SortingVisualizer {
private:
    static const int ARRAY_SIZE = 7;
    static const int MAX_STATE_SIZE = 10;
    
    // Core data
    int array[ARRAY_SIZE];
    int originalArray[ARRAY_SIZE];  // For reset functionality
    int algorithmState[MAX_STATE_SIZE];
    
    // Current algorithm
    AlgorithmInfo* currentAlgorithm;
    int currentAlgorithmIndex;
    
    // Visualization state
    bool isPaused;
    int stepCount;
    int highlightIndex1, highlightIndex2;
    bool sortingComplete;
    
    // Frame timing
    sf::Clock frameClock;
    static const float FRAME_DURATION;  // 1/60 second
    
    // UI Components
    SimpleUI ui;
    BarRenderer barRenderer;
    InputHandler inputHandler;
    
    // Window
    sf::RenderWindow& window;
    
public:
    SortingVisualizer(sf::RenderWindow& win);
    bool initialize();
    void run();
    
private:
    void initializeArray();
    void resetAlgorithm();
    void stepForward();
    void stepBackward();  // For future implementation
    void nextAlgorithm();
    void update();
    void render();
    void randomizeArray();
};
