//
// Created by Kuanysh Yabekov on 14.11.2025.
//
#include <iostream>
using namespace std;

class BasicPaper
{
public:
    string paper_type = "Basic paper type";

    void virtual print_paper_type()
    {
        cout << "Это вывод виртуальной функции" << endl;
        cout << paper_type << endl;
    }
};

class Book : public virtual BasicPaper
{
};
class Magazine : public virtual BasicPaper
{
};

class Something : public Book, public Magazine
{
public:
    void print_paper_type() override
    {
        cout << "Вывод переопределенной функции" << endl;
    }
};

int main()
{
    auto object = Something();
    cout << "Paper type: " << object.paper_type << endl;
    object.print_paper_type();
}