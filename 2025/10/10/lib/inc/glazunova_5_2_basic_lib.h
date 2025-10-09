//
// Created by ybkuanysh on 2025/10/09.
//

#ifndef COURSE_2_GLAZUNOVA_5_2_BASIC_LIB_H
#define COURSE_2_GLAZUNOVA_5_2_BASIC_LIB_H

#include <iostream>
#include <algorithm> // Для std::swap, хоть это и не строго обязательно

const int basic_N = 6; // строки
const int basic_M = 5; // столбцы

/**
 * @brief Меняет местами минимальный и максимальный элементы в заданной матрице.
 * * @param matrix Двумерный массив целых чисел.
 * @param rows Количество строк (n).
 * @param cols Количество столбцов (m).
 */
void swap_min_max_elements(int** matrix, int rows, int cols);

/**
 * @brief Вспомогательная функция для вывода матрицы (опционально, для отладки).
 */
void print_matrix(int** matrix, int rows, int cols);

/**
 * @brief Заполняет матрицу случайными целыми числами в заданном диапазоне.
 * * @param matrix Двумерный массив целых чисел.
 * @param rows Количество строк (n).
 * @param cols Количество столбцов (m).
 * @param min_val Минимально возможное значение (включительно).
 * @param max_val Максимально возможное значение (включительно).
 */
void fill_matrix_randomly(int** matrix, int rows, int cols, int min_val, int max_val);

#endif //COURSE_2_GLAZUNOVA_5_2_BASIC_LIB_H