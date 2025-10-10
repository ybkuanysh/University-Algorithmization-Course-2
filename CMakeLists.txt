cmake_minimum_required(VERSION 4.0.2)

project(Course-2 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Неделя 1
add_subdirectory(2025/9/week-1)
add_executable(week-1-hw 2025/9/week-1/task1.cpp)

# Неделя 5
add_executable(2025-10-3-hw 2025/10/3/hw.cpp)


add_executable(sro1 sro/sro.cpp)

add_executable(sro2 sro/sro2_rk1.cpp)

# Неделя 6
add_subdirectory(2025/10/10)
add_executable(2025-10-10-hw 2025/10/10/hw.cpp)
target_link_libraries(2025-10-10-hw PRIVATE Glazunova_5_2_basic_lib Glazunova_5_2_middle_lib)