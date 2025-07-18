#include "input_handler.h"

const float InputHandler::KEY_REPEAT_DELAY = 0.2f;

InputHandler::Action InputHandler::handleInput(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            return QUIT;
        }

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Space:
                return TOGGLE_PAUSE;
            case sf::Keyboard::Right:
                return STEP_FORWARD;
            case sf::Keyboard::Left:
                return STEP_BACKWARD;
            case sf::Keyboard::R:
                return RESET;
            case sf::Keyboard::Tab:
                return NEXT_ALGORITHM;
            case sf::Keyboard::Equal: // Plus key (=)
            case sf::Keyboard::Add:   // Numpad plus
                return INCREASE_SIZE;
            case sf::Keyboard::Hyphen:   // Minus key (-)
            case sf::Keyboard::Subtract: // Numpad minus
                return DECREASE_SIZE;
            case sf::Keyboard::Num1:
                return SELECT_ALGORITHM_1;
            case sf::Keyboard::Num2:
                return SELECT_ALGORITHM_2;
            case sf::Keyboard::Num3:
                return SELECT_ALGORITHM_3;
            case sf::Keyboard::Num4:
                return SELECT_ALGORITHM_4;
            case sf::Keyboard::Num5:
                return SELECT_ALGORITHM_5;
            case sf::Keyboard::Escape:
                return QUIT;
            default:
                break;
            }
        }
    }

    return NONE;
}

bool InputHandler::isKeyPressed(sf::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed(key);
}
