#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

struct Rec1 {
    long nomer;
    char name[20];
    int year;
    char group[20];
    float sred;
};

struct Rec2 {
    char name[20];
    int year;
    char group[20];
    float sred;
};

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Rec1 readRec1FromConsole(long index) {
    Rec1 rec;
    rec.nomer = index;
    cout << "\n--- Ввод записи #" << index << " ---" << endl;

    clearInputBuffer();

    cout << "Фамилия (до 19 символов): ";
    cin.clear();
    cin.getline(rec.name, 20);

    cout << "Год рождения: ";
    while (!(cin >> rec.year) || rec.year <= 1900 || rec.year > 2025) {
        cout << "Некорректный год. Повторите ввод: ";
        cin.clear();
        clearInputBuffer();
    }

    clearInputBuffer();

    cout << "Группа (до 19 символов): ";
    cin.getline(rec.group, 20);

    cout << "Средний балл (0.0 - 5.0): ";
    while (!(cin >> rec.sred) || rec.sred < 0.0f || rec.sred > 5.0f) {
        cout << "Некорректный балл. Повторите ввод: ";
        cin.clear();
        clearInputBuffer();
    }

    // clearInputBuffer();

    return rec;
}

void printHeaderRec1() {
    cout << setfill('-') << setw(75) << "-" << setfill(' ') << endl;
    cout << "| " << left << setw(5) << "Nomer"
         << " | " << left << setw(18) << "Familiya"
         << " | " << left << setw(4) << "Year"
         << " | " << left << setw(18) << "Group"
         << " | " << left << setw(8) << "Sred_Ball"
         << " |" << endl;
    cout << setfill('-') << setw(75) << "-" << setfill(' ') << endl;
}

void printRec1(const Rec1& rec) {
    cout << "| " << right << setw(5) << rec.nomer
         << " | " << left << setw(18) << rec.name
         << " | " << right << setw(4) << rec.year
         << " | " << left << setw(18) << rec.group
         << " | " << right << fixed << setprecision(2) << setw(8) << rec.sred
         << " |" << endl;
}

void printHeaderRec2() {
    cout << setfill('-') << setw(69) << "-" << setfill(' ') << endl;
    cout << "| " << left << setw(18) << "Familiya"
         << " | " << left << setw(4) << "Year"
         << " | " << left << setw(18) << "Group"
         << " | " << left << setw(8) << "Sred_Ball"
         << " |" << endl;
    cout << setfill('-') << setw(69) << "-" << setfill(' ') << endl;
}

void printRec2(const Rec2& rec) {
    cout << "| " << left << setw(18) << rec.name
         << " | " << right << setw(4) << rec.year
         << " | " << left << setw(18) << rec.group
         << " | " << right << fixed << setprecision(2) << setw(8) << rec.sred
         << " |" << endl;
}

long getNextNomer(const char *fileName) {
    fstream file(fileName, ios::in | ios::binary | ios::ate);
    if (!file) {
        return 1;
    }
    long fileSize = file.tellg();
    file.close();

    if (fileSize == 0) {
        return 1;
    }

    long numRecords = fileSize / sizeof(Rec1);
    return numRecords + 1;
}

void CreateFileIn(const char *fileName) {
    fstream file(fileName, ios::out | ios::binary);
    if (!file) {
        cerr << "Ошибка: Не удалось открыть файл " << fileName << " для создания." << endl;
        return;
    }

    int count;
    cout << "Введите количество записей для создания: ";
    while (!(cin >> count) || count < 0) {
        cout << "Некорректное количество. Повторите ввод: ";
        cin.clear();
        clearInputBuffer();
    }

    for (int i = 0; i < count; ++i) {
        Rec1 rec = readRec1FromConsole(i + 1);
        file.write(reinterpret_cast<const char*>(&rec), sizeof(Rec1));
    }

    file.close();
    cout << "Успешно создано " << count << " записей в файле " << fileName << "." << endl;
}

void AddFileIn(const char *fileName) {
    fstream file(fileName, ios::in | ios::out | ios::binary | ios::app);
    if (!file) {
        cerr << "Ошибка: Не удалось открыть файл " << fileName << " для добавления. Возможно, его нужно сначала создать." << endl;
        return;
    }

    int count;
    cout << "Введите количество записей для добавления: ";
    while (!(cin >> count) || count < 0) {
        cout << "Некорректное количество. Повторите ввод: ";
        cin.clear();
        clearInputBuffer();
    }

    long startNomer = getNextNomer(fileName);

    for (int i = 0; i < count; ++i) {
        Rec1 rec = readRec1FromConsole(startNomer + i);
        file.write(reinterpret_cast<const char*>(&rec), sizeof(Rec1));
    }

    file.close();
    cout << "Успешно добавлено " << count << " записей в файл " << fileName << "." << endl;
}

void ReadFileIn(const char *fileName) {
    fstream file(fileName, ios::in | ios::binary);
    if (!file) {
        cout << "Файл " << fileName << " не найден или пуст." << endl;
        return;
    }

    cout << "\n--- Просмотр входного файла: " << fileName << " ---" << endl;
    printHeaderRec1();

    Rec1 rec;
    int count = 0;
    while (file.read(reinterpret_cast<char*>(&rec), sizeof(Rec1))) {
        printRec1(rec);
        count++;
    }

    cout << setfill('-') << setw(75) << "-" << setfill(' ') << endl;
    if (count == 0) {
        cout << "Файл не содержит записей." << endl;
    } else {
        cout << "Всего записей: " << count << endl;
    }

    file.close();
}

void CreateFileOut(const char *fileName1, const char *fileName2) {
    fstream fileIn(fileName1, ios::in | ios::binary);
    if (!fileIn) {
        cerr << "Ошибка: Не удалось открыть входной файл " << fileName1 << "." << endl;
        return;
    }

    vector<Rec1> students;
    Rec1 rec;
    while (fileIn.read(reinterpret_cast<char*>(&rec), sizeof(Rec1))) {
        students.push_back(rec);
    }
    fileIn.close();

    if (students.empty()) {
        cout << "Входной файл " << fileName1 << " пуст. Выходной файл не создан." << endl;
        return;
    }

    int max_year = students[0].year;
    for (const auto& student : students) {
        if (student.year > max_year) {
            max_year = student.year;
        }
    }

    float max_sred = -1.0f;
    for (const auto& student : students) {
        if (student.year == max_year) {
            if (student.sred > max_sred) {
                max_sred = student.sred;
            }
        }
    }

    fstream fileOut(fileName2, ios::out | ios::binary);
    if (!fileOut) {
        cerr << "Ошибка: Не удалось открыть выходной файл " << fileName2 << " для записи." << endl;
        return;
    }

    int count = 0;
    for (const auto& student : students) {
        if (student.year == max_year && student.sred == max_sred) {
            Rec2 recOut;
            strcpy(recOut.name, student.name);
            recOut.year = student.year;
            strcpy(recOut.group, student.group);
            recOut.sred = student.sred;

            fileOut.write(reinterpret_cast<const char*>(&recOut), sizeof(Rec2));
            count++;
        }
    }

    fileOut.close();
    cout << "Обработка завершена. Найдено " << count
         << " студентов (самый молодой год: " << max_year
         << ", максимальный балл среди них: "
         << fixed << setprecision(2) << max_sred << ")." << endl;
    cout << "Результаты записаны в файл " << fileName2 << "." << endl;
}


void ReadFileOut(const char *fileName) {
    fstream file(fileName, ios::in | ios::binary);
    if (!file) {
        cout << "Файл " << fileName << " не найден или пуст." << endl;
        return;
    }

    cout << "\n--- Просмотр выходного файла: " << fileName << " ---" << endl;
    printHeaderRec2();

    Rec2 rec;
    int count = 0;
    while (file.read(reinterpret_cast<char*>(&rec), sizeof(Rec2))) {
        printRec2(rec);
        count++;
    }

    cout << setfill('-') << setw(69) << "-" << setfill(' ') << endl;
    if (count == 0) {
        cout << "Файл не содержит записей." << endl;
    } else {
        cout << "Всего записей: " << count << endl;
    }

    file.close();
}

void SortFileIn(const char *fileName, int sortType) {
    fstream file(fileName, ios::in | ios::binary);
    if (!file) {
        cerr << "Ошибка: Не удалось открыть входной файл " << fileName << " для сортировки." << endl;
        return;
    }

    vector<Rec1> students;
    Rec1 rec;
    while (file.read(reinterpret_cast<char*>(&rec), sizeof(Rec1))) {
        students.push_back(rec);
    }
    file.close();

    if (students.empty()) {
        cout << "Файл " << fileName << " пуст. Сортировка не требуется." << endl;
        return;
    }

    if (sortType == 1) {
        sort(students.begin(), students.end(), [](const Rec1& a, const Rec1& b) {
            return a.sred > b.sred;
        });
        cout << "Сортировка по полю 'Средний балл' (по убыванию) завершена." << endl;
    } else if (sortType == 2) {
        sort(students.begin(), students.end(), [](const Rec1& a, const Rec1& b) {
            return a.year > b.year;
        });
        cout << "Сортировка по полю 'Year' (самые молодые в начале) завершена." << endl;
    }

    fstream fileOut(fileName, ios::out | ios::binary | ios::trunc);
    if (!fileOut) {
        cerr << "Ошибка: Не удалось открыть файл " << fileName << " для записи отсортированных данных." << endl;
        return;
    }

    for (size_t i = 0; i < students.size(); ++i) {
        students[i].nomer = i + 1;
        fileOut.write(reinterpret_cast<const char*>(&students[i]), sizeof(Rec1));
    }

    fileOut.close();
    cout << "Файл " << fileName << " успешно обновлен и содержит " << students.size() << " записей." << endl;
}

void SortBySred(const char *fileName) {
    SortFileIn(fileName, 1);
}

void SortByYear(const char *fileName) {
    SortFileIn(fileName, 2);
}


void menu() {
    const char* IN_FILE = "students_in.bin";
    const char* OUT_FILE = "results_out.bin";
    int choice;

    do {
        cout << "\n==============================================" << endl;
        cout << "          МЕНЮ УПРАВЛЕНИЯ ФАЙЛАМИ СТУДЕНТОВ" << endl;
        cout << "==============================================" << endl;
        cout << "1. CreateFileIn: Создать входной файл (" << IN_FILE << ")" << endl;
        cout << "2. AddFileIn: Добавить записи во входной файл" << endl;
        cout << "3. ReadFileIn: Просмотреть входной файл" << endl;
        cout << "4. CreateFileOut: Обработать данные и создать выходной файл (" << OUT_FILE << ")" << endl;
        cout << "5. ReadFileOut: Просмотреть выходной файл" << endl;
        cout << "6. Сортировка входного файла по среднему баллу (Sred)" << endl;
        cout << "7. Сортировка входного файла по году рождения (Year)" << endl;
        cout << "0. Выход" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "Выберите опцию: ";

        if (!(cin >> choice)) {
            cerr << "Некорректный ввод. Пожалуйста, введите число." << endl;
            cin.clear();
            clearInputBuffer();
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:
                CreateFileIn(IN_FILE);
                break;
            case 2:
                AddFileIn(IN_FILE);
                break;
            case 3:
                ReadFileIn(IN_FILE);
                break;
            case 4:
                CreateFileOut(IN_FILE, OUT_FILE);
                break;
            case 5:
                ReadFileOut(OUT_FILE);
                break;
            case 6:
                SortBySred(IN_FILE);
                break;
            case 7:
                SortByYear(IN_FILE);
                break;
            case 0:
                cout << "Программа завершена. До свидания!" << endl;
                break;
            default:
                cout << "Неизвестная опция. Повторите выбор." << endl;
                break;
        }
    } while (choice != 0);
}

int main() {
    cout << fixed << setprecision(2);
    menu();
    return 0;
}