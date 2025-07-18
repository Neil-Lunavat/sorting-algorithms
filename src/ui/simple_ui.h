#pragma once
#include <SFML/Graphics.hpp>

/**
 * Simple UI manager for displaying text and instructions
 */
class SimpleUI
{
private:
    sf::Font font;
    sf::Text algorithmName;
    sf::Text instructions;
    sf::Text arrayDisplay;
    sf::Text stepInfo;
    sf::Text swapInfo;
    sf::Text arraySize;
    sf::Text complexityInfo;
    sf::Text algorithmDescription;
    sf::Text arrayStats;
    bool fontLoaded;

public:
    bool initialize();
    void updateAlgorithmName(const char *name);
    void updateInstructions(bool paused);
    void updateArrayDisplay(int array[], int size);
    void updateStepInfo(int step, bool complete);
    void updateSwapInfo(int swaps);
    void updateArraySize(int size);
    void updateComplexityInfo(const char* best, const char* avg, const char* worst);
    void updateAlgorithmDescription(const char* description);
    void updateArrayStats(int min, int max, int median);
    void render(sf::RenderWindow &window);
};
