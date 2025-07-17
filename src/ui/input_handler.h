#pragma once
#include <SFML/Graphics.hpp>

/**
 * Handles user input for the sorting visualizer
 */
class InputHandler {
public:
    enum Action {
        NONE,
        STEP_FORWARD,
        STEP_BACKWARD,
        TOGGLE_PAUSE,
        RESET,
        NEXT_ALGORITHM,
        QUIT
    };
    
    Action handleInput(sf::RenderWindow& window);
    bool isKeyPressed(sf::Keyboard::Key key);
    
private:
    sf::Clock keyRepeatClock;
    static const float KEY_REPEAT_DELAY;
};
