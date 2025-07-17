#include "simple_ui.h"
#include <sstream>
#include <iostream>

bool SimpleUI::initialize()
{
    // Don't worry about loading custom fonts - SFML has a default font
    // Just set up the text objects

    // Setup algorithm name text
    algorithmName.setCharacterSize(24);
    algorithmName.setFillColor(sf::Color::White);
    algorithmName.setPosition(20, 20);

    // Setup instructions text
    instructions.setCharacterSize(16);
    instructions.setFillColor(sf::Color::Yellow);
    instructions.setPosition(20, 60);

    // Setup array display text
    arrayDisplay.setCharacterSize(14);
    arrayDisplay.setFillColor(sf::Color::Cyan);
    arrayDisplay.setPosition(20, 100);

    // Setup step info text
    stepInfo.setCharacterSize(14);
    stepInfo.setFillColor(sf::Color::Green);
    stepInfo.setPosition(20, 120);

    return true;
}

void SimpleUI::updateAlgorithmName(const char *name)
{
    algorithmName.setString(std::string("Algorithm: ") + name);
}

void SimpleUI::updateInstructions(bool paused)
{
    if (paused)
    {
        instructions.setString("PAUSED - Press SPACE to resume | LEFT/RIGHT arrows to step | R to reset | TAB to change algorithm");
    }
    else
    {
        instructions.setString("RUNNING - Press SPACE to pause | R to reset | TAB to change algorithm");
    }
}

void SimpleUI::updateArrayDisplay(int array[], int size)
{
    std::ostringstream oss;
    oss << "Array: [";
    for (int i = 0; i < size; i++)
    {
        oss << array[i];
        if (i < size - 1)
            oss << ", ";
    }
    oss << "]";
    arrayDisplay.setString(oss.str());
}

void SimpleUI::updateStepInfo(int step, bool complete)
{
    std::ostringstream oss;
    if (complete)
    {
        oss << "Sorting Complete! Steps taken: " << step;
    }
    else
    {
        oss << "Step: " << step;
    }
    stepInfo.setString(oss.str());
}

void SimpleUI::render(sf::RenderWindow &window)
{
    window.draw(algorithmName);
    window.draw(instructions);
    window.draw(arrayDisplay);
    window.draw(stepInfo);
}
