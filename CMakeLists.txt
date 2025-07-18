cmake_minimum_required(VERSION 3.10)
project(SortingVisualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Find all algorithm files
file(GLOB ALGORITHM_SOURCES "algorithms/*.cpp")
list(REMOVE_ITEM ALGORITHM_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/algorithms/template.cpp")

# Create executable
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/visualizer.cpp
    src/ui/simple_ui.cpp
    src/ui/bar_renderer.cpp
    src/ui/input_handler.cpp
    src/ui/algorithm_comparison.cpp
    algorithms/algorithm_registry.cpp
    ${ALGORITHM_SOURCES}
)

# Link SFML
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Copy SFML DLLs to output directory (Windows only)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
