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
