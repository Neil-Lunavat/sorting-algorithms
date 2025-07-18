#include "bar_renderer.h"
#include <algorithm>

BarRenderer::BarRenderer()
{
    currentArraySize = 7; // Default size
    barWidth = WINDOW_WIDTH / currentArraySize;
    maxBarHeight = BAR_AREA_HEIGHT - 20;

    // Set default colors
    normalColor = sf::Color(100, 150, 255);  // Light blue
    swapColor = sf::Color(255, 100, 100);    // Red
    compareColor = sf::Color(255, 255, 100); // Yellow

    // Initialize bars
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        bars[i].setFillColor(normalColor);
        bars[i].setOutlineColor(sf::Color::White);
        bars[i].setOutlineThickness(1);
    }
}

void BarRenderer::updateBars(int array[], int size, int highlight1, int highlight2)
{
    // Update array size if it changed
    if (size != currentArraySize)
    {
        currentArraySize = size;
        barWidth = WINDOW_WIDTH / currentArraySize;
        if (barWidth < 2)
            barWidth = 2; // Minimum width
    }

    // Find max value for scaling
    int maxValue = *std::max_element(array, array + size);
    if (maxValue == 0)
        maxValue = 1; // Avoid division by zero

    for (int i = 0; i < size && i < MAX_ARRAY_SIZE; i++)
    {
        // Calculate bar height proportional to value
        int barHeight = (array[i] * maxBarHeight) / maxValue;
        if (barHeight < 10)
            barHeight = 10; // Minimum height for visibility

        // Set bar size and position
        int actualBarWidth = barWidth - 2;
        if (actualBarWidth < 1)
            actualBarWidth = 1;

        bars[i].setSize(sf::Vector2f(actualBarWidth, barHeight));
        bars[i].setPosition(i * barWidth + 1, BAR_Y_OFFSET + maxBarHeight - barHeight);

        // Set color based on highlighting
        if (i == highlight1 || i == highlight2)
        {
            bars[i].setFillColor(swapColor);
        }
        else
        {
            bars[i].setFillColor(normalColor);
        }
    }
}

void BarRenderer::render(sf::RenderWindow &window)
{
    for (int i = 0; i < currentArraySize && i < MAX_ARRAY_SIZE; i++)
    {
        window.draw(bars[i]);
    }
}

void BarRenderer::setColors(sf::Color normal, sf::Color swap, sf::Color compare)
{
    normalColor = normal;
    swapColor = swap;
    compareColor = compare;
}
