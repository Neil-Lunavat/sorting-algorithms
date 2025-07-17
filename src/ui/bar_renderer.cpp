#include "bar_renderer.h"
#include <algorithm>

BarRenderer::BarRenderer() {
    barWidth = WINDOW_WIDTH / ARRAY_SIZE;
    maxBarHeight = BAR_AREA_HEIGHT - 20;
    
    // Set default colors
    normalColor = sf::Color(100, 150, 255);     // Light blue
    swapColor = sf::Color(255, 100, 100);       // Red
    compareColor = sf::Color(255, 255, 100);    // Yellow
    
    // Initialize bars
    for (int i = 0; i < ARRAY_SIZE; i++) {
        bars[i].setFillColor(normalColor);
        bars[i].setOutlineColor(sf::Color::White);
        bars[i].setOutlineThickness(2);
    }
}

void BarRenderer::updateBars(int array[], int size, int highlight1, int highlight2) {
    // Find max value for scaling
    int maxValue = *std::max_element(array, array + size);
    if (maxValue == 0) maxValue = 1;  // Avoid division by zero
    
    for (int i = 0; i < size && i < ARRAY_SIZE; i++) {
        // Calculate bar height proportional to value
        int barHeight = (array[i] * maxBarHeight) / maxValue;
        if (barHeight < 10) barHeight = 10;  // Minimum height for visibility
        
        // Set bar size and position
        bars[i].setSize(sf::Vector2f(barWidth - 4, barHeight));
        bars[i].setPosition(i * barWidth + 2, BAR_Y_OFFSET + maxBarHeight - barHeight);
        
        // Set color based on highlighting
        if (i == highlight1 || i == highlight2) {
            bars[i].setFillColor(swapColor);
        } else {
            bars[i].setFillColor(normalColor);
        }
    }
}

void BarRenderer::render(sf::RenderWindow& window) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        window.draw(bars[i]);
    }
}

void BarRenderer::setColors(sf::Color normal, sf::Color swap, sf::Color compare) {
    normalColor = normal;
    swapColor = swap;
    compareColor = compare;
}
