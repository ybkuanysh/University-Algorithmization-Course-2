#include <iostream>
#include <chrono>

using namespace std;

/**
 * 11.1 СРЕДНИЙ УРОВЕНЬ
 * Задание: создать класс с полями, указанными в индивидуальном задании.\n
 * Реализовать в классе методы:
 * - конструктор по умолчанию
 * - конструктор перегрузки с параметрами
 * - деструктор для освобождения памяти (с сообщением об уничтожении объекта)
 * - функция обработки данных (1 и 2), указанные в индивидуальном задании
 * - функцию формирования строки информации об объекте
 */
class Book
{
    chrono::year_month_day date_publish_;
public:
    string name_, author_;
    Book() : name_(), author_(), date_publish_() {}

    Book(
        string name,
        string author,
        const chrono::year y,
        const chrono::month m,
        const chrono::day d
        ) : name_(std::move(name)),
    author_(std::move(author)),
    date_publish_(y/m/d)
    {
        if (!date_publish_.ok())
        {
            throw invalid_argument("Некорректная дата рождения");
        }
    }

    void print_years_left_from_publish() const
    {
        auto years_left = get_years_left();
        cout << "С даты публикации прошло " << years_left << " лет" << endl;
    }

    void print_days_left_from_publish() const
    {
        using namespace chrono;
        year_month_day today = floor<days>(system_clock::now());
        auto days_left = static_cast<sys_days>(today) - static_cast<sys_days>(date_publish_);
        cout << "С даты публикации прошло " << days_left.count() << " дней" << endl;
    }

    int get_years_left() const
    {
        chrono::year_month_day today = floor<chrono::days>(chrono::system_clock::now());
        return (int) today.year() - (int) date_publish_.year();
    }
};

/**
 * Задание: для класса, созданного в предыдущем задании создать класс-потомок
 * с дополнительным полем, указанным в индивидуальном задании.
 * Реализовать в классе-потомке методы:
 * - конструктор
 * - функцию обработки данных
 */
class Parent
{
public:
    double x, y;
    Parent() : x(0), y(0) {}
    Parent(const double x, const double y) : x(x), y(y) {}
};

class Child : public Parent
{
public:
    double z;
    Child(): z(0) {}
    Child(const double x, const double y, const double z) : Parent(x, y), z(z) {}

    void process_and_print()
    {
        double result = sqrt(x*y + z);
        cout << "Результат вычисления: " << result << endl;
    }
};

class BookShop: public Book
{
    double price_;
public:
    BookShop(): price_(0) {}
    BookShop(
        string name,
        string author,
        chrono::year y,
        chrono::month m,
        chrono::day d,
        double price
        ) : Book(
            std::move(name),
            std::move(author),
            y, m,d), price_(price)
    {
        if (get_years_left() > 5) {
            price_ = price * 0.8;
            cout << "Книге уже больше 5 лет с даты выпуска, цена снижена до: " << price_ << endl;
        }
    }

    void print_description() const
    {
        cout << "Данные о данном объекте класса BookShop:" << endl
        << "Название: " << name_ << endl
        << "Автор: " << author_ << endl
        << "Прошло лет с публикации: " << get_years_left() << endl;
    }
};

int main()
{
    cout << "11.1 СРЕДНИЙ УРОВЕНЬ:" << endl;
    using namespace chrono;
    Book book1 = Book("Book 1", "Author 1", 2023y, November, 10d);
    book1.print_years_left_from_publish();
    book1.print_days_left_from_publish();

    cout << "11.2 БАЗОВЫЙ УРОВЕНЬ:" << endl;
    Child child1 = Child(2, 3, 11);
    child1.process_and_print();

    cout << "11.2 СРЕДНИЙ УРОВЕНЬ:" << endl;
    BookShop bookShop1 = BookShop(
        "Book 2",
        "Author 2",
        2018y, October, 3d,
        1000);
    bookShop1.print_description();
}