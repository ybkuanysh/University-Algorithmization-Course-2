//
// Created by ybkuanysh on 2025/10/10.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <random>

#define A 1
#define B 100
#define N_ROWS 6
#define M_COLS 5

using namespace std;
using Matrix = vector<vector<int>>;

/**
 *
 * @return
 */

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

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    uniform_int_distribution<int> distribution(min_val, max_val);

    for (auto& row : matrix) {
        for (int& val : row) {
            val = distribution(generator);
        }
    }
}


/**
 * @brief Выводит матрицу на экран с форматированием.
 */
void print_matrix(const Matrix& matrix) {
    cout << "Матрица matrix (" << N_ROWS << "x" << M_COLS << "):\n";
    for (int i = 0; i < N_ROWS; ++i) {
        for (int j = 0; j < M_COLS; ++j) {
            if (isnan(matrix[i][j])) {
                cout << setw(12) << "NaN";
            } else {
                cout << setw(12) << fixed << setprecision(4) << matrix[i][j];
            }
        }
        cout << "\n";
    }
}

/**
 * Основная функция задачи.
 */
int task_8_c(Matrix& matrix) {
    int max_num = A - 1;

    for (int i = 0; i < M_COLS; ++i) {
        bool COL_SORTED_ASC = true;
        bool COL_SORTED_DESC = true;

        for (int j = 0; j < N_ROWS - 1; ++j) {
            if (matrix[j][i] < matrix[j + 1][i]) COL_SORTED_ASC = false;
            if (matrix[j][i] > matrix[j + 1][i]) COL_SORTED_DESC = false;
        }

        if (COL_SORTED_ASC || COL_SORTED_DESC) {
            for (int j = 0; j < N_ROWS; ++j) {
                if (matrix[j][i] > max_num) {
                    max_num = matrix[j][i];
                }
            }
        }
    }
    return max_num;
}

int main() {
    Matrix matrix(N_ROWS, vector<int>(M_COLS));

    int choice;
    cout << "Как заполнить матрицу " << N_ROWS << "x" << M_COLS << "?\n"
            "1. Ввести вручную\n"
            "2. Сгенерировать случайными числами (от " << A << " до " << B << ")\n"
            "Ваш выбор: ";
    cin >> choice;

    system("clear");

    if (choice == 1) {
        cout << "Введите элементы матрицы " << N_ROWS << "x" << M_COLS << " (целые числа):\n";
        for (int i = 0; i < N_ROWS; ++i) {
            for (int j = 0; j < M_COLS; ++j) {
                cout << "Элемент [" << i << "][" << j << "]: ";
                cin >> matrix[i][j];
            }
        }
    } else {
        fill_matrix_randomly_vector(matrix, A, B);
        cout << "Матрица успешно заполнена случайными числами.\n";
    }

    print_matrix(matrix);

    int max_num = task_8_c(matrix);

    if (max_num != A - 1) {
        cout << "Максимальное число среди отсортированных столбцов: " << max_num << endl;
    } else {
        cout << "Нет ни одного отсортированного столбца" << endl;
    }

    return 0;
}