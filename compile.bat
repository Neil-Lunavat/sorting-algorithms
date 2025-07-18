@echo off
echo Building Sorting Algorithm Visualizer...

:: Add MSYS2 MinGW to PATH
set PATH=C:\msys64\mingw64\bin;%PATH%

:: Create build directory if it doesn't exist
if not exist build mkdir build

:: Navigate to script directory
cd /d "%~dp0"

echo Compiling new visualizer...
g++ -std=c++17 -Wall -O2 -mwindows ^
    src/main.cpp src/visualizer.cpp ^
    src/ui/simple_ui.cpp src/ui/bar_renderer.cpp src/ui/input_handler.cpp ^
    algorithms/algorithm_registry.cpp algorithms/register_algorithms.cpp ^
    algorithms/bubble_sort.cpp algorithms/selection_sort.cpp ^
    algorithms/shell_sort.cpp algorithms/merge_sort.cpp ^
    -lsfml-graphics -lsfml-window -lsfml-system ^
    -o build/SortingVisualizer.exe

if %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
    echo Executable created: build/SortingVisualizer.exe
    
    :: Copy SFML DLLs
    echo Copying SFML DLLs...
    copy "C:\msys64\mingw64\bin\sfml-*.dll" build\ >nul 2>&1
    
    echo Build completed successfully!
) else (
    echo Compilation failed!
    echo Error details:
    g++ -std=c++17 -Wall -O2 ^
        src/main.cpp src/visualizer.cpp ^
        src/ui/simple_ui.cpp src/ui/bar_renderer.cpp src/ui/input_handler.cpp ^
        algorithms/algorithm_registry.cpp algorithms/register_algorithms.cpp ^
        algorithms/bubble_sort.cpp algorithms/selection_sort.cpp ^
        algorithms/shell_sort.cpp algorithms/merge_sort.cpp ^
        -lsfml-graphics -lsfml-window -lsfml-system ^
        -o build/SortingVisualizer.exe
    exit /b 1
)
