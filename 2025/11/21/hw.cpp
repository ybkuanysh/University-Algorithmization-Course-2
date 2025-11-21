//
// Created by Kuanysh Yabekov on 21.11.2025.
//

#include <iostream>
#include <cmath>
#include <random>

using namespace std;


/**
 * Армия:
 * - вид войск;
 * - численность (тыс человек):
 * - вооруженность (баллы - число).
 * Q=0,3·численность+0,7·вооруженность
 */
class Army
{
public:
    string type_of_forces;
    int count_of_warriors = 0;
    double armament = 0.0;

    Army(string s, int c, double a) : type_of_forces(std::move(s)), count_of_warriors(c), armament(a) {}
    double process() const { return 0.3 * count_of_warriors + 0.7 * armament; }
    void description() const
    {
        cout << "Объект класса Army\nВид войск: " << type_of_forces
        << "\nЧисленность: " << count_of_warriors
        << "\nВооруженность: " << armament << endl;
    }
};

/**
 * P: опыт (число месяцев, на протяжении которых армия вела боевые действия)
 * Qp = Q · (Р+1)
 */
class Second : public Army
{
    double skill = 0.0;
    public:
    Second(string s, int c, double a, double sk) : Army(s, c, a), skill(sk) {}
    double process() const
    {
        double Q = Army::process();
        return Q * (skill + 1);
    }
    void description() const
    {
        cout << "Объект класса Second\nВид войск: " << type_of_forces
        << "\nЧисленность: " << count_of_warriors
        << "\nВооруженность: " << armament
        << "\nОпыт: " << skill << endl;
    }
};

void glazunova_11_3_basic()
{
    Army firstArmy {"Сухопутные", 12, 3.4};
    Army* army = &firstArmy;
    army->description();
    auto result= army->process();
    cout << "Качество объекта: " << result << endl << endl;

    Second secondObj {"Воздушные", 12, 3.4, 10};
    secondObj.description();
    result = secondObj.process();
    cout << "Качество объекта: " << result << endl;
}

class Rectangle
{
public:
    int a, b = 0;
    Rectangle(int a, int b) : a(a), b(b) {}
    virtual double perimeter() { return 2 * (a + b); }
    virtual double area() { return a * b; }
    virtual void multiply_by_2() { a *= 2; b *= 2; }
    virtual void information()
    {
        int p = perimeter();
        int q = area();
        cout << "Информация о прямоугольнике\nA: " << a << "\nB: " << b
        << "\nПериметр: " << p << "\nПлощадь: " << q << endl;
    }
};

class RoundedRectangle: public Rectangle
{
public:
    int r = 0;
    RoundedRectangle(int a, int b, int r) : Rectangle(a, b), r(r) {}
    double perimeter() override
    {
        const double p = Rectangle::perimeter();
        return p - 8 * r + 2 * M_PI * r;
    }
    double area() override
    {
        const double S = Rectangle::area();
        return S - 4 * pow(r, 2) + M_PI * pow(r, 2);
    }
    void multiply_by_2() override
    {
        Rectangle::multiply_by_2();
        r *= 2;
    }
    void information() override
    {
        Rectangle::information();
        cout << "Радиус скругления: " << r << endl;
    }
};

void glazunova_11_3_middle()
{
    Rectangle rect {2, 3};
    rect.information();
    cout << endl;
    rect.multiply_by_2();
    rect.information();

    cout << endl;

    RoundedRectangle r_rect {2, 3, 1};
    r_rect.multiply_by_2();
    r_rect.information();
}

class Person
{
public:
    string name;
    int age;
    int experience;
    Person(string n, int a, int e) : name(std::move(n)), age(a) ,experience(e) {}
    virtual bool shoot() const = 0;
    virtual string type() const = 0;
};

bool getBoolWithProbability(double probability) {
    if (probability < 0.0 || probability > 1.0) {
        throw std::out_of_range("Вероятность должна быть в диапазоне [0.0, 1.0]");
    }
    static random_device rd;
    static mt19937 generator(rd());
    static std::uniform_real_distribution<> distribution(0.0, 1.0);
    return distribution(generator) < probability;
}

class Newbie: public Person
{
public:
    Newbie(string n, int a, int e) : Person(n, a, e) {}
    // 0,01 * стаж обучения
    bool shoot() const override { return getBoolWithProbability(0.01 * experience); }
    string type() const override { return "новичок"; }
};

class Experienced : public Person
{
public:
    Experienced(string n, int a, int e) : Person(n, a, e) {}
    // 0,05 * стаж обучения
    bool shoot() const override { return getBoolWithProbability(0.05 * experience); }
    string type() const override { return "опытный"; }
};

class Veteran: public Person
{
public:
    Veteran(string n, int a, int e) : Person(n, a, e) {}
    // 0,9 – 0,01 * возраст
    bool shoot() const override { return getBoolWithProbability(0.9 - 0.01 * age); }
    string type() const override { return "ветеран"; }
};

void glazunova_11_3_high()
{
    vector<Person*> arr {
        new Newbie("Алексей", 23, 1),
        new Experienced("Алибек", 45, 10),
        new Veteran("Кирилл", 54, 20),
        new Experienced("Ернияз", 27, 9),
        new Newbie("Василий", 34, 2),
        new Experienced("Темерлан", 30, 6),
        new Veteran("Руслан", 42, 22)
    };

    for (auto p : arr)
    {
        cout << p->type() << " имя: " << p->name << "    возраст: " << p->age << "    стаж: " << p->experience << "    попал: " << p->shoot() << endl;
    }
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
            "1) 11.3 Базовый уровень\n"
            "2) 11.3 Средний уровень\n"
            "3) 11.3 Высокий уровень\n"
            "0) Выйти\n"
            "\033[7mВы ввели: ";
        int taskNum;
        cin >> taskNum;
        cout << "\033[0m";
        system("clear");
        switch (taskNum)
        {
        case 1:
            glazunova_11_3_basic();
            waitForContinue();
            break;
        case 2:
            glazunova_11_3_middle();
            waitForContinue();
            break;
        case 3:
            glazunova_11_3_high();
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
