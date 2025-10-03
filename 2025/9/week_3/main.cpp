#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

void glazunova_3_1_middle();

void glazunova_3_2_low();

void glazunova_3_2_middle();

void glazunova_3_2_high();

void glazunova_3_4_high();

int main() {
    bool exit = false;

    while (!exit) {
        cout << "Выберите задание из списка: \n"
                "1) Глазунова 3.1 средний\n"
                "2) Глазунова 3.2 легкий\n"
                "3) Глазунова 3.2 средний\n"
                "4) Глазунова 3.2 высокий\n"
                "5) Глазунова 3.4 высокий\n"
                "Вы ввели: ";
        int taskNum;
        cin >> taskNum;

        switch (taskNum) {
            case 1:
                glazunova_3_1_middle();
                break;
            case 2:
                glazunova_3_2_low();
                break;
            case 3:
                glazunova_3_2_middle();
                break;
            case 4:
                glazunova_3_2_high();
                break;
            case 5:
                glazunova_3_4_high();
                break;
            case 0:
                exit = true;
                break;
            default:
                cout << "Задания с таким номером нет. Попробуйте снова." << endl;
                break;
        }
    }

    cout << "Выход из программы" << endl;
    return 0;
}

/**
 * @brief <b>3.1 СРЕДНИЙ УРОВЕНЬ</b>\n
 * <b>Задание:</b> составить схему алгоритма и написать программу вычисления суммы (произведения)
 * конечного ряда. При разработке программы предусмотреть пропуск слагаемых (множителей),
 * равных нулю или бесконечности. \n
 * <b>14 вариант:</b> $$S=\sum_{k=3}^{n}\frac{(-2)^{k-1}}{(k-5)x^k}\prod_{i=1}^{k+7}\frac{i^3-27}{i-7}$$
 * Значение x и n вводить с клавиатуры \n
 */
void glazunova_3_1_middle() {
    double x;
    int n;

    cout << "Введите x: ";
    cin >> x;
    cout << "Введите n: ";
    cin >> n;

    double S = 0.0;

    for (int k = 3; k <= n; ++k) {
        if (k == 5 || x == 0) {
            cout << "Пропускаем слагаемое при k = " << k << " (знаменатель равен 0 или x = 0)" << std::endl;
            continue;
        }

        double product = 1.0;

        for (int i = 1; i <= k + 7; ++i) {
            if (i == 7) {
                cout << "Пропускаем множитель при i = 7 (знаменатель равен 0)" << std::endl;
                continue;
            }
            product *= (pow(i, 3) - 27.0) / (i - 7.0);
        }

        double term_part1 = pow(-2, k - 1) / ((k - 5) * pow(x, k));
        double term = term_part1 * product;


        S += term;
        cout << "Слагаемое при k = " << k << ": " << term << std::endl;
    }

    cout << "Итоговая сумма S = " << S << std::endl;
}

/**
 * @brief <b>3.2 БАЗОВЫЙ УРОВЕНЬ</b>\n
 * <b>Задание:</b> составить блок-схему алгоритма и программу согласно условию задачи.\n
 * <b>14 вариант:</b> Дано натуральное число n в диапазоне от 100 до 800. Определить
 * количество трёхзначных натуральных чисел больше n
 */
void glazunova_3_2_low() {
    int n;
    while (true) {
        cout << "Введите число n (от 100 до 800): ";
        cin >> n;
        if (n < 100 || n > 800) {
            cout << "Число выходит за диапазон (от 100 до 800). Попробуйте снова." << endl;
        } else { break; }
    }

    cout << "Существует еще " << 999 - n << " чисел больше n" << endl;
}

/**
 * @brief <b>3.2 СРЕДНИЙ УРОВЕНЬ</b>\n
 * <b>Задание:</b> составить блок-схему алгоритма и программу согласно заданию.\n
 * <b>14 вариант:</b> Даны числа от 1 до 1000 и число m. Вывести результат
 * целочисленного деления нечетных сотен на число m.
 */
void glazunova_3_2_middle() {
    int m;
    cout << "Введите число m: ";
    cin >> m;
    cout << "Вывод целочисленного деления нечетных сотен на число m" << endl;
    for (int i = 1; i < 10; i+=2) {
        cout << i << "00 / " << m << " = " << 100 * i / m << endl;
    }
}

/**
 * @brief <b>3.2 ВЫСОКИЙ УРОВЕНЬ</b>\n
 * <b>Задание:</b> составить блок-схему алгоритма и программу согласно заданию.\n
 * <b>14 вариант:</b> Вычислить y – первое из чисел sin(x), sin(sin(x)),
 * sin(sin(sin(x))), …, меньшее по модулю 10^-4.
 */
void glazunova_3_2_high() {
    cout << "Введите число x: ";
    double x;
    cin >> x;
    double y = sin(x);
    int iteration = 1;
    while (abs(y) >= 0.0001) {
        y = sin(y);
        iteration++;
        cout << "Итерация " << iteration << ": y = " << y << std::endl;
    }
    cout << "Первое число меньшее по модулю чем 10^-4: y = " << y << std::endl;
}

/**
 * @brief <b>3.4 ВЫСОКИЙ УРОВЕНЬ</b>\n
 * <b>Задание:</b> составить схему алгоритма и написать программу вычисления
 * таблицы значений функции f(x) на промежутке [x_n; x_k] с шагом h.
 */
void glazunova_3_4_high() {
    vector<double> x;

    for (double i = 1; i <= 2; i+=0.1) {
       x.push_back(cosh(i));
    }

    string resultMsg = "";
    for (double x1: x) {
        resultMsg += to_string(x1) + "\n";
    }
    cout << resultMsg << endl;
}
