cmake_minimum_required(VERSION 4.0.2)

#set(CMAKE_CXX_COMPILER /Library/Developer/CommandLineTools/usr/bin)
project(Course-2 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Неделя 1
find_package(Matplot++ REQUIRED)
add_executable(week-1-hw 2025/9/week-1/task1.cpp)
target_link_libraries(week-1-hw PUBLIC Matplot++::matplot)

# Неделя 5
add_executable(2025-10-3-hw 2025/10/3/hw.cpp)


add_executable(sro1 sro/sro.cpp)
add_executable(sro2 sro/sro2_rk1.cpp)
add_executable(sro3 sro/sro3.cpp)
add_executable(sro4 sro/sro4.cpp)
add_executable(sro5 sro/sro5.cpp)
add_executable(rk2 sro/rk2.cpp)

# Неделя 6
add_subdirectory(2025/10/10)
add_executable(2025-10-10-hw 2025/10/10/hw.cpp)
target_link_libraries(2025-10-10-hw PRIVATE Glazunova_5_2_basic_lib Glazunova_5_2_middle_lib)

# Неделя 7
add_executable(2025-10-17-hw 2025/10/17/hw.cpp)

# Неделя 8
add_executable(2025-10-24-cw 2025/10/24/cw.cpp)

# Неделя 9
add_executable(2025-10-31-hw 2025/10/31/hw.cpp)
add_executable(2025-10-31-cw 2025/10/31/cw.cpp)

# Неделя 10
add_executable(2025-11-7-cw 2025/11/7/hw.cpp)

# Неделя 11
add_executable(2025-11-14-hw 2025/11/14/hw.cpp)
add_executable(2025-11-14-cw 2025/11/14/cw.cpp)

# Неделя 12
add_executable(2025-11-21-hw 2025/11/21/hw.cpp)

# Неделя 13
add_executable(2025-11-28-cw 2025/11/28/cw.cpp)
add_executable(2025-11-28-hw 2025/11/28/hw.cpp)

# Неделя 14
add_executable(2025-12-5-hw 2025/12/5/hw.cpp)

# Неделя 15
add_executable(2025-12-12-hw 2025/12/12/hw.cpp)