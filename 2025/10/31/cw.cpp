//
// Created by Kuanysh Yabekov on 31.10.2025.
//

#include <iostream>

using namespace std;

class MyClass
{
    friend class MathFundamentals;
    friend void getDescription(string funcName, string description);
public:
    const double num1, num2;

    MyClass(double num1, double num2): num1(num1), num2(num2) {}
    ~MyClass()
    {
        // Деструктор класса
        std::cout << num1 << " " << num2 << endl;
    }
};

class MathFundamentals
{
public:
    double divide(MyClass &my_class)
    {
        return my_class.num1 / my_class.num2;
    }
};

void getDescription(MyClass &my_class)
{
    cout << "MyClass" << my_class.num1 << endl;
}

int main()
{
    auto myClass = MyClass(2.3, 5.2);
    cout << myClass.num1 << " " << myClass.num2 << endl;
    getDescription(myClass);
}