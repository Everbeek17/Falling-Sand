cmake_minimum_required(VERSION 3.28)
project(FallingSand LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Add my directories
include_directories(
    src/game
    src/debug)

# Lists all the .cpp files
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/game/game_logic.cpp
    src/game/window_logic.cpp
    src/game/block_map.cpp
    src/debug/timer_functions.cpp
    src/debug/window_functions.cpp)

# Set additional compiler definitions for debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
endif()

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)
