#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Director
{
    string name;
    string surname;
};

class Movie
{
public:
    string title;
    Director director;
    int year_published;
    string country;
    double price;
    double income;
    double profit;

    Movie() : year_published(0), price(0), income(0), profit(0)
    {
    }

    Movie(
        string t,
        string n,
        string s,
        const int y,
        string c,
        const double p,
        const double i,
        const double pr
    ) : title(std::move(t)),
        director(std::move(n), std::move(s)),
        year_published(y),
        country(std::move(c)),
        price(p),
        income(i),
        profit(pr)
    {
    }

    static vector<Movie> mockMovies()
    {
        return {
            Movie(
                "Dune",
                "Denis", "Villeneuve",
                2021,
                "USA",
                10.50, // Price
                402000000.0, // Income
                300000000.0 // Profit (Примерные данные)
            ),

            Movie(
                "Interstellar",
                "Christopher", "Nolan",
                2014,
                "USA",
                8.99,
                677000000.0,
                500000000.0
            ),

            Movie(
                "Parasite",
                "Bong", "Joon-ho",
                2019,
                "South Korea",
                7.00,
                258000000.0,
                245000000.0
            ),

            Movie(
                "Potop", // title
                "Jerzy", // director.name
                "Hoffman", // director.surname
                1974, // year_published
                "Poland", // country
                6.00, // price (пример)
                5500000.0, // income (пример)
                3500000.0 // profit (пример)
            ),

            Movie(
                "Ogniem i mieczem", // title
                "Jerzy", // director.name
                "Hoffman", // director.surname
                1999, // year_published
                "Poland", // country
                7.50, // price (пример)
                10500000.0, // income (пример)
                8000000.0 // profit (пример)
            )
        };
    }
};

std::ostream& operator<<(std::ostream& os, const Movie& m)
{
    os << m.title << "\n"
        << m.director.name << "\n"
        << m.director.surname << "\n"
        << m.year_published << "\n"
        << m.country << "\n"
        << m.price << "\n"
        << m.income << "\n"
        << m.profit << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, Movie& m)
{
    getline(is, m.title);
    getline(is, m.director.name);
    getline(is, m.director.surname);

    if (!(is >> m.year_published)) return is;
    if (is.peek() == '\n') is.ignore(1);

    getline(is, m.country);
    if (!(is >> m.price)) return is;
    if (!(is >> m.income)) return is;
    if (!(is >> m.profit)) return is;
    if (is.peek() == '\n') is.ignore(1);
    return is;
}

void writeMovies(const vector<Movie>& movies, const string& file_name)
{
    ofstream outfile(file_name, ios::out);
    for (auto& movie : movies)
    {
        if (outfile.is_open())
        {
            outfile << movie;
        }
        else
        {
            cerr << "Не удалось открыть файл для записи." << endl;
        }
    }
    cout << "Объекты сохранены. Количество: " << movies.size() << endl;
    outfile.close();
}

vector<Movie> readAllMovies(const string& file_name)
{
    vector<Movie> loaded_movies;

    if (ifstream infile(file_name); infile.is_open())
    {
        Movie movie;
        while (infile >> movie)
        {
            loaded_movies.push_back(movie);
        }
        if (infile.eof())
        {
            std::cout << "Файл успешно считан до конца. Загружено объектов: "
                << loaded_movies.size() << std::endl;
        }
        else if (infile.fail())
        {
            std::cerr << "Ошибка форматирования при чтении файла!" << std::endl;
        }
        infile.close();
    }
    else
    {
        std::cerr << "Ошибка: Не удалось открыть файл для чтения." << std::endl;
    }
    return loaded_movies;
}

void printMovies(const vector<Movie>& movies)
{
    for (auto& m : movies)
    {
        cout << "\n============================================\n"
            << "🎬 Фильм: " << m.title << " (" << m.year_published << ")"
            << "\n============================================\n"
            << "  Режиссер: " << m.director.name << " " << m.director.surname << "\n"
            << "  Страна:   " << m.country << "\n"
            << "--------------------------------------------\n"
            << std::fixed << std::setprecision(2)
            << "  Цена:     $" << m.price << "\n"
            << "  Доход:    $" << m.income << "\n"
            << "  Прибыль:  $" << m.profit << "\n\n";
    }
}

vector<Movie> filterMoviesByDirectorName(const vector<Movie>& movies, const string& director_name)
{
    vector<Movie> filtered_movies;
    for (auto& movie : movies)
    {
        if (movie.director.name == director_name)
        {
            filtered_movies.push_back(movie);
        }
    }
    cout << "Найдено " << filtered_movies.size() << " записей удовлетворяющих условию." << endl;
    return filtered_movies;
}


void glazunova_8_1_basic()
{
    const string file_name = "movie_data.txt";
    const auto movies = Movie::mockMovies();
    writeMovies(movies, file_name);
    cout << movies[0] << endl;

    const auto loaded_movies = readAllMovies(file_name);
    const auto filtered_movies = filterMoviesByDirectorName(loaded_movies, "Jerzy");
    printMovies(filtered_movies);

    const string filtered_movies_file_name = "movies_filtered_data.txt";
    writeMovies(filtered_movies, filtered_movies_file_name);
}

// ----------------------------------------------------------------------------------------

vector<double> readNums(const string& file_name)
{
    vector<double> nums;
    if (ifstream infile(file_name); infile.is_open())
    {
        double num;
        while (infile >> num)
        {
            nums.push_back(num);
        }
        if (infile.eof())
        {
            std::cout << "Файл успешно считан до конца. Загружено объектов: "
                << nums.size() << std::endl;
        }
        else if (infile.fail())
        {
            std::cerr << "Ошибка форматирования при чтении файла!" << std::endl;
        }
        infile.close();
    }
    else
    {
        std::cerr << "Ошибка: Не удалось открыть файл для чтения." << std::endl;
    }
    return nums;
}

void glazunova_8_1_middle()
{
    const string file_name = "2025-11-28-hw-middle.txt";
    const auto nums = readNums(file_name);
    double max_num = 0;
    for (int i = 1; i < nums.size(); i+=2)
    {
        if (abs(nums[i]) > max_num) max_num = abs(nums[i]);
    }
    cout << "Максимальный модуль числа с нечетным номером: " << max_num << endl;
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
            "1) 8.1 Базовый уровень\n"
            "2) 8.1 Средний уровень\n"
            "0) Выйти\n"
            "\033[7mВы ввели: ";
        int taskNum;
        cin >> taskNum;
        cout << "\033[0m";
        system("clear");
        switch (taskNum)
        {
        case 1:
            glazunova_8_1_basic();
            waitForContinue();
            break;
        case 2:
            glazunova_8_1_middle();
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
