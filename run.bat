@echo off
echo Running Sorting Algorithm Visualizer...

if not exist build\SortingVisualizer.exe (
    echo SortingVisualizer.exe not found! Please compile first using compile.bat
    pause
    exit /b 1
)

echo Controls:
echo   SPACE - Pause/Resume
echo   LEFT/RIGHT - Step through algorithm
echo   R - Reset and randomize array
echo   TAB - Change algorithm
echo   ESC - Quit
echo.

cd build
SortingVisualizer.exe
cd ..

echo Application closed.
pause
