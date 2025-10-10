//
// Created by ybkuanysh on 2025/10/09.
//

#include "../inc/glazunova_5_2_middle_lib.h"

/**
 * @brief Вычисляет котангенс, используя sin/cos.
 */
double cot(double x) {
    return cos(x) / sin(x);
}

/**
 * @brief Выводит матрицу на экран с форматированием.
 */
void print_matrix(const DMatrix& A) {
    cout << "Матрица A (" << middle_N << "x" << middle_M << "):\n";
    for (int i = 0; i < middle_N; ++i) {
        for (int j = 0; j < middle_M; ++j) {
            if (isnan(A[i][j])) {
                cout << setw(12) << "NaN";
            } else {
                cout << setw(12) << fixed << setprecision(4) << A[i][j];
            }
        }
        cout << "\n";
    }
}

/**
 * @brief Выводит вектор на экран.
 */
void print_vector(const vector<double>& B, const string& name) {
    cout << "\nВектор " << name << " (размер " << B.size() << "): [";
    for (size_t i = 0; i < B.size(); ++i) {
        cout << fixed << setprecision(4) << B[i] << (i < B.size() - 1 ? ", " : "");
    }
    cout << "]\n";
}

/**
 * @brief Заполняет матрицу A элементами согласно заданию.
 */
void create_matrix_A(DMatrix& A) {
    for (int i = 0; i < middle_N; ++i) {
        for (int j = 0; j < middle_M; ++j) {

            if (i != j) {
                // a_i,j = cot(i - j) + ln((7i - j) / (i^2 - j^2))
                double diff = i - j;
                double numerator = 7.0 * i - j;
                double denominator = pow(i, 2) - pow(j, 2);

                // Проверки на область определения: sin(x) != 0 и аргумент логарифма > 0
                if (sin(diff) == 0.0 || denominator == 0.0 || numerator / denominator <= 0.0) {
                    A[i][j] = numeric_limits<double>::quiet_NaN();
                    continue;
                }

                A[i][j] = cot(diff) + log(numerator / denominator);

            } else { // i = j
                // a_i,j = log_4(i + j) - e
                // log_4(x) = log(x) / log(4)
                double log_arg = i + j;
                A[i][j] = log(log_arg) / log(4.0) - E;
            }
        }
    }
}

/**
 * @brief Вычисляет вектор B: скалярное произведение каждой строки A на 2-ой столбец A.
 */
void create_vector_B(const DMatrix& A, vector<double>& B) {
    const int second_col_idx = 1; // 2-ой столбец имеет индекс 1

    for (int i = 0; i < middle_N; ++i) {
        double scalar_product = 0.0;

        for (int j = 0; j < middle_M; ++j) {
            scalar_product += A[i][j] * A[j][second_col_idx];
        }
        B[i] = scalar_product;
    }
}

/**
 * @brief Вычисляет функцию G по элементам вектора B.
 */
double calculate_G(const vector<double>& B) {
    double sum_of_squares = 0.0;
    double product = 1.0;

    for (int i = 0; i < middle_N; ++i) {
        sum_of_squares += pow(B[i], 2);
        product *= B[i];
    }

    double expression = sum_of_squares - (static_cast<double>(middle_N) * product);

    if (expression < 0) {
        cerr << "\n! Ошибка: Аргумент корня отрицателен (" << expression << "). Расчет G невозможен.\n";
        return numeric_limits<double>::quiet_NaN();
    }

    return sqrt(expression);
}