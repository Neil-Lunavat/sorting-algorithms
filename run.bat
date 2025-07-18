@echo off

if not exist build\SortingVisualizer.exe (
    echo SortingVisualizer.exe not found! Please compile first using compile.bat
    exit /b 1
)

cd build
start SortingVisualizer.exe
cd ..
