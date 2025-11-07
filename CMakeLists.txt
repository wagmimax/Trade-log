cmake_minimum_required(VERSION 3.10)
project(TradeLog)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the path to vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "C:/Users/maxxk/OneDrive/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# Add path to tabulate configuration
set(CMAKE_PREFIX_PATH "C:/Users/maxxk/OneDrive/vcpkg/installed/x64-windows/share")

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find and include the tabulate package
find_package(tabulate CONFIG REQUIRED)

# Add executable
add_executable(TradeLog 
src/main.cpp
src/UserIMP.cpp
)

# Link the tabulate library
target_link_libraries(TradeLog PRIVATE tabulate::tabulate)