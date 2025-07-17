#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include "sorting_algorithms.h"

class SortingVisualizer
{
private:
    static const int ARRAY_SIZE = 100;
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
    static const int BAR_WIDTH = WINDOW_WIDTH / ARRAY_SIZE;
    static const int MAX_BAR_HEIGHT = 400;

    std::vector<int> array;
    std::vector<sf::RectangleShape> bars;
    std::unique_ptr<SortingAlgorithm> currentSorter;
    SortState sortState;

    sf::RenderWindow &window;
    sf::Font font;
    sf::Text titleText;
    sf::Text instructionsText;
    sf::Text statusText;

    bool isSorting;
    int currentAlgorithm;
    std::vector<std::unique_ptr<SortingAlgorithm>> algorithms;

    // Timing for animation
    sf::Clock sortClock;
    float sortDelay;       // Delay between sorting steps in seconds
    int speedMultiplier;   // Number of steps to perform per frame
    int maxSpeedLevel;     // Maximum speed level
    int currentSpeedLevel; // Current speed setting (1 = slowest, maxSpeedLevel = fastest)

public:
    SortingVisualizer(sf::RenderWindow &win) : window(win), isSorting(false), currentAlgorithm(0),
                                               sortDelay(0.02f), speedMultiplier(1), maxSpeedLevel(5), currentSpeedLevel(3)
    {
        initializeArray();
        initializeAlgorithms();
        setupText();
        createBars();
        updateSpeed(); // Initialize speed settings
    }

    void initializeArray()
    {
        array.resize(ARRAY_SIZE);

        // Generate random heights
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(10, MAX_BAR_HEIGHT);

        for (int i = 0; i < ARRAY_SIZE; ++i)
        {
            array[i] = dis(gen);
        }
    }

    void initializeAlgorithms()
    {
        algorithms.push_back(std::make_unique<BubbleSort>());
        algorithms.push_back(std::make_unique<SelectionSort>());
        algorithms.push_back(std::make_unique<InsertionSort>());

        currentSorter = std::make_unique<BubbleSort>();
    }

    void setupText()
    {
        // Set up title text
        titleText.setString("Sorting Algorithm Visualizer");
        titleText.setCharacterSize(24);
        titleText.setFillColor(sf::Color::White);
        titleText.setPosition(250.f, 10.f);

        // Set up instructions
        instructionsText.setString("SPACE=Start/Stop | R=Randomize | 1/2/3=Algorithm | +/-=Speed | ESC=Exit");
        instructionsText.setCharacterSize(16);
        instructionsText.setFillColor(sf::Color::Yellow);
        instructionsText.setPosition(10.f, 40.f);

        // Set up status text
        statusText.setCharacterSize(18);
        statusText.setFillColor(sf::Color::Green);
        statusText.setPosition(10.f, 70.f);
        updateStatusText();
    }

    void createBars()
    {
        bars.clear();
        bars.resize(ARRAY_SIZE);

        for (int i = 0; i < ARRAY_SIZE; ++i)
        {
            bars[i].setSize(sf::Vector2f(BAR_WIDTH - 1, array[i]));
            bars[i].setPosition(i * BAR_WIDTH, WINDOW_HEIGHT - array[i] - 100);
            bars[i].setFillColor(sf::Color::Cyan);
        }
    }

    void updateStatusText()
    {
        std::string status = "Algorithm: ";
        status += currentSorter->getName();
        status += " | Speed: " + std::to_string(currentSpeedLevel) + "/" + std::to_string(maxSpeedLevel);
        if (isSorting)
        {
            status += " | Status: Sorting...";
        }
        else if (sortState.isComplete)
        {
            status += " | Status: Complete!";
        }
        else
        {
            status += " | Status: Ready";
        }
        statusText.setString(status);
    }

    void updateSpeed()
    {
        // Calculate delay and multiplier based on speed level
        switch (currentSpeedLevel)
        {
        case 1:
            sortDelay = 0.1f;
            speedMultiplier = 1;
            break; // Very Slow
        case 2:
            sortDelay = 0.05f;
            speedMultiplier = 1;
            break; // Slow
        case 3:
            sortDelay = 0.02f;
            speedMultiplier = 1;
            break; // Normal
        case 4:
            sortDelay = 0.01f;
            speedMultiplier = 2;
            break; // Fast
        case 5:
            sortDelay = 0.005f;
            speedMultiplier = 3;
            break; // Very Fast
        }
    }

    void increaseSpeed()
    {
        if (currentSpeedLevel < maxSpeedLevel)
        {
            currentSpeedLevel++;
            updateSpeed();
            std::cout << "Speed increased to level " << currentSpeedLevel << std::endl;
        }
    }

    void decreaseSpeed()
    {
        if (currentSpeedLevel > 1)
        {
            currentSpeedLevel--;
            updateSpeed();
            std::cout << "Speed decreased to level " << currentSpeedLevel << std::endl;
        }
    }

    void handleEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;

                case sf::Keyboard::Space:
                    if (!isSorting && !sortState.isComplete)
                    {
                        startSorting();
                    }
                    else if (isSorting)
                    {
                        stopSorting();
                    }
                    else if (sortState.isComplete)
                    {
                        randomizeArray();
                    }
                    break;

                case sf::Keyboard::R:
                    randomizeArray();
                    break;

                case sf::Keyboard::Num1:
                    changeAlgorithm(0);
                    break;

                case sf::Keyboard::Num2:
                    changeAlgorithm(1);
                    break;

                case sf::Keyboard::Num3:
                    changeAlgorithm(2);
                    break;

                case sf::Keyboard::Equal: // Plus key (=+)
                case sf::Keyboard::Add:   // Numpad +
                    increaseSpeed();
                    break;

                case sf::Keyboard::Hyphen:   // Minus key
                case sf::Keyboard::Subtract: // Numpad -
                    decreaseSpeed();
                    break;
                }
            }
        }
    }

    void startSorting()
    {
        if (!sortState.isComplete)
        {
            isSorting = true;
            sortClock.restart();
            std::cout << "Started sorting with " << currentSorter->getName() << std::endl;
        }
    }

    void stopSorting()
    {
        isSorting = false;
        std::cout << "Sorting paused" << std::endl;
    }

    void randomizeArray()
    {
        isSorting = false;
        initializeArray();
        createBars();
        currentSorter->reset(sortState);
        std::cout << "Array randomized" << std::endl;
    }

    void changeAlgorithm(int algorithmIndex)
    {
        if (algorithmIndex >= 0 && algorithmIndex < algorithms.size())
        {
            isSorting = false;
            currentAlgorithm = algorithmIndex;

            // Create new instance of the selected algorithm
            switch (algorithmIndex)
            {
            case 0:
                currentSorter = std::make_unique<BubbleSort>();
                break;
            case 1:
                currentSorter = std::make_unique<SelectionSort>();
                break;
            case 2:
                currentSorter = std::make_unique<InsertionSort>();
                break;
            }

            currentSorter->reset(sortState);
            std::cout << "Changed to " << currentSorter->getName() << std::endl;
        }
    }

    void update()
    {
        if (isSorting && sortClock.getElapsedTime().asSeconds() >= sortDelay)
        {
            // Perform multiple steps per frame for higher speeds
            for (int step = 0; step < speedMultiplier && isSorting; ++step)
            {
                bool swapped = currentSorter->performOneStep(array, sortState);

                if (sortState.isComplete)
                {
                    isSorting = false;
                    std::cout << "Sorting completed!" << std::endl;
                    break;
                }
            }

            // Update bar heights and positions after all steps
            for (int i = 0; i < ARRAY_SIZE; ++i)
            {
                bars[i].setSize(sf::Vector2f(BAR_WIDTH - 1, array[i]));
                bars[i].setPosition(i * BAR_WIDTH, WINDOW_HEIGHT - array[i] - 100);
            }

            sortClock.restart();
        }

        updateStatusText();
    }

    void render()
    {
        window.clear(sf::Color::Black);

        // Draw bars
        for (const auto &bar : bars)
        {
            window.draw(bar);
        }

        // Draw UI text
        window.draw(titleText);
        window.draw(instructionsText);
        window.draw(statusText);

        window.display();
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sorting Algorithm Visualizer");
    window.setFramerateLimit(60);

    SortingVisualizer visualizer(window);

    std::cout << "Sorting Visualizer Started!" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "- SPACE: Start/Stop sorting" << std::endl;
    std::cout << "- R: Randomize array" << std::endl;
    std::cout << "- 1: Bubble Sort" << std::endl;
    std::cout << "- 2: Selection Sort" << std::endl;
    std::cout << "- 3: Insertion Sort" << std::endl;
    std::cout << "- +: Increase speed (faster)" << std::endl;
    std::cout << "- -: Decrease speed (slower)" << std::endl;
    std::cout << "- ESC: Exit" << std::endl;

    while (window.isOpen())
    {
        visualizer.handleEvents();
        visualizer.update();
        visualizer.render();
    }

    std::cout << "Application closed." << std::endl;
    return 0;
}
