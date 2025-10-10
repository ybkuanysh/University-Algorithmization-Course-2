//
// Created by ybkuanysh on 2025/10/09.
//
#include "glazunova_5_2_basic_lib.h"
#include "glazunova_5_2_middle_lib.h"

using namespace std;

/**
 * @brief <b>5.2 Базовый уровень</b>\n
 * Задание: ввести с клавиатуры массив, состоящий из n строк и m столбцов.
 * Создать библиотеку, в которой будет содержаться функция, которая производит
 * вычисления согласно заданию, приведенному в таблице.\n
 * Вариант 14: массив n*m 6*5 из целых чисел. Функция из библиотеки glazunova_5_2_basic_lib
 * должна менять максимальный и минимальный элемент матрицы.
 */
void glazunova_5_2_basic() {
    const int N_ROWS = 6;
    const int M_COLS = 5;

    Matrix matrix(N_ROWS, vector<int>(M_COLS));

    int choice;
    cout << "Как заполнить матрицу " << N_ROWS << "x" << M_COLS << "?\n";
    cout << "1. Ввести вручную\n";
    cout << "2. Сгенерировать случайными числами (от 0 до 100)\n";
    cout << "Ваш выбор: ";
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
        fill_matrix_randomly_vector(matrix, 0, 100);
        cout << "Матрица успешно заполнена случайными числами.\n";
    }

    cout << "\n--- Исходная матрица ---\n";
    print_matrix_vector(matrix);

    // 3. Вызов библиотечной функции, использующей векторы
    swap_min_max_elements_vector(matrix);

    cout << "\n--- Матрица после обмена min и max ---\n";
    print_matrix_vector(matrix);
}

/**
 * @brief <b>5.2 Средний уровень</b>\n
 * Задание: написать программу согласно заданию.\n
 * Вариант 14: массив N*M 6*6.
 */
void glazunova_5_2_middle() {
    DMatrix A(middle_N, vector<double>(middle_M));
    vector<double> B(middle_N);

    cout << "--- Выполнение задания 5.2 (Средний уровень, Вариант 14) ---\n";

    create_matrix_A(A);
    print_matrix(A);

    create_vector_B(A, B);
    print_vector(B, "B");

    double G = calculate_G(B);

    if (!isnan(G)) {
        cout << "\nРезультат вычисления функции G:\n";
        cout << "G = " << fixed << setprecision(6) << G << "\n";
    } else {
        cout << "\nВычисление G завершено с ошибкой (NaN).\n";
    }
    cout << "------------------------------------------------------------------\n";
}

void waitForContinue() {
    cin.ignore();
    cout << "Для продолжения нажмите Enter." << endl;
    cin.get();
    system("clear");
}

int main() {
    bool exit = false;

    system("clear");

    while (!exit) {
        cout << "\033[1mВыберите задачу из списка:\033[0m\n"
                "1) 5.2 Базовый уровень\n"
                "2) 5.2 Средний уровень\n"
                "0) Выйти\n"
                "\033[7mВы ввели: ";
        int taskNum;
        cin >> taskNum;
        cout << "\033[0m";
        system("clear");
        switch (taskNum) {
            case 1:
                glazunova_5_2_basic();
                waitForContinue();
                break;
            case 2:
                glazunova_5_2_middle();
                waitForContinue();
                break;
            case 0:
                exit = true;
                break;
            default:
                cout << "\033[1;31mЗадания с таким номером нет. Попробуйте снова.\033[0m" << endl;
                break;
        }
    }

    cout << "\033[36mВыход из программы.\033[0m" << endl;
    return 0;
}
