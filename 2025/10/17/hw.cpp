//
// Created by Kuanysh Yabekov on 16.10.2025.
//

#include <iostream>
#include <forward_list>
#include <iomanip>

using namespace std;

/**
 * @brief <b>6.3 Базовый уровень</b>\n
 * Задание: написать программу в соответствии с индивидуальным заданием.\n
 * Вариант 14: Создать линейный однонаправленный список из вещественных чисел.
 * Удалить из списка элемент перед положительным первым элементом.
 */
void glazunova_6_3_basic()
{
    forward_list list = {-5.2, -10.5, 1.0, 3.14, 9.9, -1.0, 7.77};

    cout << "Исходный список:" << endl;
    for (const auto& item : list)
    {
        cout << fixed << setprecision(2) << item << " ";
    }
    cout << "\n----------------------------------------" << endl;

    auto prev_it = list.before_begin();

    auto current_it = list.begin();

    auto it_to_erase_after = list.end();

    bool found_positive = false;
    double first_positive_value = 0.0;
    int counter = 0;

    while (current_it != list.end())
    {
        if (*current_it > 0)
        {
            it_to_erase_after = prev_it;
            first_positive_value = *current_it;
            found_positive = true;
            break;
        }
        if (counter > 0) ++prev_it;
        ++current_it;
        ++counter;
    }

    if (found_positive)
    {
        if (next(it_to_erase_after) == list.before_begin())
        {
            cout << "Первый положительный элемент ("
                << fixed << setprecision(2) << first_positive_value
                << ") является первым в списке. Невозможно удалить элемент перед ним."
                << endl;
        }
        else
        {
            double removed_value = *next(it_to_erase_after);

            list.erase_after(it_to_erase_after);

            cout << "Первый положительный элемент: "
                << fixed << setprecision(2) << first_positive_value
                << endl;
            cout << "Удален элемент, предшествующий ему. Удаленное значение: "
                << fixed << setprecision(2) << removed_value
                << endl;
        }
    }
    else
    {
        cout << "В списке не найдено положительных элементов. Удаление не выполнено." << endl;
    }

    // ----------------------------------------------------------------------

    // 4. Вывод измененного списка
    cout << "\nСписок после операции:" << endl;
    if (list.empty())
    {
        cout << "Список пуст." << endl;
    }
    else
    {
        for (const auto& item : list)
        {
            cout << fixed << setprecision(2) << item << " ";
        }
        cout << endl;
    }
}

/**
 * @brief <b>6.3 Средний уровень</b>\n
 * Задание: написать программу в соответствии с индивидуальным заданием.\n
 * Вариант 14: Создать линейный однонаправленный список из вещественных чисел.
 * Вставить первый положительный элемент списка после каждого отрицательного
 * числа (если такого нет, оставить список без изменения).
 */
void glazunova_6_3_middle()
{
    forward_list list = {-10.5, 5.2, -0.1, 0.0, -3.14, 9.9, -7.77};

    cout << "Исходный список:" << endl;
    for (const auto& item : list)
    {
        cout << fixed << setprecision(2) << item << " ";
    }
    cout << "\n----------------------------------------" << endl;

    auto first_positive_it = find_if(list.begin(), list.end(),
                                          [](double n) { return n > 0; });

    if (first_positive_it == list.end())
    {
        cout << "В списке не найдено положительных элементов. Список остается без изменения." << endl;
        cout << "----------------------------------------" << endl;
        return;
    }

    const double value_to_insert = *first_positive_it;
    cout << "Первый положительный элемент (для вставки): "
        << fixed << setprecision(2) << value_to_insert << endl;

    auto current_it = list.begin();

    while (current_it != list.end())
    {
        if (*current_it < 0)
        {
            current_it = list.insert_after(current_it, value_to_insert);
        }
        ++current_it;
    }

    cout << "\nСписок после операции:" << endl;
    for (const auto& item : list)
    {
        cout << fixed << setprecision(2) << item << " ";
    }
    cout << endl;
}

/**
 * @brief <b>6.3 Высокий уровень</b>\n
 * Задание: написать программу в соответствии с индивидуальным заданием.\n
 * Вариант 14: Даны указатели P1 и P2 на первый и последний элементы непустого
 * двусвязного списка, содержащего четное количество элементов. Преобразовать
 * список в два циклических списка, первый из которых содержит первую половину
 * элементов исходного списка, а второй — вторую половину. Вывести указатели PA
 * и PB на два средних элемента исходного списка (элемент с адресом PA должен
 * входить в первый циклический список, а элемент с адресом PB — во второй).
 * Операции выделения и освобождения памяти не использовать.
 */
void glazunova_6_3_high()
{
}

void waitForContinue()
{
    cin.ignore();
    cout << "Для продолжения нажмите Enter." << endl;
    cin.get();
    system("clear");
}

int main()
{
    bool exit = false;

    system("clear");

    while (!exit)
    {
        cout << "\033[1mВыберите задачу из списка:\033[0m\n"
            "1) 6.3 Базовый уровень\n"
            "2) 6.3 Средний уровень\n"
            "3) 6.3 Высокий уровень\n"
            "0) Выйти\n"
            "\033[7mВы ввели: ";
        int taskNum;
        cin >> taskNum;
        cout << "\033[0m";
        system("clear");
        switch (taskNum)
        {
        case 1:
            glazunova_6_3_basic();
            waitForContinue();
            break;
        case 2:
            glazunova_6_3_middle();
            waitForContinue();
            break;
        case 3:
            glazunova_6_3_high();
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
