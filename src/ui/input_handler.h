#pragma once
#include <SFML/Graphics.hpp>

/**
 * Handles user input for the sorting visualizer
 */
class InputHandler
{
public:
    enum Action
    {
        NONE,
        STEP_FORWARD,
        STEP_BACKWARD,
        TOGGLE_PAUSE,
        RESET,
        NEXT_ALGORITHM,
        INCREASE_SIZE,
        DECREASE_SIZE,
        SELECT_ALGORITHM_1,
        SELECT_ALGORITHM_2,
        SELECT_ALGORITHM_3,
        SELECT_ALGORITHM_4,
        SELECT_ALGORITHM_5,
        SELECT_ALGORITHM_6,
        SELECT_ALGORITHM_7,
        SELECT_ALGORITHM_8,
        SELECT_ALGORITHM_9,
        SELECT_ALGORITHM_10,
        TOGGLE_COMPARISON_MODE,
        COMPARISON_STEP_FORWARD,
        COMPARISON_RESET,
        QUIT
    };

    Action handleInput(sf::RenderWindow &window);
    bool isKeyPressed(sf::Keyboard::Key key);

private:
    sf::Clock keyRepeatClock;
    static const float KEY_REPEAT_DELAY;
};
