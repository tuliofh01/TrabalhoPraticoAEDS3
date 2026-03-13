cmake_minimum_required(VERSION 3.10)
project(AcademicEnrollmentSystem LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output executables to builds/ directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/builds)

# Add executable
add_executable(enrollment_system
    src/main.cpp
    src/dao/StudentDAO.cpp
)

# Add test executable
add_executable(run_tests
    tests/test_main.cpp
    src/dao/StudentDAO.cpp
)

# Optional: Set compiler-specific flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /permissive-)
endif()