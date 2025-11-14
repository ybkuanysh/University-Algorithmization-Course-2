//
// Created by Kuanysh Yabekov on 24.10.2025.
//

#include <iostream>

class Animal
{
    public:
    std::string name;
    std::string color;
};

class Cat: public Animal
{
    public:
    Cat(const std::string& name, const std::string& color)
    {
        this->name = name;
        this->color = color;
    }
    Cat() {}

    static void basicGreeting()
    {
        std::cout << "meow\n";
    }
    void describe() const {
        std::cout << "meow, my name is " + name + " and my color is " + color + "\n";
    }
};

int main()
{
    auto murzik = Cat();

    murzik.name = "Murzik";
    murzik.color = "grey";
    murzik.basicGreeting();
    murzik.describe();
}