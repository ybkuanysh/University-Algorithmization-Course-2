//
// Created by Kuanysh Yabekov on 12.12.2025.
//

#include <iostream>
#include <vector>

using namespace std;

/// Златопольский 13.29
enum CarType
{
    PassengerCar,
    TruckCar
};
class Car
{
public:
    double price;
    CarType type;
    Car() : price(0), type(PassengerCar) {}
    Car(const double p, const CarType t) : price(p), type(t) {}
    static vector<Car> mock()
    {
        return {
            // Легковые авто (PassengerCar)
            Car(15230.50, PassengerCar),
            Car(24999.00, PassengerCar),
            Car(12875.99, PassengerCar),
            Car(55000.00, PassengerCar),
            Car(18045.20, PassengerCar),
            Car(31200.75, PassengerCar),
            Car(9500.00, PassengerCar),

            // Грузовые авто (TruckCar)
            Car(85670.30, TruckCar),
            Car(120900.00, TruckCar),
            Car(45320.60, TruckCar),
            Car(77123.45, TruckCar),
            Car(150000.00, TruckCar),
            Car(62500.99, TruckCar),
            Car(98765.40, TruckCar),
            Car(110000.00, TruckCar)
        };
    }
};
void Exercise_13_29()
{
    vector<Car> carsList = Car::mock();
    double totalPrice = 0;
    int counter = 0;
    for (auto car : carsList)
    { if (car.type == PassengerCar) { totalPrice += car.price; counter++; } }
    cout << "Средняя цена: " << totalPrice / counter << " среди " << counter << " машин." << endl;
}

/// Златопольский 13.44
class Game
{
public:
    int goals_for;
    int goals_against;
    Game() : goals_for(0), goals_against(0) {}
    Game(const int f, const int a) : goals_for(f), goals_against(a) {}
    void game_result() const
    { cout << (goals_for == goals_against ? "Ничья" : goals_for > goals_against ? "Победа" : "Проигрыш") << endl; }
    static void count_wins(const vector<Game>& games)
    {
        int counter = 0;
        for (const auto game : games) { game.goals_for > game.goals_against ? counter++ : counter; }
        cout << "Количество побед команды: " << counter << endl;
    }
    static void count_wins_losses(const vector<Game>& games)
    {
        count_wins(games);
        int counter = 0;
        for (const auto game : games) { game.goals_for < game.goals_against ? counter++ : counter; }
        cout << "Количество проигрышей команды: " << counter << endl;
    }
    static void count_wins_losses_draws(const vector<Game>& games)
    {
        count_wins_losses(games);
        int counter = 0;
        for (const auto game : games) { game.goals_for == game.goals_against ? counter++ : counter; }
        cout << "Количество ничьих: " << counter << endl;
    }
    static void score(const vector<Game>& games)
    {
        int score = 0;
        for (const auto game : games)
        {
            game.goals_for == game.goals_against
                ? score++ : game.goals_for > game.goals_against
                    ? score += 3 : score;
        }
        cout << "Счет команды: " << score << endl;
    }
    static vector<Game> mock()
    {
        return {
            // Игры с победой (Goals For > Goals Against)
            Game(3, 1),
            Game(2, 0),
            Game(4, 2),
            Game(1, 0),
            Game(5, 3),
            Game(2, 1),
            Game(6, 0),
            Game(3, 2),
            Game(1, 0),
            Game(4, 1),

            // Игры с ничьей (Goals For == Goals Against)
            Game(0, 0),
            Game(1, 1),
            Game(2, 2),
            Game(3, 3),

            // Игры с поражением (Goals For < Goals Against)
            Game(0, 1),
            Game(1, 3),
            Game(2, 4),
            Game(0, 2),
            Game(1, 4),
            Game(0, 3),
            Game(2, 3),
            Game(1, 2)
        };
    }
};
void Exercise_13_44()
{
    vector<Game> games = Game::mock();
    cout << "А) --------------------------------" << endl;
    for (const auto game : games) { game.game_result(); }
    cout << endl << "Б) --------------------------------" << endl;
    Game::count_wins(games);
    cout << endl << "В) --------------------------------" << endl;
    Game::count_wins_losses(games);
    cout << endl << "Г) --------------------------------" << endl;
    Game::count_wins_losses_draws(games);
    cout << endl << "Д) --------------------------------" << endl;
    Game::score(games);
}

int main()
{
    cout << "--- Златопольский 13.29 ---" << endl;
    Exercise_13_29();
    cout << endl << "--- Златопольский 13.44 ---" << endl;
    Exercise_13_44();
    return 0;
}