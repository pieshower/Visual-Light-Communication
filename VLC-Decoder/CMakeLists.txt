cmake_minimum_required(VERSION 3.10)

# Project name
project(VLC-Decode)

# Use modern C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(OpenCV REQUIRED)

# Add your source files
add_executable(
    ${PROJECT_NAME}  
    source/main.cpp
    source/VLCDecoder.cpp
#   source/VLCVisualizer.cpp
)

# Link OpenCV
target_include_directories(${PROJECT_NAME}  PRIVATE ${OpenCV_INCLUDE_DIRS})

# Link Libraries to Target
target_link_libraries(
    ${PROJECT_NAME} 
    ${OpenCV_LIBS}
)
