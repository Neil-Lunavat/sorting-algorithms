#pragma once
#include <SFML/Graphics.hpp>

/**
 * Simple UI manager for displaying text and instructions
 */
class SimpleUI {
private:
    sf::Font font;
    sf::Text algorithmName;
    sf::Text instructions;
    sf::Text arrayDisplay;
    sf::Text stepInfo;
    
public:
    bool initialize();
    void updateAlgorithmName(const char* name);
    void updateInstructions(bool paused);
    void updateArrayDisplay(int array[], int size);
    void updateStepInfo(int step, bool complete);
    void render(sf::RenderWindow& window);
};
