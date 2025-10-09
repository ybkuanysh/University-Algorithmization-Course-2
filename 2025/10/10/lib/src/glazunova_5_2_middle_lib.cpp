//
// Created by ybkuanysh on 2025/10/09.
//

#include "../inc/glazunova_5_2_middle_lib.h"

/**
 * @brief Вычисляет котангенс, используя sin/cos.
 */
double cot(double x) {
    return std::cos(x) / std::sin(x);
}

/**
 * @brief Выводит матрицу на экран с форматированием.
 */
void print_matrix(const std::vector<std::vector<double>>& A) {
    std::cout << "Матрица A (" << middle_N << "x" << middle_M << "):\n";
    for (int i = 0; i < middle_N; ++i) {
        for (int j = 0; j < middle_M; ++j) {
            if (std::isnan(A[i][j])) {
                std::cout << std::setw(12) << "NaN";
            } else {
                std::cout << std::setw(12) << std::fixed << std::setprecision(4) << A[i][j];
            }
        }
        std::cout << "\n";
    }
}

/**
 * @brief Выводит вектор на экран.
 */
void print_vector(const std::vector<double>& B, const std::string& name) {
    std::cout << "\nВектор " << name << " (размер " << B.size() << "): [";
    for (size_t i = 0; i < B.size(); ++i) {
        std::cout << std::fixed << std::setprecision(4) << B[i] << (i < B.size() - 1 ? ", " : "");
    }
    std::cout << "]\n";
}

/**
 * @brief Заполняет матрицу A элементами согласно заданию.
 */
void create_matrix_A(std::vector<std::vector<double>>& A) {
    for (int i = 0; i < middle_N; ++i) {
        for (int j = 0; j < middle_M; ++j) {
            // 1-ое индексирование
            double i_prime = static_cast<double>(i + 1);
            double j_prime = static_cast<double>(j + 1);

            if (i != j) {
                // a_i,j = cot(i - j) + ln((7i - j) / (i^2 - j^2))
                double diff = i_prime - j_prime;
                double numerator = 7.0 * i_prime - j_prime;
                double denominator = std::pow(i_prime, 2) - std::pow(j_prime, 2);

                // Проверки на область определения: sin(x) != 0 и аргумент логарифма > 0
                if (std::sin(diff) == 0.0 || denominator == 0.0 || numerator / denominator <= 0.0) {
                    A[i][j] = std::numeric_limits<double>::quiet_NaN();
                    continue;
                }

                // std::log() - это натуральный логарифм (ln)
                A[i][j] = cot(diff) + std::log(numerator / denominator);

            } else { // i = j
                // a_i,j = log_4(i + j) - e
                // log_4(x) = log(x) / log(4)
                double log_arg = i_prime + j_prime; // i + j = 2 * (i+1)
                A[i][j] = std::log(log_arg) / std::log(4.0) - E;
            }
        }
    }
}

/**
 * @brief Вычисляет вектор B: скалярное произведение каждой строки A на 2-ой столбец A.
 */
void create_vector_B(const std::vector<std::vector<double>>& A, std::vector<double>& B) {
    const int second_col_idx = 1; // 2-ой столбец имеет индекс 1

    for (int i = 0; i < middle_N; ++i) { // Для каждой строки A (и элемента B)
        double scalar_product = 0.0;

        for (int j = 0; j < middle_M; ++j) {
            // A[i][j] - j-ый элемент i-ой строки
            // A[j][second_col_idx] - j-ый элемент 2-ого столбца
            scalar_product += A[i][j] * A[j][second_col_idx];
        }
        B[i] = scalar_product;
    }
}

/**
 * @brief Вычисляет функцию G по элементам вектора B.
 */
double calculate_G(const std::vector<double>& B) {
    double sum_of_squares = 0.0;
    double product = 1.0;

    for (int i = 0; i < middle_N; ++i) {
        sum_of_squares += std::pow(B[i], 2);
        product *= B[i];
    }

    double expression = sum_of_squares - (static_cast<double>(middle_N) * product);

    if (expression < 0) {
        std::cerr << "\n! Ошибка: Аргумент корня отрицателен (" << expression << "). Расчет G невозможен.\n";
        return std::numeric_limits<double>::quiet_NaN();
    }

    return std::sqrt(expression);
}