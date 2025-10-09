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
    // 1. Создание динамического массива n*m
    int** matrix = new int*[basic_N];
    for (int i = 0; i < basic_N; ++i) {
        matrix[i] = new int[basic_M];
    }

    int choice;
    std::cout << "Как заполнить матрицу?\n";
    std::cout << "1. Ввести вручную\n";
    std::cout << "2. Сгенерировать случайными числами (от 0 до 100)\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;

    system("clear");

    if (choice == 1) {
        // Ввод данных с клавиатуры
        std::cout << "Введите элементы матрицы " << basic_N << "x" << basic_M << " (целые числа):\n";
        for (int i = 0; i < basic_N; ++i) {
            for (int j = 0; j < basic_M; ++j) {
                std::cout << "Элемент [" << i << "][" << j << "]: ";
                std::cin >> matrix[i][j];
            }
        }
    } else {
        // Заполнение случайными числами
        fill_matrix_randomly(matrix, basic_N, basic_M, 0, 100);
        std::cout << "Матрица успешно заполнена случайными числами.\n";
    }

    std::cout << "\n--- Исходная матрица ---\n";
    print_matrix(matrix, basic_N, basic_M);

    // 3. Вызов библиотечной функции
    swap_min_max_elements(matrix, basic_N, basic_M);

    std::cout << "\n--- Матрица после обмена min и max ---\n";
    print_matrix(matrix, basic_N, basic_M);

    // 4. Очистка динамической памяти
    for (int i = 0; i < basic_N; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

/**
 * @brief <b>5.2 Средний уровень</b>\n
 * Задание: написать программу согласно заданию.\n
 * Вариант 14: массив N*M 6*6.
 */
void glazunova_5_2_middle() {
    // Инициализация матрицы и вектора
    std::vector<std::vector<double>> A(middle_N, std::vector<double>(middle_M));
    std::vector<double> B(middle_N);

    std::cout << "--- Выполнение задания 5.2 (Средний уровень, Вариант 14) ---\n";

    // 1. Создание матрицы A
    create_matrix_A(A);
    print_matrix(A);

    // 2. Создание вектора B
    create_vector_B(A, B);
    print_vector(B, "B");

    // 3. Вычисление функции G
    double G = calculate_G(B);

    // 4. Вывод результата G
    if (!std::isnan(G)) {
        std::cout << "\nРезультат вычисления функции G:\n";
        std::cout << "G = " << std::fixed << std::setprecision(6) << G << "\n";
    } else {
        std::cout << "\nВычисление G завершено с ошибкой (NaN).\n";
    }
    std::cout << "------------------------------------------------------------------\n";
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
