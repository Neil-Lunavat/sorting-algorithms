#include <SFML/Graphics.hpp>
#include "visualizer.h"
#include "../algorithms/register_algorithms.h"

int main()
{
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;

    // Register all algorithms
    registerAllAlgorithms();

    // Create window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "Sorting Algorithm Visualizer - Educational Version");
    window.setFramerateLimit(60);

    // Create visualizer
    SortingVisualizer visualizer(window);

    // Initialize
    if (!visualizer.initialize())
    {
        return -1;
    }

    // Run visualizer
    visualizer.run();

    return 0;
}
