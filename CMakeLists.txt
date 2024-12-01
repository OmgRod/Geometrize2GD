cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(Geometrize2GD VERSION 1.0.0)

include(cmake/CPM.cmake)

# Adding the geometrize-lib package
CPMAddPackage(
    NAME geometrize-lib
    GITHUB_REPOSITORY Tw1ddle/geometrize-lib
    GIT_TAG master
    OPTIONS "BUILD_EXAMPLES OFF"
)

# Gather all .cpp files recursively from the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Gather all .h files recursively from the src directory (optional, if needed)
file(GLOB_RECURSE HEADERS "src/*.h")

# Now that geometrize-lib is available, add it to the project
add_library(${PROJECT_NAME} SHARED
    ${SOURCES}
    ${HEADERS}
)

# Make sure the Geode SDK is available
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

# Add the Geode SDK as a subdirectory
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Set up the Geode mod
setup_geode_mod(${PROJECT_NAME})