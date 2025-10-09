//
// Created by ybkuanysh on 2025/10/09.
//

#ifndef COURSE_2_GLAZUNOVA_5_2_MIDDLE_LIB_H
#define COURSE_2_GLAZUNOVA_5_2_MIDDLE_LIB_H

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <limits>
#include <string>

// Размеры матрицы согласно Варианту 14
const int middle_N = 6;
const int middle_M = 6;
// Константа e
const double E = std::exp(1.0);

double cot(double x);

void print_matrix(const std::vector<std::vector<double>>& A);

void print_vector(const std::vector<double>& B, const std::string& name);

void create_matrix_A(std::vector<std::vector<double>>& A);

void create_vector_B(const std::vector<std::vector<double>>& A, std::vector<double>& B);

double calculate_G(const std::vector<double>& B);

#endif //COURSE_2_GLAZUNOVA_5_2_MIDDLE_LIB_H