#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>

#define ARRAY_SIZE 10

using namespace std;

void quickSort(int (&arr)[ARRAY_SIZE]);

void recursiveMergeSort(int (&arr)[ARRAY_SIZE]);

void iterativeMergeSort(int (&arr)[ARRAY_SIZE]);

void shakerSort(int (&arrCopy)[ARRAY_SIZE]);

void combSort(int (&arr)[ARRAY_SIZE]);

void shellSort(int (&arrCopy)[ARRAY_SIZE]);

void generateArray(int (&arr)[ARRAY_SIZE]);

void showArray(int (&arr)[ARRAY_SIZE], bool generated);

/**
 * @brief <b>СТАРТ ПРОГРАММЫ</b>\n
 */
int main() {
    bool exit = false;

    int array[ARRAY_SIZE];

    generateArray(array);

    while (!exit) {
        showArray(array, true);
        cout << "\033[1mОтсортировать массив алгоритмом:\033[0m\n"
                "1) Быстрая сортировка/Алгоритм Хоара \n"
                "2) Сортировка слиянием: рекурсивная\n"
                "3) Сортировка слиянием: итеративная\n"
                "4) Шэйкерный\n"
                "5) Сортировка расческой\n"
                "6) Сортировка Шелла\n"
                "\033[1mНастройки:\033[0m\n"
                "9) Сгенерировать новый массив\n"
                "0) Выйти\n"
                "\033[7mВы ввели: ";
        int taskNum;
        cin >> taskNum;
        cout << "\033[0m";
        system("clear");
        switch (taskNum) {
            case 1:
                quickSort(array);
                break;
            case 2:
                recursiveMergeSort(array);
                break;
            case 3:
                iterativeMergeSort(array);
                break;
            case 4:
                shakerSort(array);
                break;
            case 5:
                combSort(array);
                break;
            case 6:
                shellSort(array);
                break;
            case 9:
                generateArray(array);
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

/**
 * @brief <b>Функции-утилиты</b>\n
 * Вспомогательные функции для генерации и\n
 * вывода массива в консоль.
 */
void generateArray(int (&arr)[ARRAY_SIZE]) {
    using namespace chrono;
    int seed = system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(-100, 100);
    for (int &i : arr) {
        i = distribution(generator);
    }
}

void showArray(int (&arr)[ARRAY_SIZE], bool generated) {
    string arrayTypeText;
    string color;
    if (generated) {
        arrayTypeText = "Сгенерированный массив";
        color = "\033[34;1m";
    }
    else {
        arrayTypeText = "Отсортированны массив";
        color = "\033[32;1m";
    }
    cout << color << arrayTypeText << " из " << ARRAY_SIZE << " элементов" << endl;
    string msg;
    for (int i: arr) {
        msg += to_string(i) + " ";
    }
    cout << msg << "\033[0m" << endl;
}

void waitForContinue() {
    cin.ignore();
    cout << "Для продолжения нажмите Enter." << endl;
    cin.get();
    system("clear");
}

/**
 * @brief <b>Алгоритм быстрой сортировки/Хоара</b>\n
 * Реализация из трех функций:
 */
int partOfQuickSort(int (&arr)[ARRAY_SIZE], int left, int right) {
    int pivot = arr[(left + right) / 2];
    while (left <= right) {
        while (arr[left] < pivot) left++;
        while (arr[right] > pivot) right--;
        if (left <= right) {
            swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }
    return left;
}
void quickSort(int (&arr)[ARRAY_SIZE], int start, int end) {
    if (start >= end) return;
    int rightStart = partOfQuickSort(arr, start, end);
    quickSort(arr, start, rightStart - 1);
    quickSort(arr, rightStart, end);
}
void quickSort(int (&arr)[ARRAY_SIZE]) {
    int arrCopy[ARRAY_SIZE];
    ranges::copy(arr, arrCopy);
    cout << "\033[1mМассив отсортирован алгоритмом быстрой сортировки\033[0m" << endl;
    showArray(arrCopy, true);
    quickSort(arrCopy, 0, ARRAY_SIZE - 1);
    showArray(arrCopy, false);
    waitForContinue();
}

/**
 * @brief <b>Рекурсивный алгоритм сортировки слиянием</b>\n
 * Реализация из двух функций:
 */
void recursiveMergeSort(int a[], int f_size) {
    if (f_size < 2) return;
    recursiveMergeSort(a, f_size / 2);
    recursiveMergeSort(&a[f_size / 2], f_size - (f_size / 2));
    int* buf = new int[f_size];
    int idbuf = 0, idl = 0, idr = f_size / 2;
    while ((idl < f_size / 2) && (idr < f_size))
        if (a[idl] < a[idr])
            buf[idbuf++] = a[idl++];
        else
            buf[idbuf++] = a[idr++];
    while (idl < f_size / 2) buf[idbuf++] = a[idl++];
    while (idr < f_size) buf[idbuf++] = a[idr++];
    for (idl = 0; idl < f_size; idl++) a[idl] = buf[idl];
    delete[] buf;
}
void recursiveMergeSort(int (&arr)[ARRAY_SIZE]) {
    int arrCopy[ARRAY_SIZE];
    ranges::copy(arr, arrCopy);
    cout << "\033[1mМассив отсортирован рекурсивным алгоритмом слияния\033[0m" << endl;
    showArray(arrCopy, true);
    recursiveMergeSort(arrCopy, ARRAY_SIZE);
    showArray(arrCopy, false);
    waitForContinue();
}

/**
 * @brief <b>Итеративный алгоритм сортировки слиянием</b>\n
 * Реализация из трех функций:
 */
void merge(int a[], int left, int mid, int right) {
    int it1 = 0, it2 = 0;
    int* buf = new int[right - left];
    while ((left + it1 < mid) && (mid + it2 < right)) {
        if (a[left + it1] < a[mid + it2]) {
            buf[it1 + it2] = a[left + it1];
            it1++;
        }
        else {
            buf[it1 + it2] = a[mid + it2];
            it2++;
        }
    }
    while (left + it1 < mid) {
        buf[it1 + it2] = a[left + it1];
        it1++;
    }
    while (mid + it2 < right) {
        buf[it1 + it2] = a[mid + it2];
        it2++;
    }
    for (int i = 0; i < it1 + it2; i++) a[left + i] = buf[i];
    delete[] buf;
}
void iterativeMergeSort(int a[], int f_size) {
    for (int i = 1; i < f_size; i*=2) {
        for (int j = 0; j < f_size - i; j += 2 * i) {
            merge(a, j, j + i, min(j+2*i, f_size));
        }
    }
}
void iterativeMergeSort(int (&arr)[ARRAY_SIZE]) {
    int arrCopy[ARRAY_SIZE];
    ranges::copy(arr, arrCopy);
    cout << "\033[1mМассив отсортирован итеративными алгоритмом слияния\033[0m" << endl;
    showArray(arrCopy, true);
    iterativeMergeSort(arrCopy, ARRAY_SIZE);
    showArray(arrCopy, false);
    waitForContinue();
}

/**
 * @brief <b>Алгоритм сортировки перемешиванием/Шейкерный</b>\n
 * Реализация:
 */
void shakerSort(int (&arr)[ARRAY_SIZE]) {
    int arrCopy[ARRAY_SIZE];
    ranges::copy(arr, arrCopy);
    cout << "\033[1mМассив отсортирован Шейкерным алгоритмом\033[0m" << endl;
    showArray(arrCopy, true);
    int left = 0, right = ARRAY_SIZE - 1;
    while (left <= right) {
        for (int i = right; i > left; --i) {
            if (arrCopy[i - 1] > arrCopy[i]) {
                swap(arrCopy[i - 1], arrCopy[i]);
            }
        }
        ++left;
        for (int i = left; i < right; ++i) {
            if (arrCopy[i] > arrCopy[i + 1]) {
                swap(arrCopy[i], arrCopy[i + 1]);
            }
        }
        --right;
    }
    showArray(arrCopy, false);
    waitForContinue();
}

/**
 * @brief <b>Алгоритм сортировки расческой</b>\n
 * Реализация:
 */
void combSort(int (&arr)[ARRAY_SIZE]) {
    int arrCopy[ARRAY_SIZE];
    ranges::copy(arr, arrCopy);
    cout << "\033[1mМассив отсортирован алгоритмом расчески\033[0m" << endl;
    showArray(arrCopy, true);

    const double factor = 1.247;
    int step = ARRAY_SIZE - 1;

    while (step >= 1) {
        for (int i = 0; i + step < ARRAY_SIZE; ++i) {
            swap(arrCopy[i], arrCopy[i + step]);
        }
        step /= factor;
    }

    for (size_t idx_i = 0; idx_i + 1 < ARRAY_SIZE; ++idx_i) {
        for (size_t idx_j = 0; idx_j + 1 < ARRAY_SIZE - idx_i; ++idx_j) {
            if (arrCopy[idx_j + 1] < arrCopy[idx_j]) {
                swap(arrCopy[idx_j + 1], arrCopy[idx_j]);
            }
        }
    }

    showArray(arrCopy, false);
    waitForContinue();
}

/**
 * @brief <b>Алгоритм сортировки Шелла</b>\n
 * Реализация:
 */
void shellSort(int (&arr)[ARRAY_SIZE]) {
    int arrCopy[ARRAY_SIZE];
    ranges::copy(arr, arrCopy);
    cout << "\033[1mМассив отсортирован алгоритмом Шелла\033[0m" << endl;
    showArray(arrCopy, true);

    int gap = 1;
    while (gap < ARRAY_SIZE / 3) {
        gap = 3 * gap + 1;
    }

    while (gap >= 1) {
        for (int i = gap; i < ARRAY_SIZE; i++) {
            int temp = arrCopy[i];
            int j;
            for (j = i; j >= gap && arrCopy[j - gap] > temp; j -= gap) {
                arrCopy[j] = arrCopy[j - gap];
            }
            arrCopy[j] = temp;
        }
        gap /= 3;
    }

    showArray(arrCopy, false);
    waitForContinue();
}
