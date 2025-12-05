//
// Created by Kuanysh Yabekov on 05.12.2025.
//
#include <vector>
#include <fstream>
#include <iostream>
#include <random>
#include <iomanip>
#include <sstream>
#include <algorithm>

#define M 6
#define N 3

#define ExtraMatricesFileName "extra-matrices.txt"
#define LMatricesFileName "l-matrices.txt"
#define KMatricesFileName "k-matrices.txt"

using namespace std;
using Matrix = vector<vector<double>>;

vector<Matrix> getMockMatrices()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution dist(0.0, 10.0);

    vector<Matrix> matrices;
    Matrix temp_matrix;
    vector<double> temp_row;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < M; k++)
            {
                temp_row.push_back(dist(gen));
            }
            temp_matrix.push_back(temp_row);
            temp_row.clear();
        }
        matrices.push_back(temp_matrix);
        temp_matrix.clear();
    }
    return matrices;
}

void printMatrices(const vector<Matrix>& matrices)
{
    int count = 1;
    for (auto& matrix : matrices)
    {
        cout << "Матрица " << count << " " << N << "x" << M
            << fixed << setprecision(2) << endl;
        count++;
        for (auto& row : matrix)
        {
            for (auto& el : row)
            {
                cout << setw(5) << left << el;
            }
            cout << endl;
        }
    }
}

ofstream& operator<<(ofstream& os, const Matrix& m)
{
    os << N << "x" << M << endl;
    for (const auto& row : m)
    {
        for (const auto& el : row)
        {
            os << el << " ";
        }
        os << endl;
    }
    os << endl;
    return os;
}

istream& operator>>(istream& is, Matrix& m)
{
    int rows = 0;
    int cols = 0;
    char delimiter = ' ';
    string size_line;

    do
    {
        if (!getline(is, size_line))
        {
            if (is.eof()) { is.setstate(ios::failbit); }
            return is;
        }
    }
    while (ranges::all_of(size_line, [](const char c) { return isspace(static_cast<unsigned char>(c)); }));

    if (stringstream ss(size_line);
        !(ss >> rows >> delimiter >> cols) || delimiter != 'x')
    {
        if (ss)
            is.setstate(ios::failbit);
        return is;
    }

    m.assign(rows, vector<double>(cols));

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (!(is >> m[i][j]))
            {
                is.setstate(ios::failbit);
                return is;
            }
        }
    }
    return is;
}

void writeMatricesToFile(const vector<Matrix>& matrices, const string& filename)
{
    ofstream outfile(filename, ios::out);
    for (auto& matrix : matrices)
    {
        if (outfile.is_open())
        {
            outfile << matrix;
        }
        else
        {
            cerr << "Не удалось открыть файл для записи." << endl;
        }
    }
    cout << "Объекты сохранены. Количество: " << matrices.size() << endl;
    outfile.close();
}

vector<Matrix> readMatricesFromFile(const string& filename)
{
    vector<Matrix> matrices;
    if (ifstream infile(filename); infile.is_open())
    {
        Matrix temp_matrix;
        while (infile >> temp_matrix)
        {
            matrices.push_back(temp_matrix);
        }
        if (infile.eof())
        {
            cout << "Файл успешно считан до конца. Загружено объектов: "
                << matrices.size() << endl;
        }
        else if (infile.fail())
        {
            cerr << "Ошибка форматирования при чтении файла!" << endl;
        }
        infile.close();
    }
    return matrices;
}

int main()
{

    const auto l_matrices = readMatricesFromFile(LMatricesFileName);
    const auto k_matrices = readMatricesFromFile(KMatricesFileName);
    const vector<Matrix> extra_matrices = l_matrices.size() > k_matrices.size()
    ? vector(l_matrices.begin() + k_matrices.size(), l_matrices.end())
    : vector(k_matrices.begin() + l_matrices.size(), k_matrices.end());
    writeMatricesToFile(extra_matrices, ExtraMatricesFileName);

    cout << "Содержимое файла с L матрицами" << endl;
    printMatrices(l_matrices);
    cout << endl;

    cout << "Содержимое файла с K матрицами" << endl;
    printMatrices(k_matrices);
    cout << endl;

    cout << "Содержимое файла с Extra матрицами" << endl;
    printMatrices(extra_matrices);
    cout << endl;
}
