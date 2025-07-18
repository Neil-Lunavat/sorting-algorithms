#include <SFML/Graphics.hpp>
#include <iostream>
#include "visualizer.h"
#include "../algorithms/register_algorithms.h"

int main()
{
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

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
        std::cerr << "Failed to initialize visualizer!" << std::endl;
        return -1;
    }

    std::cout << "Sorting Algorithm Visualizer Started!" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  SPACE - Pause/Resume" << std::endl;
    std::cout << "  LEFT/RIGHT - Step through algorithm" << std::endl;
    std::cout << "  R - Reset and randomize array" << std::endl;
    std::cout << "  TAB - Change algorithm" << std::endl;
    std::cout << "  +/- - Increase/Decrease array size" << std::endl;
    std::cout << "  1-5 - Select algorithm directly" << std::endl;
    std::cout << "  ESC - Quit" << std::endl;

    // Run visualizer
    visualizer.run();

    return 0;
}
