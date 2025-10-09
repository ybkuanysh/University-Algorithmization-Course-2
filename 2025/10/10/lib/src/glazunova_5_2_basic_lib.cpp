//
// Created by ybkuanysh on 2025/10/09.
//

#include "../inc/glazunova_5_2_basic_lib.h"
#include <limits> // Для std::numeric_limits
#include <random>    // Для генератора случайных чисел
#include <chrono>    // Для инициализации генератора

void swap_min_max_elements(int** matrix, int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        // Защита от некорректных размеров
        return;
    }

    // Инициализация координат и значений
    int min_val = std::numeric_limits<int>::max();
    int max_val = std::numeric_limits<int>::min();

    // Координаты минимального элемента
    int min_row = 0;
    int min_col = 0;

    // Координаты максимального элемента
    int max_row = 0;
    int max_col = 0;

    // Шаг 1: Поиск минимального и максимального элементов и их координат
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int current_val = matrix[i][j];

            // Ищем минимальный элемент (если несколько - берем первый)
            if (current_val < min_val) {
                min_val = current_val;
                min_row = i;
                min_col = j;
            }

            // Ищем максимальный элемент (если несколько - берем первый)
            if (current_val > max_val) {
                max_val = current_val;
                max_row = i;
                max_col = j;
            }
        }
    }

    // Шаг 2: Обмен значениями (если они не совпадают)
    // Достаточно поменять значения в найденных ячейках.
    if (min_row != max_row || min_col != max_col) {
        // Используем стандартную функцию обмена
        std::swap(matrix[min_row][min_col], matrix[max_row][max_col]);
    }
    // Если min_val == max_val (например, вся матрица из нулей),
    // то min_row/col == max_row/col, и обмен не требуется.
}

// Опциональная функция для вывода (полезно для тестирования)
void print_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

/**
 * Реализация функции генерации случайных чисел
 */
void fill_matrix_randomly(int** matrix, int rows, int cols, int min_val, int max_val) {
    if (rows <= 0 || cols <= 0) {
        return;
    }

    // 1. Инициализация генератора случайных чисел
    // Используем текущее время для инициализации (получаем "seed" для рандома)
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    // 2. Определение равномерного распределения в заданном диапазоне
    std::uniform_int_distribution<int> distribution(min_val, max_val);

    // 3. Заполнение матрицы
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = distribution(generator);
        }
    }
}