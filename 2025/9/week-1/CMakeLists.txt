find_package(Matplot++ REQUIRED)

add_executable(task1 task1.cpp)
target_link_libraries(task1 PUBLIC Matplot++::matplot)
