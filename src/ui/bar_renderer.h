#pragma once
#include <SFML/Graphics.hpp>

/**
 * Renders the array as bars with visual highlighting
 */
class BarRenderer
{
private:
    static const int MAX_ARRAY_SIZE = 50;
    static const int WINDOW_WIDTH = 1280;
    static const int WINDOW_HEIGHT = 720;
    static const int BAR_AREA_HEIGHT = 400;
    static const int BAR_Y_OFFSET = 300;

    sf::RectangleShape bars[MAX_ARRAY_SIZE];
    sf::Color normalColor;
    sf::Color swapColor;
    sf::Color compareColor;

    int currentArraySize;
    int barWidth;
    int maxBarHeight;

public:
    BarRenderer();
    void updateBars(int array[], int size, int highlight1 = -1, int highlight2 = -1);
    void render(sf::RenderWindow &window);
    void setColors(sf::Color normal, sf::Color swap, sf::Color compare);
};
