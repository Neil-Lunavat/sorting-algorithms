# Sorting Algorithm Visualizer - Enhanced Educational Version

An interactive, educational sorting algorithm visualizer designed for students to learn and compare different sorting algorithms through step-by-step visualization.

## 🎯 Project Overview

This project provides a comprehensive visual learning tool for understanding sorting algorithms. It features:

-   **6 Sorting Algorithms**: Bubble Sort, Selection Sort, Shell Sort, Merge Sort, Quick Sort, and Radix Sort
-   **Step-by-Step Visualization**: Pause and step through algorithms one operation at a time
-   **Algorithm Comparison Mode**: Side-by-side comparison of multiple algorithms
-   **Performance Metrics**: Real-time display of steps, swaps, and time complexity information
-   **Educational Interface**: Detailed algorithm descriptions and complexity analysis
-   **High-Resolution Display**: 1280x720 window for better visualization

## ✨ Key Features

### 🎮 Interactive Controls

-   **SPACE**: Pause/Resume algorithm execution
-   **LEFT/RIGHT Arrow Keys**: Step backward/forward through algorithm (when paused)
-   **R**: Reset and randomize array
-   **TAB**: Switch between different sorting algorithms
-   **+/-**: Increase/decrease array size (3-50 elements)
-   **1-6**: Direct algorithm selection
-   **C**: Toggle algorithm comparison mode
-   **ESC**: Exit the application

### 📊 Performance Metrics

-   **Step Counter**: Shows total operations performed
-   **Swap Counter**: Displays number of element swaps
-   **Time Complexity**: Real-time display of best/average/worst case complexity
-   **Array Statistics**: Min, max, and median values
-   **Algorithm Description**: Educational text explaining each algorithm

### 🔄 Algorithm Comparison Mode

-   **Side-by-Side Visualization**: Compare up to 4 algorithms simultaneously
-   **Color-Coded Display**: Each algorithm has a distinct color
-   **Performance Tracking**: Individual step and swap counters for each algorithm
-   **Race Mode**: All algorithms sort the same array simultaneously

## 📚 Implemented Algorithms

### 1. **Bubble Sort** (O(n²))

-   **Best Case**: O(n) - when array is already sorted
-   **Average Case**: O(n²)
-   **Worst Case**: O(n²)
-   **Description**: Compares adjacent elements and swaps them if they're in wrong order
-   **Key**: 1

### 2. **Selection Sort** (O(n²))

-   **Best Case**: O(n²)
-   **Average Case**: O(n²)
-   **Worst Case**: O(n²)
-   **Description**: Finds the minimum element and places it at the beginning
-   **Key**: 2

### 3. **Shell Sort** (O(n^1.5))

-   **Best Case**: O(n log n)
-   **Average Case**: O(n^1.5)
-   **Worst Case**: O(n²)
-   **Description**: Improved insertion sort with gap sequences
-   **Key**: 3

### 4. **Merge Sort** (O(n log n))

-   **Best Case**: O(n log n)
-   **Average Case**: O(n log n)
-   **Worst Case**: O(n log n)
-   **Description**: Divide and conquer with stable sorting
-   **Key**: 4

### 5. **Quick Sort** (O(n log n))

-   **Best Case**: O(n log n)
-   **Average Case**: O(n log n)
-   **Worst Case**: O(n²)
-   **Description**: Divide and conquer with pivot selection
-   **Key**: 5

### 6. **Radix Sort** (O(nk))

-   **Best Case**: O(nk)
-   **Average Case**: O(nk)
-   **Worst Case**: O(nk)
-   **Description**: Non-comparison sort using digit distribution
-   **Key**: 6

## 🚀 Quick Start

### Prerequisites

-   C++17 compatible compiler
-   SFML 2.5 or later
-   CMake 3.10 or later

### Building and Running

1. **Clone the repository**

    ```bash
    git clone <repository-url>
    cd sorting
    ```

2. **Build the project**

    ```bash
    # Windows
    compile.bat

    # Or using CMake
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

3. **Run the visualizer**

    ```bash
    # Windows
    run.bat

    # Or directly
    ./build/bin/SortingVisualizer
    ```

## 🎓 Educational Value

### For Students

-   **Visual Learning**: See exactly how each algorithm works step-by-step
-   **Performance Comparison**: Understand why some algorithms are faster than others
-   **Complexity Analysis**: Learn about time complexity through real examples
-   **Interactive Experience**: Control the speed and progression of algorithms

### For Educators

-   **Classroom Demonstrations**: Perfect for explaining sorting concepts
-   **Algorithm Comparison**: Show students the differences between algorithms
-   **Performance Analysis**: Demonstrate time complexity in practice
-   **Interactive Learning**: Engage students with hands-on visualization

## 🏗️ Technical Architecture

### Core Components

-   **Algorithm Interface**: Simple C-style functions for easy algorithm implementation
-   **Visualization Engine**: SFML-based rendering with smooth animations
-   **UI System**: Modular interface components for different display modes
-   **Input Handler**: Responsive keyboard controls for user interaction
-   **Comparison Mode**: Multi-algorithm visualization system

### File Structure

```
sorting/
├── algorithms/           # Sorting algorithm implementations
│   ├── algorithm_interface.h
│   ├── algorithm_registry.h/cpp
│   ├── bubble_sort.cpp
│   ├── selection_sort.cpp
│   ├── shell_sort.cpp
│   ├── merge_sort.cpp
│   ├── quick_sort.cpp
│   └── radix_sort.cpp
├── src/
│   ├── main.cpp         # Application entry point
│   ├── visualizer.h/cpp # Main visualization controller
│   └── ui/              # User interface components
│       ├── simple_ui.h/cpp
│       ├── bar_renderer.h/cpp
│       ├── input_handler.h/cpp
│       └── algorithm_comparison.h/cpp
├── CMakeLists.txt       # Build configuration
├── compile.bat          # Windows build script
└── run.bat             # Windows run script
```

## 🎨 Visual Features

### Single Algorithm Mode

-   **Cyan bars** represent array elements with heights corresponding to values
-   **Red highlighting** shows elements being compared or swapped
-   **Real-time updates** display each operation as it happens
-   **Information panel** shows algorithm details, performance metrics, and controls

### Comparison Mode

-   **Color-coded sections** for each algorithm (Red, Green, Blue, Yellow)
-   **Side-by-side visualization** of up to 4 algorithms
-   **Individual performance tracking** for each algorithm
-   **Synchronized execution** for fair comparison

## 🔧 Adding New Algorithms

To add a new sorting algorithm:

1. **Create algorithm file** (`algorithms/your_algorithm.cpp`):

    ```cpp
    #include "algorithm_interface.h"

    SwapResult yourAlgorithm(int array[], int size, int *state)
    {
        // Your algorithm implementation
        // Return SwapResult with operation details
    }
    ```

2. **Register the algorithm** in `algorithms/register_algorithms.cpp`:

    ```cpp
    registerAlgorithm("Your Algorithm", yourAlgorithm, stateSize);
    ```

3. **Add algorithm information** in `src/visualizer.cpp`:
    ```cpp
    else if (strcmp(currentAlgorithm->name, "Your Algorithm") == 0)
    {
        best = "O(n)";
        avg = "O(n log n)";
        worst = "O(n²)";
        description = "Your algorithm description";
    }
    ```

## 📈 Performance Analysis

The visualizer helps understand algorithm performance through:

-   **Step-by-step execution**: See exactly how many operations each algorithm performs
-   **Swap counting**: Compare the number of element swaps between algorithms
-   **Visual patterns**: Observe how different algorithms handle the same data
-   **Complexity verification**: Confirm theoretical complexity with practical examples

## 🎯 Use Cases

### Classroom Demonstrations

-   **Algorithm Introduction**: Show students how sorting algorithms work
-   **Performance Comparison**: Demonstrate why some algorithms are preferred
-   **Complexity Analysis**: Visualize time complexity differences
-   **Interactive Learning**: Let students control the visualization

### Research and Analysis

-   **Algorithm Study**: Analyze algorithm behavior on different data sets
-   **Performance Testing**: Compare algorithm efficiency
-   **Educational Content**: Create visual materials for teaching

### Personal Learning

-   **Self-Study**: Learn sorting algorithms at your own pace
-   **Concept Reinforcement**: Visualize abstract algorithmic concepts
-   **Performance Understanding**: See why algorithm choice matters

## 🔮 Future Enhancements

Potential improvements for future versions:

-   **More Algorithms**: Heap Sort, Counting Sort, Bucket Sort
-   **Advanced Visualizations**: 3D representations, network graphs
-   **Performance Profiling**: Detailed timing and memory analysis
-   **Custom Data Sets**: User-defined input arrays
-   **Export Features**: Save visualizations as videos or images
-   **Mobile Support**: Touch-based controls for tablets

## 📄 License

This project is designed for educational purposes. Feel free to use, modify, and distribute for learning and teaching sorting algorithms.

---

**Happy Sorting! 🎉**
