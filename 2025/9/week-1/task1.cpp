#include <cmath>
#include <matplot/matplot.h>

using namespace std;

void glazunova_2_1_high();

void glazunova_2_2_middle();

void glazunova_2_2_high();

void glazunova_2_3_high();

int main() {
    bool exit = false;

    while (!exit) {
        cout << "Выберите задание из списка:\n"
                "1) Глазунова 2.1 высокий\n"
                "2) Глазунова 2.2 средний\n"
                "3) Глазунова 2.2 высокий\n"
                "4) Глазунова 2.3 высокий\n"
                "0) Выйти из программы\n"
                "Вы ввели: ";

        int taskNum;
        cin >> taskNum;

        switch (taskNum) {
            case 1:
                glazunova_2_1_high();
                break;
            case 2:
                glazunova_2_2_middle();
                break;
            case 3:
                glazunova_2_2_high();
                break;
            case 4:
                glazunova_2_3_high();
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

/*
 * Задание: записать логические выражения, используя условные операторы,
 * операции отношений и логические операции алгоритмического языка.
 */
void glazunova_2_1_high() {
    namespace plt = matplot;

    // Circle presets
    const double r = 1;
    const double xc = 0;
    const double yc = 0;
    double pointX, pointY;

    cout << "Введите координаты для точки:" << endl;
    cin >> pointX >> pointY;
    cin.ignore();

    cout << (pointY < 1 - abs(pointX) && pointY < 1 ||
        pow(r,2) == pow(pointX - xc, 2) + pow(pointY - yc, 2)
                 ? "Точка входит в область"
                 : "Точка не входит в область") << endl;

    cout << "Вывожу график..." << endl;

    // Clear plot window
    plt::cla();

    // Draw circle
    const auto circle = plt::fplot(
        [r, xc](const double x) { return r * cos(x) + xc; },
        [r, yc](const double y) { return r * sin(y) + yc; }
    );
    circle->line_width(2);
    circle->color("black");

    plt::hold(plt::on);

    // Draw triangle
    plt::vector_1d triX = {-1, 0, 1, -1};
    plt::vector_1d triY = {0, 1, 0, 0};
    auto triangle = plt::plot(triX, triY);

    // Setup triangle appearance
    triangle->line_width(2);
    triangle->color("red");
    triangle->fill(true).color("blue");

    // Add point
    auto point = plt::rectangle(pointX - 0.025, pointY - 0.025, 0.05, 0.05, 1.);
    point->fill(true).color("green");

    plt::grid(true);
    plt::axis(plt::equal);
    plt::wait();
}

/*
 * Ввести с клавиатуры три числа. Вывести на экран наименьшее из них.
 */
void glazunova_2_2_middle() {
    cout << "Введите 3 числа" << endl;
    vector<int> nums;
    int buffer;
    for (int i = 0; i < 3; i++) {
        cin >> buffer;
        nums.push_back(buffer);
    }
    cout << "Наименьшее число: " << ranges::min_element(nums)[0] << endl;
}

/*
 * Рейтинг бакалавра заочного отделения при поступлении в магистратуру
 * определяется средним баллом по диплому, умноженным на коэффициент
 * стажа работы по специальности, который равен: нет стажа – 1, меньше 2
 * лет – 13, от 2 до 5 лет – 16. Составить программу расчета рейтинга при
 * заданном среднем балле диплома (от 3 до 5) и вывести сообщение о
 * приеме в магистратуру при проходном балле 45.
 */
void glazunova_2_2_high() {
    double avgScore;
    while (true) {
        cout << "Введите средний балл по диплому: ";
        cin >> avgScore;
        if (avgScore > 5.0 || avgScore < 3.0) {
            cout << "Ошибка ввода: допустимые значения от 3.0 до 5.0" << endl;
            continue;
        }
        break;
    }

    int variant, k = 0;
    bool variantSelected = false;
    while (!variantSelected) {
        cout << "Выберите подходящий вариант. Какой у вас стаж работы по специальности?\n"
                "1) Нет стажа\n"
                "2) Стаж меньше 2 лет\n"
                "3) Стаж от 2 до 5 лет\n"
                "Вы ввели: ";
        cin >> variant;
        switch (variant) {
            case 1:
                k = 1;
                variantSelected = true;
                break;
            case 2:
                k = 13;
                variantSelected = true;
                break;
            case 3:
                k = 16;
                variantSelected = true;
                break;
            default:
                cout << "Такого варианта нет в списке. Попробуйте снова." << endl;
                break;
        }
    }

    cout << (k * avgScore > 45 ? "Вы прошли" : "Вы не прошли. Очень жаль ;(") << endl;
}

/*
 * Написать программу, которая по дате рождения (день d месяц n) определяет
 * знак Зодиака: с 22 марта по 21 апреля - Овен (4); с 22 апреля по 21
 * мая - Телец (5); с 22 мая по 21 июня - Близнецы (6); с 22 июня по 21 июля
 * - Рак (7); с 22 июля по 21 августа - Лев (8); с 22 августа по 21 сентября -
 * Дева (9); 22 сентября по 21 октября - Весы (10); с 22 октября по 21 ноября
 * - Скорпион (11); с 22 ноября по 21 декабря - Стрелец (12); с 22 декабря по
 * 21 января - Козерог (1); 22 января по 21 февраля - Водолей (2); с 22
 * февраля по 21 марта - Рыбы (3).
 */
void glazunova_2_3_high() {
    cout << "Введите день и месяц своей даты рождения" << endl;
    int d, n;

    while (true) {
        cout << "День: ";
        cin >> d;
        cout << "Месяц: ";
        cin >> n;

        if ((d > 31 || d < 1) ||
            ((n == 4 || n == 6 || n == 9 || n == 11) && d > 30) ||
            (n == 2 && d > 29)) {
            cout << "Введена несуществующая дата. Попробуйте снова." << endl;
            continue;
        }
        break;
    }

    string zz[] = {
        "Козерог",
        "Водолей",
        "Рыбы",
        "Овен",
        "Телец",
        "Близнецы",
        "Рак",
        "Лев",
        "Дева",
        "Весы",
        "Скорпион",
        "Стрелец"
    };

    string result;
    for (int i = 1; i <= 12; i++) {
        if (d > 22 && n == (i - 1 == 0 ? 12 : i - 1) || d < 21 && n == i) result = zz[i - 1];
    }
    cout << "Ваш знак зодиака: " << result << endl;
}
