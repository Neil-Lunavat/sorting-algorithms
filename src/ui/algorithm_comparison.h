#pragma once
#include <SFML/Graphics.hpp>
#include "../../algorithms/algorithm_interface.h"
#include <vector>

/**
 * Algorithm comparison mode for side-by-side visualization
 */
class AlgorithmComparison
{
private:
    static const int MAX_ALGORITHMS = 4;
    static const int COMPARISON_ARRAY_SIZE = 20;
    
    struct ComparisonAlgorithm
    {
        AlgorithmInfo* algorithm;
        int* array;
        int* originalArray;
        int state[20];
        int stepCount;
        int swapCount;
        bool isComplete;
        sf::Color color;
    };

    std::vector<ComparisonAlgorithm> algorithms;
    bool isActive;
    int currentStep;
    bool isPaused;

public:
    AlgorithmComparison();
    ~AlgorithmComparison();
    
    bool initialize();
    void addAlgorithm(AlgorithmInfo* algorithm, sf::Color color);
    void reset();
    void stepForward();
    void togglePause() { isPaused = !isPaused; }
    bool isRunning() const { return !isPaused; }
    bool isPausedState() const { return isPaused; }
    bool isComplete() const;
    void render(sf::RenderWindow& window);
    
private:
    void initializeArrays();
    void randomizeArrays();
}; 