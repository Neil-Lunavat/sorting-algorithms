#include "algorithm_comparison.h"
#include "../../algorithms/algorithm_registry.h"
#include <random>
#include <algorithm>
#include <cstring>

AlgorithmComparison::AlgorithmComparison()
    : isActive(false), currentStep(0), isPaused(true)
{
}

AlgorithmComparison::~AlgorithmComparison()
{
    for (auto& algo : algorithms)
    {
        delete[] algo.array;
        delete[] algo.originalArray;
    }
}

bool AlgorithmComparison::initialize()
{
    // Add algorithms for comparison
    addAlgorithm(getAlgorithmByName("Bubble Sort"), sf::Color::Red);
    addAlgorithm(getAlgorithmByName("Selection Sort"), sf::Color::Green);
    addAlgorithm(getAlgorithmByName("Merge Sort"), sf::Color::Yellow);
    addAlgorithm(getAlgorithmByName("Radix Sort"), sf::Color::Blue);
    
    isActive = true;
    reset();
    return true;
}

void AlgorithmComparison::addAlgorithm(AlgorithmInfo* algorithm, sf::Color color)
{
    if (algorithms.size() >= MAX_ALGORITHMS || !algorithm)
        return;

    ComparisonAlgorithm compAlgo;
    compAlgo.algorithm = algorithm;
    compAlgo.array = new int[COMPARISON_ARRAY_SIZE];
    compAlgo.originalArray = new int[COMPARISON_ARRAY_SIZE];
    compAlgo.color = color;
    
    algorithms.push_back(compAlgo);
}

void AlgorithmComparison::reset()
{
    currentStep = 0;
    isPaused = true;
    
    initializeArrays();
    randomizeArrays();
    
    for (auto& algo : algorithms)
    {
        std::memset(algo.state, 0, sizeof(algo.state));
        algo.stepCount = 0;
        algo.swapCount = 0;
        algo.isComplete = false;
        
        // Copy original array
        for (int i = 0; i < COMPARISON_ARRAY_SIZE; i++)
        {
            algo.originalArray[i] = algo.array[i];
        }
    }
}

void AlgorithmComparison::stepForward()
{
    if (isPaused || isComplete())
        return;

    currentStep++;
    
    for (auto& algo : algorithms)
    {
        if (!algo.isComplete)
        {
            SwapResult result = algo.algorithm->function(algo.array, COMPARISON_ARRAY_SIZE, algo.state);
            
            if (result.swapped)
            {
                algo.stepCount++;
                algo.swapCount++;
            }
            
            algo.isComplete = result.isComplete;
        }
    }
}

bool AlgorithmComparison::isComplete() const
{
    for (const auto& algo : algorithms)
    {
        if (!algo.isComplete)
            return false;
    }
    return true;
}

void AlgorithmComparison::render(sf::RenderWindow& window)
{
    if (!isActive)
        return;

    // Render each algorithm's array as bars
    int windowWidth = window.getSize().x;
    int windowHeight = window.getSize().y;
    int sectionWidth = windowWidth / algorithms.size();
    
    // Draw title and controls
    sf::Font font;
    if (font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        // Title
        sf::Text title;
        title.setFont(font);
        title.setString("Algorithm Comparison Mode");
        title.setCharacterSize(24);
        title.setFillColor(sf::Color::White);
        title.setPosition(20, 20);
        window.draw(title);
        
        // Controls
        sf::Text controls;
        controls.setFont(font);
        controls.setString("Controls: SPACE: pause/resume | S: step | R: reset | C: exit comparison");
        controls.setCharacterSize(16);
        controls.setFillColor(sf::Color::Yellow);
        controls.setPosition(20, 50);
        window.draw(controls);
        
        // Status
        sf::Text status;
        status.setFont(font);
        status.setCharacterSize(14);
        status.setFillColor(sf::Color::Cyan);
        status.setPosition(20, 80);
        if (isPausedState())
        {
            status.setString("Status: PAUSED - Press SPACE to start or S to step");
        }
        else
        {
            status.setString("Status: RUNNING - Press SPACE to pause");
        }
        window.draw(status);
    }
    
    for (size_t i = 0; i < algorithms.size(); i++)
    {
        const auto& algo = algorithms[i];
        int startX = i * sectionWidth;
        
        // Draw algorithm name
        if (font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
        {
            sf::Text text;
            text.setFont(font);
            text.setString(algo.algorithm->name);
            text.setCharacterSize(18);
            text.setFillColor(algo.color);
            text.setPosition(startX + 10, 120);
            window.draw(text);
            
            // Draw step and swap info
            sf::Text info;
            info.setFont(font);
            info.setCharacterSize(14);
            info.setFillColor(sf::Color::White);
            info.setPosition(startX + 10, 145);
            info.setString("Steps: " + std::to_string(algo.stepCount) + " | Swaps: " + std::to_string(algo.swapCount));
            window.draw(info);
            
            // Draw completion status
            sf::Text complete;
            complete.setFont(font);
            complete.setCharacterSize(12);
            complete.setPosition(startX + 10, 165);
            if (algo.isComplete)
            {
                complete.setString("COMPLETE");
                complete.setFillColor(sf::Color::Green);
            }
            else
            {
                complete.setString("RUNNING");
                complete.setFillColor(sf::Color::Yellow);
            }
            window.draw(complete);
        }
        
        // Draw bars
        float barWidth = (float)(sectionWidth - 20) / COMPARISON_ARRAY_SIZE;
        float maxHeight = windowHeight - 200;
        
        for (int j = 0; j < COMPARISON_ARRAY_SIZE; j++)
        {
            sf::RectangleShape bar;
            float height = (float)algo.array[j] / COMPARISON_ARRAY_SIZE * maxHeight;
            bar.setSize(sf::Vector2f(barWidth - 1, height));
            bar.setPosition(startX + 10 + j * barWidth, windowHeight - height - 100);
            bar.setFillColor(algo.color);
            window.draw(bar);
        }
    }
}

void AlgorithmComparison::initializeArrays()
{
    for (auto& algo : algorithms)
    {
        for (int i = 0; i < COMPARISON_ARRAY_SIZE; i++)
        {
            algo.array[i] = i + 1;
        }
    }
}

void AlgorithmComparison::randomizeArrays()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (auto& algo : algorithms)
    {
        std::shuffle(algo.array, algo.array + COMPARISON_ARRAY_SIZE, gen);
    }
} 