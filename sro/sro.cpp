#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Множество символов-разделителей
const string DELIMITERS = "_.,;:\n\t!?";

// --- Вспомогательные функции для свойств ---

/**
 * @brief Проверяет, обладает ли слово свойством Q:
 * буквы располагаются по возрастанию (по ASCII) и не повторяются.
 * @param word Проверяемое слово.
 * @return true, если свойство Q выполняется, иначе false.
 */
bool has_property_Q(const string& word) {
    if (word.empty()) {
        return false;
    }
    // Проверка на возрастание и отсутствие повторов
    for (size_t i = 0; i < word.length() - 1; ++i) {
        // Сравнение символов по ASCII
        if (word[i] >= word[i+1]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Проверяет, обладает ли символ свойством T:
 * символ является маленькой согласной латинской буквой.
 * @param c Проверяемый символ.
 * @return true, если свойство T выполняется, иначе false.
 */
bool has_property_T(char c) {
    // Проверка, является ли символ маленькой латинской буквой
    if (c >= 'a' && c <= 'z') {
        // Проверка, является ли символ согласной (т.е. не 'a', 'e', 'i', 'o', 'u', 'y')
        return (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'y');
    }
    return false;
}

// --- Функции, требуемые заданием ---

/**
 * @brief Сортировка вектора указателей на строки в лексикографическом порядке.
 * @param words_pointers Вектор указателей на слова.
 */
void sort_words(vector<const string*>& words_pointers) {
    // Используем алгоритм sort и компаратор для сравнения строк, на которые указывают указатели
    sort(words_pointers.begin(), words_pointers.end(),
         [](const string* a, const string* b) {
             return *a < *b;
         });
}

/**
 * @brief Удаление символов из строки, обладающих свойством T.
 * @param str Обрабатываемая строка (передается по ссылке).
 */
void remove_T_chars(string& str) {
    // Используем идиому erase-remove_if
    str.erase(remove_if(str.begin(), str.end(), has_property_T), str.end());
}

// --- Основная логика ---

/**
 * @brief Выделяет слова из строки-предложения s, используя заданные разделители.
 * @param s Исходная строка-предложение.
 * @param delimiters Строка с символами-разделителями.
 * @return Вектор выделенных слов.
 */
vector<string> extract_words(const string& s, const string& delimiters) {
    vector<string> words;
    string current_word;

    for (char c : s) {
        // Проверка, является ли символ разделителем
        if (delimiters.find(c) != string::npos) {
            // Если текущее слово не пустое, добавляем его в вектор
            if (!current_word.empty()) {
                words.push_back(current_word);
                current_word.clear();
            }
        } else {
            // Символ не является разделителем, добавляем его к текущему слову
            current_word += c;
        }
    }

    // Обработка последнего слова, если строка не заканчивается разделителем
    if (!current_word.empty()) {
        words.push_back(current_word);
    }

    return words;
}

// --- Главная функция ---

int main() {
    string s = "Complexity.Abcd;a_b_c_d!Zyx:AcE.aDd,cde?BcdE\tAbC\nFGh;";

    cout << "Исходная строка-предложение s:\n\"" << s << "\"" << endl;
    cout << "---" << endl;

    // 1. Выделить все слова
    vector<string> words = extract_words(s, DELIMITERS);

    if (words.empty()) {
        cout << "В строке не найдено слов." << endl;
        return 0;
    }

    cout << "Выделенные слова (" << words.size() << "):\n";
    for (const string& word : words) {
        cout << "[" << word << "] ";
    }
    cout << "\n---" << endl;

    // 2. Найти количество всех слов, обладающих свойством Q
    int count_Q = 0;
    for (const string& word : words) {
        if (has_property_Q(word)) {
            count_Q++;
        }
    }
    cout << "Количество слов со свойством Q (буквы по возрастанию и без повторов): " << count_Q << endl;
    cout << "---" << endl;

    // 3. Вывести все слова в лексикографическом порядке

    // Создаем вектор указателей для сортировки, чтобы не копировать строки
    vector<const string*> sorted_words_pointers;
    for (const string& word : words) {
        sorted_words_pointers.push_back(&word);
    }

    // Сортируем с помощью требуемой функции
    sort_words(sorted_words_pointers);

    cout << "Слова в лексикографическом порядке:\n";
    for (const string* p_word : sorted_words_pointers) {
        cout << *p_word << endl;
    }
    cout << "---" << endl;

    // 4. Записать в строку t любое из слов максимальной длины строки s
    string t;
    size_t max_len = 0;

    for (const string& word : words) {
        if (word.length() > max_len) {
            max_len = word.length();
            t = word; // Записываем в t первое найденное слово максимальной длины
        }
    }

    cout << "Слово максимальной длины, записанное в строку t: \"" << t << "\"" << endl;

    // 5. Удалить из строки t все символы, обладающие свойством T
    string t_original = t; // Сохраняем оригинал для вывода

    // Удаляем символы с помощью требуемой функции
    remove_T_chars(t);

    cout << "Строка t после удаления символов со свойством T (маленькая согласная латинская буква):\n";
    cout << "Было: \"" << t_original << "\"\n";
    cout << "Стало: \"" << t << "\"" << endl;

    return 0;
}
