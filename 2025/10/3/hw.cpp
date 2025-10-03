#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/**
 * @brief <b>7.2 Базовый уровень</b>\n
 * Задание: Написать программу согласно заданию\n
 * Вариант 14: В заданной строке посчитать количество точек и запятых
 */
void glazunova_7_2_basic() {
    std::string text = "Это строка с точками, запятыми, и другими символами. Вот еще: один.";
    int dots_count = 0;
    int commas_count = 0;

    // --- Метод 1: Использование std::count (Рекомендуется для C++) ---
    dots_count = ranges::count(text, '.');
    commas_count = ranges::count(text, ',');

    /*
    // --- Метод 2: Ручной подсчет в цикле (Классический подход) ---
    for (char c : text) {
        if (c == '.') {
            dots_count++;
        } else if (c == ',') {
            commas_count++;
        }
    }
    */

    std::cout << "--- Задание 7.2 (Базовый) ---" << std::endl;
    std::cout << "Исходная строка: \"" << text << "\"" << std::endl;
    std::cout << "Количество точек: " << dots_count << std::endl;
    std::cout << "Количество запятых: " << commas_count << std::endl;
}

/**
 * @brief <b>7.2 Средний уровень</b>\n
 * Задание: написать программу согласно заданию\n
 * Вариант 14: В заданной строке удалить первый символ «», который найдется в строке
 */
void glazunova_7_2_middle() {
    std::string text = "Это строка со скобками, (которые нужно) удалить.";
    char char_to_remove = '(';

    // Находим позицию первого вхождения символа
    size_t pos = text.find(char_to_remove);

    std::cout << "--- Задание 7.2 (Средний) ---" << std::endl;
    std::cout << "Исходная строка: \"" << text << "\"" << std::endl;
    std::cout << "Символ для удаления: '" << char_to_remove << "'" << std::endl;

    if (pos != std::string::npos) {
        // Если символ найден, удаляем 1 символ с этой позиции
        text.erase(pos, 1);
        std::cout << "Результат:       \"" << text << "\"" << std::endl;
    } else {
        std::cout << "Результат: Символ '" << char_to_remove << "' не найден. Строка не изменена." << std::endl;
    }
}


/**
 * @brief <b>7.2 Высокий уровень</b>\n
 * Задание: написать программу согласно заданию\n
 * Вариант 4: В заданной строке заменить каждый символ «*» числом,\n
 * соответствующим номеру по порядку вхождения этого символа в строку
 */
void glazunova_7_2_high() {
    std::string text = "Это* тестовая* строка* с несколькими* звездочками.";
    int counter = 0; // Счетчик вхождений символа '*'
    char target_char = '*';

    std::cout << "--- Задание 7.2 (Высокий) ---" << std::endl;
    std::cout << "Исходная строка: \"" << text << "\"" << std::endl;

    // Проходим по строке в цикле
    for (size_t i = 0; i < text.length(); ++i) {
        if (text[i] == target_char) {
            counter++;

            // Преобразуем текущий счетчик в строку
            std::string replacement = std::to_string(counter);

            // Заменяем '*' на число:
            // 1. Удаляем 'target_char' (1 символ) с позиции i
            text.erase(i, 1);

            // 2. Вставляем строку 'replacement' на ту же позицию i
            text.insert(i, replacement);

            // 3. Сдвигаем счетчик цикла 'i', чтобы пропустить только что вставленное число
            // (длина вставленной строки - 1, т.к. 1 символ мы уже удалили)
            i += replacement.length() - 1;
        }
    }

    std::cout << "Результат:       \"" << text << "\"" << std::endl;
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
                "1) 7.2 Базовый уровень\n"
                "2) 7.2 Средний уровень\n"
                "3) 7.2 Высокий уровень\n"
                "0) Выйти\n"
                "\033[7mВы ввели: ";
        int taskNum;
        cin >> taskNum;
        cout << "\033[0m";
        system("clear");
        switch (taskNum) {
            case 1:
                glazunova_7_2_basic();
                waitForContinue();
                break;
            case 2:
                glazunova_7_2_middle();
                waitForContinue();
                break;
            case 3:
                glazunova_7_2_high();
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
