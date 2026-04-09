cmake_minimum_required(VERSION 3.10)
project(Project)

set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.10)
project(Project)

set(CMAKE_CXX_STANDARD 17)

# Include your local headers
include_directories(include)

# Add executable + glad.c
add_executable(main 
    main.cpp 
    glad.c
)

# Find packages from vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

# Link libraries
target_link_libraries(main 
    PRIVATE 
    glfw 
    assimp::assimp
)

