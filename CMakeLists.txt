cmake_minimum_required(VERSION 3.15)
project(MyCppProject LANGUAGES CXX)

# Set CXX Standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check whether VCPKG is set up in your system
if(NOT DEFINED ENV{VCPKG_ROOT})
  message(FATAL_ERROR "ERROR: This project requires VCPKG.\n")
endif()

# Set VCPKG root directory
set(VCPKG_ROOT $ENV{VCPKG_ROOT})

# Include VCPKG toolchain
include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)


# Add library project
set(LIB_PROJECT ${CMAKE_PROJECT_NAME}_LIB)
add_library(${LIB_PROJECT} include/example.h src/example.cpp include/example-imgui.h src/example-imgui.cpp)
target_include_directories(${LIB_PROJECT} PRIVATE include)

# Setup imgui
find_package(imgui CONFIG REQUIRED)
target_link_libraries(${LIB_PROJECT} PRIVATE imgui::imgui "d3d12.lib" "dxgi.lib" "d3dcompiler.lib")

# Setup implot
find_package(implot CONFIG REQUIRED)
target_link_libraries(${LIB_PROJECT} PRIVATE implot::implot)

# Add executable project
add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE imgui::imgui ${LIB_PROJECT})

# Setup Catch2
enable_testing()
find_package(Catch2 CONFIG REQUIRED)
include(CTest)
include(Catch)

# Add test project
set(TEST_PROJECT ${CMAKE_PROJECT_NAME}_TEST)
add_executable(${TEST_PROJECT} tests/test_main.cpp tests/test_example.cpp)
target_include_directories(${TEST_PROJECT} PRIVATE include)
target_link_libraries(${TEST_PROJECT} PRIVATE Catch2::Catch2 Catch2::Catch2WithMain ${LIB_PROJECT})

# Automatically discover and add tests
catch_discover_tests(${TEST_PROJECT})