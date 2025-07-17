# Building the Sorting Algorithm Visualizer

This guide will help you build and run the sorting algorithm visualizer on your system.

## Prerequisites

### Required Software

-   **C++ Compiler**: GCC, Clang, or Visual Studio
-   **SFML Library**: Version 2.5 or higher
-   **CMake**: Version 3.10 or higher (recommended)

### Installing SFML

#### Windows

1. Download SFML from https://www.sfml-dev.org/download.php
2. Extract to a folder (e.g., `C:\SFML`)
3. Add SFML to your system PATH or use the full path in build commands

#### Linux (Ubuntu/Debian)

```bash
sudo apt-get install libsfml-dev
```

#### macOS

```bash
brew install sfml
```

## Building with CMake (Recommended)

### 1. Create CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)
project(SortingVisualizer)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Find all algorithm files
file(GLOB ALGORITHM_SOURCES "algorithms/*.cpp")

# Create executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/visualizer.cpp
    src/ui/simple_ui.cpp
    src/ui/bar_renderer.cpp
    src/ui/input_handler.cpp
    algorithms/algorithm_registry.cpp
    ${ALGORITHM_SOURCES}
)

# Link SFML
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src)
```

### 2. Build Commands

```bash
mkdir build
cd build
cmake ..
make
```

### 3. Run

```bash
./SortingVisualizer
```

## Building with Direct Compilation

### Windows (MinGW)

```batch
g++ -std=c++17 -I"C:\SFML\include" -L"C:\SFML\lib" ^
    src/main.cpp src/visualizer.cpp ^
    src/ui/simple_ui.cpp src/ui/bar_renderer.cpp src/ui/input_handler.cpp ^
    algorithms/algorithm_registry.cpp ^
    algorithms/bubble_sort.cpp algorithms/selection_sort.cpp algorithms/insertion_sort.cpp ^
    -lsfml-graphics -lsfml-window -lsfml-system ^
    -o SortingVisualizer.exe
```

### Linux/macOS

```bash
g++ -std=c++17 \
    src/main.cpp src/visualizer.cpp \
    src/ui/simple_ui.cpp src/ui/bar_renderer.cpp src/ui/input_handler.cpp \
    algorithms/algorithm_registry.cpp \
    algorithms/bubble_sort.cpp algorithms/selection_sort.cpp algorithms/insertion_sort.cpp \
    -lsfml-graphics -lsfml-window -lsfml-system \
    -o SortingVisualizer
```

## Updated Build Scripts

### compile.bat (Windows)

```batch
@echo off
echo Building Sorting Algorithm Visualizer...

set SFML_DIR=C:\SFML
set BUILD_DIR=build

if not exist %BUILD_DIR% mkdir %BUILD_DIR%

g++ -std=c++17 -I"%SFML_DIR%\include" -L"%SFML_DIR%\lib" ^
    src/main.cpp src/visualizer.cpp ^
    src/ui/simple_ui.cpp src/ui/bar_renderer.cpp src/ui/input_handler.cpp ^
    algorithms/algorithm_registry.cpp ^
    algorithms/bubble_sort.cpp algorithms/selection_sort.cpp algorithms/insertion_sort.cpp ^
    -lsfml-graphics -lsfml-window -lsfml-system ^
    -o %BUILD_DIR%/SortingVisualizer.exe

if %errorlevel% == 0 (
    echo Build successful!
    echo Run with: %BUILD_DIR%\SortingVisualizer.exe
) else (
    echo Build failed!
)
```

### run.bat (Windows)

```batch
@echo off
if exist build\SortingVisualizer.exe (
    echo Running Sorting Algorithm Visualizer...
    build\SortingVisualizer.exe
) else (
    echo Please build the project first using compile.bat
)
```

## Troubleshooting

### Common Issues

#### SFML Not Found

-   **Windows**: Check that SFML is properly installed and paths are correct
-   **Linux**: Install SFML development packages: `sudo apt-get install libsfml-dev`
-   **macOS**: Install via Homebrew: `brew install sfml`

#### Font Loading Issues

The program tries to load fonts from:

1. `arial.ttf` (current directory)
2. `C:/Windows/Fonts/arial.ttf` (Windows)
3. System default font (fallback)

If fonts don't load, the program will still run but text may not display correctly.

#### Missing DLLs (Windows)

Copy SFML DLLs to your output directory:

-   `sfml-graphics-2.dll`
-   `sfml-window-2.dll`
-   `sfml-system-2.dll`

#### Compilation Errors

-   Ensure C++17 support is enabled
-   Check that all source files are included in compilation
-   Verify SFML version compatibility

### Performance Issues

-   The visualizer runs at 60 FPS by default
-   If performance is poor, try reducing the frame rate
-   Ensure graphics drivers are up to date

## Development Setup

### VS Code Configuration

Create `.vscode/c_cpp_properties.json`:

```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": ["${workspaceFolder}/**", "C:/SFML/include"],
            "defines": [],
            "compilerPath": "C:/msys64/mingw64/bin/g++.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "gcc-x64"
        }
    ],
    "version": 4
}
```

### Adding New Algorithms

1. Create new `.cpp` file in `algorithms/` directory
2. Follow the template structure
3. Algorithm will be automatically included in build
4. No need to modify build scripts

## Platform-Specific Notes

### Windows

-   Use MinGW or Visual Studio
-   Ensure proper DLL placement
-   May need to adjust font paths

### Linux

-   Install SFML development packages
-   Use system package manager
-   Font loading should work automatically

### macOS

-   Use Homebrew for SFML installation
-   Clang compiler recommended
-   May need to adjust font paths

## Next Steps

After successful build:

1. Run the visualizer
2. Test with existing algorithms
3. Try adding your own algorithm
4. Read the contribution guide for more details

For more help, check the project documentation or create an issue on GitHub.
