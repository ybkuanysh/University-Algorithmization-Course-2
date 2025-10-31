//
// Created by Kuanysh Yabekov on 30.10.2025.
//
#include <iostream>
class Task14
{
public:
    double num1;
    double num2;

    Task14(double num1, double num2)
    {
        this->num1 = num1;
        this->num2 = num2;
    }

    static std::string description()
    {
        return "Это класс, написанный по индивидуальному варианту 14";
    }

    double sqrtOfProduct()
    {
        return sqrt(num1 * num2);
    }
};

class Task28
{
public:
    double u;
    double r;

    Task28(double volts, double resistance)
    {
        this->u = volts;
        this->r = resistance;
    }

    static std::string description()
    {
        return "Это класс, написанный по индивидуальному варианту 28."
               " Данный класс высчитывает силу тока по введенным данным";
    }

    double computeCurrent()
    {
        return u / r;
    }
};

int main()
{
    auto task14 = Task14(2.3, 4.5);
    std::cout << Task14::description() << std::endl;
    std::cout << task14.sqrtOfProduct() << std::endl;

    auto task28 = Task28(12, 1000);
    std::cout << Task28::description() << std::endl;
    std::cout << task28.computeCurrent() << " Ампер" << std::endl;
}