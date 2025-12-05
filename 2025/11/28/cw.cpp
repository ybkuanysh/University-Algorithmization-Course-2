#include <iostream>

#define THROW_AN_ERROR true

using namespace std;

class DatabaseConnectionException
{
public:
    const string message = "Не удалось подключиться к базе данных.";
};

class DatabaseService
{
public:
    static void connectToDatabase()
    {
        if (THROW_AN_ERROR)
        {
            throw DatabaseConnectionException();
        }
        int result = 10 / 0;
        cout << "Посчитанное значение " << result << endl;
        cout << "Успешное подключение к базе данных." << endl;
    }
};

int main()
{
    try
    {
        DatabaseService::connectToDatabase();
    }
    catch (DatabaseConnectionException e)
    {
        cerr << "Ошибка при подключении DatabaseConnectionException: " << e.message << endl;
    }
    catch (string exception)
    {
        cerr << "Ошибка при подключении: " << exception << endl;
    }
}
