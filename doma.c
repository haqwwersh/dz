#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <locale.h>

void FillInc(int* A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
}

void FillDec(int* A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = (n-i);
    }
}

void FillRand(int* A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % (123 * n);
    }
}

int CheckSum(int* A, int n) {
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += A[i];
    }
    return s;
}

int RunNumber(int* A, int n) {
    if (n < 1) return 0;
    int series = 0;
    for (int i = 0; i < n-1; i++) {
        if (!(A[i] <= A[i+1])) {
            series++;
        }
    }
    series++;
    return series;
}

void PrintMas(int* A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int BinarySearchIter(int* A, int n, int key, int* Cf) {
    int left = 0;
    int right = n - 1;
    *Cf = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        (*Cf)++;

        if (A[mid] == key)
            return mid;

        if (A[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

int BinarySearchAlt(int* A, int n, int key, int* Cf) {
    int left = 0;
    int right = n - 1;
    int result = -1;
    *Cf = 0;

    while (left < right) {
        int mid = left + (right - left) / 2;
        (*Cf)++;

        if (A[mid] < key) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    (*Cf)++;
    if (A[right] == key) {
        result = right;
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    srand(time(NULL));

    int n = 20;
    int A[n];

    printf("Массив по возрастанию:\n");
    FillInc(A, n);
    PrintMas(A, n);
    int key;
    int Cf;

    printf("Введите ключ для поиска: ");
    scanf("%d", &key);

    int pos = BinarySearchIter(A, n, key, &Cf);

    printf("\nИтерационный бинарный поиск\n");

    if (pos != -1)
        printf("Элемент найден: %d, позиция: %d\n", A[pos], pos);
    else
        printf("Элемент не найден\n");

    printf("Фактическое число сравнений Cf = %d\n", Cf);

    printf("Теоретическая оценка C = %.2f\n\n", log2(n));

    Cf = 0;

    pos = BinarySearchAlt(A, n, key, &Cf);

    printf("Альтернативный бинарный поиск\n");

    if (pos != -1)
        printf("Элемент найден: %d, позиция: %d\n", A[pos], pos);
    else
        printf("Элемент не найден\n");

    printf("Фактическое число сравнений Cf = %d\n", Cf);

    printf("Теоретическая оценка C = %.2f\n\n", log2(n));

    printf("Проверка:\n");

    int tests[3] = {A[0], A[n-1], -1};

    for (int i = 0; i < 3; i++) {

        int keytest = tests[i];
        Cf = 0;

        int pos = BinarySearchIter(A, n, keytest, &Cf);

        printf("Поиск %d -> ", keytest);

        if (pos != -1)
            printf("позиция %d", pos);
        else
            printf("не найден");

        printf(", Cf = %d\n", Cf);
    }

    printf("\nТаблица трудоемкости бинарного поиска\n");
printf("N\tCf (1)\tCf (2)\n");

for (int size = 100; size <= 1000; size += 100)
{
    int B[size];

    FillInc(B, size);

    int key = B[size/2];

    int Cf1 = 0;
    int Cf2 = 0;

    BinarySearchIter(B, size, key, &Cf1);
    BinarySearchAlt(B, size, key, &Cf2);

    printf("%d\t%d\t\t%d\n", size, Cf1, Cf2);
}
    return 0;
}