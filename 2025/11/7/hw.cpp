//
// Created by Kuanysh Yabekov on 07.11.2025.
//
#include <iostream>
using namespace std;

#include <string>
#include <sstream>
#include <ctime>
#include <iomanip> // Для форматирования вывода
#include <vector>

class Time {
    int hours_;
    int minutes_;
    int seconds_;

public:
    Time() : hours_(0), minutes_(0), seconds_(0) {}

    void inputTime() {
        std::string time_str;
        bool valid = false;

        while (!valid) {
            std::cout << "1. Введите значение времени в формате ЧЧ:ММ:СС (например, 14:30:00): ";
            std::cin >> time_str;

            // Попытка разобрать строку
            if (time_str.length() == 8 && time_str[2] == ':' && time_str[5] == ':') {
                try {
                    hours_ = std::stoi(time_str.substr(0, 2));
                    minutes_ = std::stoi(time_str.substr(3, 2));
                    seconds_ = std::stoi(time_str.substr(6, 2));

                    // Проверка диапазонов
                    if (hours_ >= 0 && hours_ <= 23 &&
                        minutes_ >= 0 && minutes_ <= 59 &&
                        seconds_ >= 0 && seconds_ <= 59) {
                        valid = true;
                    } else {
                        std::cout << "Ошибка: Неверный диапазон часов (00-23), минут (00-59) или секунд (00-59).\n";
                    }
                } catch (const std::exception& e) {
                    std::cout << "Ошибка: Неверный формат ввода.\n";
                }
            } else {
                std::cout << "Ошибка: Неверный формат ввода. Используйте ЧЧ:ММ:СС.\n";
            }
        }
    }

    void displayFormattedTime() const {
        std::cout << "   Введенное время (ЧЧ:ММ:СС): "
                  << std::setfill('0') << std::setw(2) << hours_ << ":"
                  << std::setfill('0') << std::setw(2) << minutes_ << ":"
                  << std::setfill('0') << std::setw(2) << seconds_ << "\n";
    }
};

class ElectionController {
    std::tm voting_date_tm_ = {};
    std::time_t voting_time_t_ = (std::time_t)-1;

    void inputVotingDate() {
        std::string date_str;
        bool valid = false;

        while (!valid) {
            std::cout << "2. Введите дату голосования в формате ДДММГГГГ (например, 07112025): ";
            std::cin >> date_str;

            if (date_str.length() == 8) {
                try {
                    int day = std::stoi(date_str.substr(0, 2));
                    int month = std::stoi(date_str.substr(2, 2));
                    int year = std::stoi(date_str.substr(4, 4));

                    // Установка полей std::tm
                    voting_date_tm_.tm_year = year - 1900;
                    voting_date_tm_.tm_mon = month - 1;
                    voting_date_tm_.tm_mday = day;
                    voting_date_tm_.tm_hour = 0;
                    voting_date_tm_.tm_min = 0;
                    voting_date_tm_.tm_sec = 0;
                    voting_date_tm_.tm_isdst = -1;

                    // Проверка на корректность даты с помощью mktime
                    std::time_t time_check = std::mktime(&voting_date_tm_);

                    if (time_check != (std::time_t)-1) {
                        // Проверяем, что дата не "переехала" после нормализации
                        if (voting_date_tm_.tm_mday == day && (voting_date_tm_.tm_mon + 1) == month && (voting_date_tm_.tm_year + 1900) == year) {
                            voting_time_t_ = time_check; // Сохраняем time_t для расчетов
                            valid = true;
                        } else {
                            std::cout << "Ошибка: Введена невалидная дата (например, несуществующий день).\n";
                        }
                    } else {
                        std::cout << "Ошибка: Введена невалидная дата.\n";
                    }

                } catch (const std::exception& e) {
                    std::cout << "Ошибка: Неверный формат ввода.\n";
                }
            } else {
                std::cout << "Ошибка: Неверный формат ввода. Используйте ДДММГГГГ (8 цифр).\n";
            }
        }
    }

public:
    ElectionController() {
        inputVotingDate();
    }

    void runCampaignControl() const {
        if (voting_time_t_ == (std::time_t)-1) {
            std::cerr << "Невозможно выполнить расчет: некорректная дата голосования.\n";
            return;
        }

        // 1. Расчет даты окончания агитации
        // Агитация прекращается в 00:00:00 за сутки до дня голосования.
        // Отнимаем ровно 24 часа (86400 секунд) от 00:00:00 дня голосования.
        const std::time_t AGITATION_CEASE_TIME_T = voting_time_t_;
        const std::time_t AGITATION_END_DAY_START_T = voting_time_t_ - 24 * 60 * 60;

        // Преобразуем time_t в tm для форматирования даты окончания агитации
        std::tm* agitation_end_tm_ptr = std::localtime(&AGITATION_END_DAY_START_T);
        if (agitation_end_tm_ptr == nullptr) {
            std::cerr << "Ошибка: Невозможно получить дату окончания агитации.\n";
            return;
        }

        // 2. Расчет оставшихся дней

        // Получаем текущую дату и время
        std::time_t current_time_t = std::time(nullptr);
        std::tm* current_tm_ptr = std::localtime(&current_time_t);

        // Обнуляем время текущей даты для сравнения "от начала дня" до "начала дня"
        std::tm current_day_start_tm = *current_tm_ptr;
        current_day_start_tm.tm_hour = 0;
        current_day_start_tm.tm_min = 0;
        current_day_start_tm.tm_sec = 0;
        std::time_t current_day_start_t = std::mktime(&current_day_start_tm);

        // Разница в секундах
        double diff_seconds = std::difftime(voting_time_t_, current_day_start_t);

        // Разница в днях
        const double SECONDS_IN_DAY = 24.0 * 60.0 * 60.0;
        long long days_remaining = static_cast<long long>(diff_seconds / SECONDS_IN_DAY);

        // 3. Вывод результатов
        std::cout << "\n--- Отчет о контроле предвыборной кампании ---\n";

        std::cout << "   Дата голосования: "
                  << std::put_time(&voting_date_tm_, "%d.%m.%Y") << "\n";

        if (days_remaining < 0) {
            std::cout << "   Голосование уже прошло: " << std::abs(days_remaining) << " дней назад.\n";
        } else if (days_remaining == 0) {
            std::cout << "   Голосование проходит сегодня!\n";
        } else {
            std::cout << "   Количество оставшихся дней до начала голосования: **" << days_remaining << "**\n";
        }

        std::cout << "   Дата окончания предвыборной агитации (00:00:00 дня, предшествующего голосованию):\n";
        std::cout << "   -> **" << std::put_time(agitation_end_tm_ptr, "%d.%m.%Y") << "**\n";

        std::cout << "--------------------------------------------------\n";
    }
};

void glazunova_9_basic() {
    std::cout << "====================================================\n";
    std::cout << "--- Задание 14 (Классы) ---\n";

    // 1. Выполнение Пункта 1
    Time time_input;
    time_input.inputTime();
    time_input.displayFormattedTime();

    // 2. Выполнение Пункта 2
    ElectionController controller;
    controller.runCampaignControl();
}

/**
 * @brief Проверяет, является ли год високосным.
 * * Правило високосного года (григорианский календарь):
 * Год является високосным, если он кратен 4,
 * НО не кратен 100,
 * ИЛИ кратен 400.
 * * @param year Год (например, 2024).
 * @return true, если год високосный.
 */
bool is_leap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * @brief Преобразует числовое представление дня недели в строку.
 * * В C++ (std::tm): 0 - Воскресенье, 1 - Понедельник, ..., 6 - Суббота.
 * По условию задачи: 1 - Понедельник, ..., 7 - Воскресенье.
 * * @param wday Номер дня недели из std::tm (0-6).
 * @return Соответствующий номер по условию (1-7).
 */
int get_wday_number(int wday) {
    if (wday == 0) {
        return 7; // Воскресенье -> 7
    } else {
        return wday; // Понедельник-Суббота -> 1-6
    }
}

class Student {
    int id_;
    std::string full_name_;
    int day_of_birth_;
    int month_of_birth_;
    int year_of_birth_;
    int age_;

    std::tm birth_tm_ = {};

    void calculate_age() {
        std::time_t now = std::time(nullptr);
        std::tm* now_tm = std::localtime(&now);

        age_ = now_tm->tm_year - birth_tm_.tm_year;

        if (now_tm->tm_mon < birth_tm_.tm_mon ||
            (now_tm->tm_mon == birth_tm_.tm_mon && now_tm->tm_mday < birth_tm_.tm_mday)) {
            age_--;
        }
    }

    bool setup_birth_tm() {
        birth_tm_.tm_year = year_of_birth_ - 1900;
        birth_tm_.tm_mon = month_of_birth_ - 1;
        birth_tm_.tm_mday = day_of_birth_;

        birth_tm_.tm_hour = 0;
        birth_tm_.tm_min = 0;
        birth_tm_.tm_sec = 0;
        birth_tm_.tm_isdst = -1;

        std::time_t time_check = std::mktime(&birth_tm_);

        if (time_check == (std::time_t)-1) {
            return false;
        }

        if (birth_tm_.tm_mday != day_of_birth_ ||
            (birth_tm_.tm_mon + 1) != month_of_birth_ ||
            (birth_tm_.tm_year + 1900) != year_of_birth_) {
            return false;
        }

        calculate_age();
        return true;
    }

public:
    Student(int id, const std::string& fio, int day, int month, int year)
        : id_(id), full_name_(fio), day_of_birth_(day), month_of_birth_(month), year_of_birth_(year), age_(0) {
        if (!setup_birth_tm()) {
            std::cerr << "Предупреждение: Дата рождения для " << full_name_ << " недействительна. Расчеты могут быть неточными.\n";
        }
    }

    void print_full_info() const {
        std::cout << "№" << id_ << ". " << full_name_ << ", Возраст: " << age_ << " лет.\n";

        int wday = birth_tm_.tm_wday;
        int user_wday = get_wday_number(wday);

        std::cout << "   Дата рождения: "
                  << std::put_time(&birth_tm_, "%d.%m.%Y")
                  << " | День недели рождения (1=ПН): " << user_wday << "\n";
    }

    bool born_in_leap_year() const {
        return is_leap(year_of_birth_);
    }

    const std::string& get_full_name() const { return full_name_; }
    int get_year_of_birth() const { return year_of_birth_; }
};

std::vector<Student> input_student_data() {
    std::vector<Student> group;
    int num_students;

    std::cout << "Введите количество студентов в группе: ";
    if (!(std::cin >> num_students) || num_students <= 0) {
        std::cerr << "Неверный ввод. Установлено 3 студента по умолчанию.\n";
        num_students = 3;
    }

    // Очистка буфера после ввода числа
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "--- Ввод данных студентов ---\n";
    for (int i = 0; i < num_students; ++i) {
        std::string fio, date_str;
        int day, month, year;

        std::cout << "\nСтудент №" << i + 1 << ":\n";

        std::cout << "   ФИО: ";
        std::getline(std::cin, fio);

        // Ввод даты рождения в формате ДДММГГГГ
        while (true) {
            std::cout << "   Дата рождения (ДДММГГГГ): ";
            std::cin >> date_str;

            if (date_str.length() == 8) {
                try {
                    day = std::stoi(date_str.substr(0, 2));
                    month = std::stoi(date_str.substr(2, 2));
                    year = std::stoi(date_str.substr(4, 4));

                    // Простая проверка диапазонов (более детальная проверка в конструкторе)
                    if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900 && year <= 2025) {
                        break;
                    }
                } catch (...) {
                    // Игнорируем и просим повторить
                }
            }
            std::cout << "   Ошибка: Неверный формат или диапазон даты. Повторите.\n";
        }

        // Очистка буфера после ввода даты
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        group.emplace_back(i + 1, fio, day, month, year);
    }

    return group;
}



void glazunova_9_middle() {
    std::cout << "====================================================\n";
    std::cout << "--- Задание 14: Ввод и обработка данных студентов ---\n";

    std::vector<Student> students = input_student_data();

    if (students.empty()) {
        std::cout << "Список студентов пуст. Выполнение задания невозможно.\n";
        return;
    }

    std::cout << "\n-----------------------------------------------------\n";

    std::cout << "Полная дата рождения и день недели:\n";
    for (const auto& student : students) {
        student.print_full_info();
    }

    std::cout << "\n-----------------------------------------------------\n";

    std::cout << "Список студентов, родившихся в високосный год:\n";
    bool found_leap = false;

    for (const auto& student : students) {
        if (student.born_in_leap_year()) {
            std::cout << "* " << student.get_full_name()
                      << " (Год: " << student.get_year_of_birth() << ")\n";
            found_leap = true;
        }
    }

    if (!found_leap) {
        std::cout << "   (Введенные студенты не родились в високосный год.)\n";
    }

    std::cout << "====================================================\n";
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
            "1) 9 Базовый уровень\n"
            "2) 9 Средний уровень\n"
            "0) Выйти\n"
            "\033[7mВы ввели: ";
        int taskNum;
        cin >> taskNum;
        cout << "\033[0m";
        system("clear");
        switch (taskNum)
        {
        case 1:
            glazunova_9_basic();
            waitForContinue();
            break;
        case 2:
            glazunova_9_middle();
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
