#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

/**
 * @brief <b>4.1 Базовый уровень</b>\n
 * Ввести целочисленный массив, состоящий из 17 элементов. Заменить
 * элементы кратные трем на сумму нечетных по значению элементов.
 */
void glazunova_4_1_basic() {
    std::vector<int> arr(17);

    int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    std::uniform_int_distribution<> distrib(-100, 100); // Диапазон от -100 до 100

    // Генерация и вывод исходного вектора
    std::cout << "Исходный вектор (сгенерированный):\n";
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = distrib(generator);
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }

    // Расчет суммы нечетных по значению элементов
    long long odd_sum = 0;
    for (const auto& element : arr) {
        if (element % 2 != 0) {
            odd_sum += element;
        }
    }

    // Замена элементов, кратных трем
    for (auto& element : arr) {
        if (element % 3 == 0) {
            element = odd_sum;
        }
    }

    // Вывод измененного вектора
    std::cout << "\nИзмененный вектор:\n";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }
}

/**
 * @brief <b>4.1 Средний уровень</b>\n
 * Ввести массив, состоящий из 14 элементов действительного типа.
 * Поменять местами первую половину со второй. Определить количество
 * произведенных при этом перестановок.
 */
void glazunova_4_1_middle() {
    // Шаг 1: Инициализация вектора и генератора
    const int size = 14;
    std::vector<double> arr(size);

    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> distribution(-100.0, 100.0); // Используем double

    // Шаг 2: Генерация и вывод исходного массива
    std::cout << "Исходный массив:\n";
    for (int i = 0; i < size; ++i) {
        arr[i] = distribution(generator);
        std::cout << arr[i] << " ";
    }
    std::cout << "\n\n";

    // Шаг 3: Обмен первой половины со второй
    int half_size = size / 2;
    for (int i = 0; i < half_size; ++i) {
        // Меняем местами элемент из первой половины (i) с элементом из второй (i + half_size)
        std::swap(arr[i], arr[i + half_size]);
    }

    // Шаг 4: Подсчет перестановок
    int swaps_count = half_size;

    // Вывод измененного массива и количества перестановок
    std::cout << "Массив после обмена:\n";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n\nКоличество произведенных перестановок: " << swaps_count << std::endl;
}

/**
 * @brief <b>4.1 Высокий уровень</b>\n
 * Задан массив чисел в двоичной системе счисления. Упорядочить элементы
 * массива по убыванию. Определить сумму чисел.
 */
void glazunova_4_1_high() {
    // Настройка генератора случайных чисел
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    uniform_int_distribution<> binary_dist(0, 1);
    uniform_int_distribution<> length_dist(1, 8); // Длина двоичной строки от 1 до 8 бит

    const int array_size = 10;
    vector<string> binary_numbers(array_size);

    // Генерация массива двоичных чисел
    cout << "Исходный массив двоичных чисел:\n";
    for (int i = 0; i < array_size; ++i) {
        int length = length_dist(gen);
        string binary_str;
        for (int j = 0; j < length; ++j) {
            binary_str += std::to_string(binary_dist(gen));
        }
        binary_numbers[i] = binary_str;
        cout << binary_numbers[i] << " ";
    }
    cout << "\n\n";

    // Преобразование в десятичные числа и сортировка
    vector<int> decimal_numbers;
    for (const auto& bin_str : binary_numbers) {
        try {
            decimal_numbers.push_back(stoi(bin_str, nullptr, 2));
        } catch (const invalid_argument& e) {
            // Обработка возможной ошибки, хотя при генерации она маловероятна
            cerr << "Неверный формат двоичного числа: " << bin_str << endl;
        }
    }

    // Сортировка по убыванию
    sort(decimal_numbers.begin(), decimal_numbers.end(), greater<int>());

    // Вывод отсортированного массива в десятичном виде
    cout << "Отсортированный массив (по убыванию) в десятичном виде:\n";
    for (const auto& dec_num : decimal_numbers) {
        cout << dec_num << " ";
    }
    cout << "\n";

    // Вычисление суммы
    long long sum = accumulate(decimal_numbers.begin(), decimal_numbers.end(), 0LL);

    // Вывод суммы
    cout << "\nСумма всех чисел: " << sum << endl;
}

/**
 * @brief <b>СТАРТ ПРОГРАММЫ</b>\n
 */
int main() {
    bool exit = false;

    while (!exit) {
        cout << "\033[1mВыберите задачу из списка:\033[0m\n"
                "1) 4.1 Базовый уровень\n"
                "2) 4.1 Средний уровень\n"
                "3) 4.1 Высокий уровень\n"
                "0) Выйти\n"
                "\033[7mВы ввели: ";
        int taskNum;
        cin >> taskNum;
        cout << "\033[0m";
        system("clear");
        switch (taskNum) {
            case 1:
                glazunova_4_1_basic();
                break;
            case 2:
                glazunova_4_1_middle();
                break;
            case 3:
                glazunova_4_1_high();
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
