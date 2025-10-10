//
// Created by ybkuanysh on 2025/10/09.
//

#ifndef COURSE_2_GLAZUNOVA_5_2_BASIC_LIB_H
#define COURSE_2_GLAZUNOVA_5_2_BASIC_LIB_H

#include <vector>

using Matrix = std::vector<std::vector<int>>;

/**
 * @brief Меняет местами минимальный и максимальный элементы в матрице.
 * * @param matrix Матрица для обработки. Передается по ссылке для изменения.
 */
void swap_min_max_elements_vector(Matrix& matrix);

/**
 * @brief Выводит матрицу в консоль.
 * * @param matrix Матрица для вывода.
 */
void print_matrix_vector(const Matrix& matrix);

/**
 * @brief Заполняет матрицу случайными числами в заданном диапазоне.
 * * @param matrix Матрица для заполнения. Передается по ссылке для изменения.
 * @param min_val Минимальное случайное значение (включительно).
 * @param max_val Максимальное случайное значение (включительно).
 */
void fill_matrix_randomly_vector(Matrix& matrix, int min_val, int max_val);

#endif //COURSE_2_GLAZUNOVA_5_2_BASIC_LIB_H