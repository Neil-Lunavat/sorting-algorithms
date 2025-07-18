#include "simple_ui.h"
#include <sstream>
#include <iostream>

bool SimpleUI::initialize()
{
    fontLoaded = false;

    // Try to load a system font
    if (font.loadFromFile("C:/Windows/Fonts/arial.ttf") ||
        font.loadFromFile("C:/Windows/Fonts/calibri.ttf") ||
        font.loadFromFile("C:/Windows/Fonts/verdana.ttf"))
    {
        fontLoaded = true;
    }
    else
    {
        // If no font loads, we'll use SFML's default font (which should work)
    }

    // Setup algorithm name text
    algorithmName.setCharacterSize(24);
    algorithmName.setFillColor(sf::Color::White);
    algorithmName.setPosition(20, 20);
    if (fontLoaded)
        algorithmName.setFont(font);

    // Setup instructions text
    instructions.setCharacterSize(16);
    instructions.setFillColor(sf::Color::Yellow);
    instructions.setPosition(20, 60);
    if (fontLoaded)
        instructions.setFont(font);

    // Setup array display text
    arrayDisplay.setCharacterSize(14);
    arrayDisplay.setFillColor(sf::Color::Cyan);
    arrayDisplay.setPosition(20, 100);
    if (fontLoaded)
        arrayDisplay.setFont(font);

    // Setup step info text
    stepInfo.setCharacterSize(14);
    stepInfo.setFillColor(sf::Color::Green);
    stepInfo.setPosition(20, 120);
    if (fontLoaded)
        stepInfo.setFont(font);

    // Setup swap info text
    swapInfo.setCharacterSize(18);
    swapInfo.setFillColor(sf::Color::Red);
    swapInfo.setPosition(20, 140);
    if (fontLoaded)
        swapInfo.setFont(font);

    // Setup array size text
    arraySize.setCharacterSize(16);
    arraySize.setFillColor(sf::Color::Magenta);
    arraySize.setPosition(20, 165);
    if (fontLoaded)
        arraySize.setFont(font);

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
        instructions.setString("PAUSED - SPACE: resume | LEFT/RIGHT: step | R: reset | TAB: next algo | +/-: size | 1-4: select algo");
    }
    else
    {
        instructions.setString("RUNNING - SPACE: pause | R: reset | TAB: next algo | +/-: size | 1-4: select algo");
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

void SimpleUI::updateSwapInfo(int swaps)
{
    std::ostringstream oss;
    oss << "Swaps: " << swaps;
    swapInfo.setString(oss.str());
}

void SimpleUI::updateArraySize(int size)
{
    std::ostringstream oss;
    oss << "Array Size: " << size;
    arraySize.setString(oss.str());
}

void SimpleUI::render(sf::RenderWindow &window)
{
    window.draw(algorithmName);
    window.draw(instructions);
    window.draw(arrayDisplay);
    window.draw(stepInfo);
    window.draw(swapInfo);
    window.draw(arraySize);
}
