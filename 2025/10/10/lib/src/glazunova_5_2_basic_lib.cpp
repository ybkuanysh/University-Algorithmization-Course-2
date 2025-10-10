//
// Created by ybkuanysh on 2025/10/09.
//

#include "../inc/glazunova_5_2_basic_lib.h"

#include <limits>
#include <random>
#include <chrono>
#include <utility>
#include <algorithm>
#include <iostream>

/**
 * @brief Меняет местами минимальный и максимальный элементы в матрице.
 * * Использует std::vector<std::vector<int>> для представления матрицы.
 *
 * @param matrix Матрица для обработки. Передается по ссылке для изменения.
 */
void swap_min_max_elements_vector(Matrix& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        return;
    }

    int min_val = std::numeric_limits<int>::max();
    int max_val = std::numeric_limits<int>::min();

    std::pair<int, int> min_coords = {0, 0};
    std::pair<int, int> max_coords = {0, 0};

    // Шаг 1: Поиск минимального и максимального элементов и их координат
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            int current_val = matrix[i][j];

            // Ищем минимальный элемент (если несколько - берем первый)
            if (current_val < min_val) {
                min_val = current_val;
                min_coords = {i, j};
            }

            // Ищем максимальный элемент (если несколько - берем первый)
            if (current_val > max_val) {
                max_val = current_val;
                max_coords = {i, j};
            }
        }
    }

    // Шаг 2: Обмен значениями (если координаты min и max не совпадают)
    if (min_coords != max_coords) {
        // Обмен значениями в найденных ячейках
        std::swap(matrix[min_coords.first][min_coords.second],
                  matrix[max_coords.first][max_coords.second]);
    }
}

// --------------------------------------------------

/**
 * @brief Выводит матрицу в консоль.
 * * @param matrix Матрица для вывода.
 */
void print_matrix_vector(const Matrix& matrix) {
    if (matrix.empty()) return;

    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << "\t";
        }
        std::cout << "\n";
    }
}

// --------------------------------------------------

/**
 * @brief Заполняет матрицу случайными числами.
 * * @param matrix Матрица для заполнения. Передается по ссылке для изменения.
 * @param min_val Минимальное случайное значение (включительно).
 * @param max_val Максимальное случайное значение (включительно).
 */
void fill_matrix_randomly_vector(Matrix& matrix, int min_val, int max_val) {
    if (matrix.empty() || matrix[0].empty()) {
        return;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    std::uniform_int_distribution<int> distribution(min_val, max_val);

    for (auto& row : matrix) {
        for (int& val : row) {
            val = distribution(generator);
        }
    }
}

// --------------------------------------------------

