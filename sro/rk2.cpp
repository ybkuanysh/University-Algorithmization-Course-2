#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Highs
{
    static string compareToString(const double a, const double b)
    {
        return to_string(a) + (a>b?" > ":" < ") + to_string(b);
    }
public:
    vector<double> horizontal_values;
    Highs() = default;
    explicit Highs(const vector<double>& horizontal_values) : horizontal_values(horizontal_values) {}

    [[nodiscard]] double maxHeight() const
    {
        if (horizontal_values.empty()) throw;
        auto _max_height = horizontal_values[0];
        for (const auto el : horizontal_values)
        { if (el > _max_height) _max_height = el; }
        return _max_height;
    }
    [[nodiscard]] double minHeight() const
    {
        if (horizontal_values.empty()) throw;
        auto _min_height = horizontal_values[0];
        for (const auto el : horizontal_values)
        { if (el < _min_height) _min_height = el; }
        return _min_height;
    }

    [[nodiscard]] double max_height_difference() const
    {
        if (horizontal_values.empty()) throw;
        return maxHeight() - minHeight();
    }
    [[nodiscard]] double summary_height_difference() const
    {
        if (horizontal_values.empty()) throw;
        double _summary_height = 0;
        for (const auto el : horizontal_values)
        { if (el > 0) _summary_height += el; }
        return _summary_height;
    }

    [[nodiscard]] double max_slope() const
    {
        if (horizontal_values.empty()) throw;
        double _max_slope = 0;
        for (int i = 0; i < horizontal_values.size() - 1; i++)
        {
            const double _slope = horizontal_values[i] - horizontal_values[i + 1];
            if (_max_slope > _slope) _max_slope = _slope;
        }
        return _max_slope;
    }
    [[nodiscard]] double medium_slope() const
    {
        if (horizontal_values.empty()) throw;
        vector<double> _slopes = {};
        for (int i = 0; i < horizontal_values.size() - 1; i++)
        {
            const double _slope = horizontal_values[i] - horizontal_values[i + 1];
            _slopes.push_back(_slope);
        }
        double _slope_sum = 0;
        for (const auto slope : _slopes)
        { _slope_sum += slope; }
        return _slope_sum / static_cast<double>(_slopes.size());
    }
    void debugDescription() const
    {
        cout << "Максимальная высота: " << maxHeight() << "\n"
            << "Минимальная высота: " << minHeight() << "\n"
            << "Наибольший перепад: " << max_height_difference() << "\n"
            << "Суммарный перепад: " << summary_height_difference() << "\n"
            << "Наибольшая крутизна: " << max_slope() << "\n"
            << "Средняя крутизна: " << medium_slope() << "\n";
    }

    static void compare(Highs& lhs, const Highs& rhs)
    {
        if (lhs.horizontal_values.size() != rhs.horizontal_values.size())
        {
            cerr << "Длина у профилей разная!" << endl;
            return;
        }
        cout << "--------Сравнение--------\n" << setw(1)
            << "Максимальная высота: " << compareToString(lhs.maxHeight(), rhs.maxHeight()) << "\n"
            << "Минимальная высота: " << compareToString(lhs.minHeight(), rhs.minHeight()) << "\n"
            << "Наибольший перепад: " << compareToString(lhs.max_height_difference(), rhs.max_height_difference()) << "\n"
            << "Суммарный перепад: " << compareToString(lhs.summary_height_difference(), rhs.summary_height_difference()) << "\n"
            << "Наибольшая крутизна: " << compareToString(lhs.max_slope(), rhs.max_slope()) << "\n"
            << "Средняя крутизна: " << compareToString(lhs.medium_slope(), rhs.medium_slope()) << "\n";
    }
};

int main()
{
    cout << "---Запись о высотах 1---" << endl;
    Highs highsOfMount1 ({1.0, -2.0, 3.0, -4.0, 5.0, -6.0});
    highsOfMount1.debugDescription();
    cout << endl << "---Запись о высотах 2---" << endl;
    Highs highsOfMount2 ({4.0, -2.0, 6.0, 2.0, -7.0, 9.0});
    highsOfMount2.debugDescription();

    cout << endl;
    Highs::compare(highsOfMount1, highsOfMount2);
}