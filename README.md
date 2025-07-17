# Sorting Algorithm Visualizer - Educational Version

An interactive, educational sorting algorithm visualizer designed for students to learn and contribute sorting algorithms in a simple, visual way.

## 🎯 Project Vision

This project is specifically designed to:
- **Help students learn** sorting algorithms through visual, step-by-step execution
- **Encourage contributions** with a simple, beginner-friendly interface
- **Focus on education** over production-level optimization
- **Enable frame-by-frame analysis** of algorithm behavior

## ✨ Features

- **Small Array Size**: 7 elements for clear visualization and easier understanding
- **Step-by-Step Control**: Pause and step through algorithms one swap at a time
- **Visual Highlighting**: Elements being swapped are highlighted in red
- **Frame-Perfect Timing**: 60 FPS with one swap per frame
- **Multiple Algorithms**: Easy to add new sorting algorithms
- **Simple Interface**: Minimal learning curve for contributors

## 🔧 Controls

- **SPACE**: Pause/Resume algorithm execution
- **LEFT/RIGHT Arrow Keys**: Step backward/forward through algorithm (when paused)
- **R**: Reset and randomize array
- **TAB**: Switch between different sorting algorithms
- **ESC**: Exit the application

## 📚 Currently Implemented Algorithms

1. **Bubble Sort** - Compares adjacent elements and swaps them if they're in wrong order
2. **Selection Sort** - Finds the minimum element and places it at the beginning  
3. **Insertion Sort** - Builds the sorted array one element at a time

## 🚀 Quick Start

### Building and Running

1. **Prerequisites**: C++17 compiler and SFML library
2. **Build**: Run `compile.bat` (Windows) or use CMake
3. **Run**: Execute `run.bat` or `build/SortingVisualizer.exe`

### Adding Your Own Algorithm

1. Copy `algorithms/template.cpp` to `algorithms/your_algorithm.cpp`
2. Implement your sorting function following the simple interface
3. Rebuild and test!

## 🎓 For Students and Contributors

This project is designed to be **beginner-friendly**. You don't need to understand SFML or complex C++ features to contribute sorting algorithms.

### Simple Algorithm Interface

All you need to know:
```cpp
SwapResult yourAlgorithm(int array[], int size, int* state) {
    // Your simple sorting logic here
    // Return information about what you swapped
}
```

### What Makes This Project Special

- **No complex OOP**: Simple C-style functions
- **No pointers/references confusion**: Basic array manipulation
- **No SFML knowledge required**: Just focus on your algorithm
- **Step-by-step execution**: One swap per function call
- **Visual feedback**: See exactly what your algorithm does

## 📖 Documentation

- **[Building Guide](docs/BUILDING.md)**: How to compile and run
- **[Contributing Guide](docs/CONTRIBUTING.md)**: Step-by-step guide for adding algorithms
- **[Algorithm Template](algorithms/template.cpp)**: Starting point for new algorithms

## 🏗️ Architecture

### New Simplified Design
- **Algorithms**: Simple C functions that perform one swap per call
- **Visualization**: Professional SFML rendering (you don't need to touch this)
- **Registration**: Automatic algorithm discovery and registration
- **UI**: Clean, educational interface with step-by-step controls

### Why This Design?
- **Separation of Concerns**: Algorithm logic is separate from visualization
- **Easy Contribution**: Students can add algorithms without understanding SFML
- **Educational Focus**: Frame-by-frame execution aids learning
- **Maintainable**: Simple code structure, easy to debug

### Visual Features

-   **Cyan bars** represent array elements with heights corresponding to values
-   **Real-time updates** show each swap/movement as it happens
-   **Status display** shows current algorithm, speed level, and sorting state
-   **Smooth animation** with 5 adjustable speed levels:
    -   **Level 1**: Very Slow (0.1s delay, 1 step per frame)
    -   **Level 2**: Slow (0.05s delay, 1 step per frame)
    -   **Level 3**: Normal (0.02s delay, 1 step per frame) - Default
    -   **Level 4**: Fast (0.01s delay, 2 steps per frame)
    -   **Level 5**: Very Fast (0.005s delay, 3 steps per frame)

## Building and Running

1. **Compile**: Run `compile.bat` to build the project
2. **Execute**: Run `run.bat` to start the visualizer
3. **Use**: Follow the on-screen controls to interact with the visualization

## Adding New Algorithms

To add a new sorting algorithm:

1. **Declare** the class in `sorting_algorithms.h`:

```cpp
class NewSort : public SortingAlgorithm {
public:
    bool performOneStep(std::vector<int>& array, SortState& state) override;
    void reset(SortState& state) override;
    const char* getName() const override { return "New Sort"; }
};
```

2. **Implement** the methods in `sorting_algorithms.cpp`:

```cpp
bool NewSort::performOneStep(std::vector<int>& array, SortState& state) {
    // Implement one step of your algorithm
    // Return true if a visual change occurred
}

void NewSort::reset(SortState& state) {
    // Reset algorithm state
}
```

3. **Add** to the main.cpp algorithms list and key handler

## Technical Details

-   **Array Size**: 100 elements
-   **Window Size**: 800x600 pixels
-   **Frame Rate**: 60 FPS
-   **Speed Levels**: 5 adjustable speeds with both timing and multi-step controls
-   **Animation Speed**: From 0.1s (very slow) to 0.005s (very fast) with up to 3 steps per frame
-   **Random Range**: Bar heights from 10 to 400 pixels

The visualization provides an excellent way to understand how different sorting algorithms work and compare their performance characteristics visually! The new speed controls allow you to slow down for educational purposes or speed up to see the full sorting process quickly.
