#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

long Mf = 0;
long Cf = 0;

void FillInc(int* A, int n) {
    for (int i = 0; i < n; i++) A[i] = i;
}

void FillDec(int* A, int n) {
    for (int i = 0; i < n; i++) A[i] = (n-i);
}

void FillRand(int* A, int n) {
    for (int i = 0; i < n; i++) A[i] = rand() % (123 * n);
}

int CheckSum(int* A, int n) {
    int s = 0;
    for (int i = 0; i < n; i++) s += A[i];
    return s;
}

int RunNumber(int* A, int n) {
    if (n < 1) return 0;
    int series = 0;
    for (int i = 0; i < n-1; i++)
        if (!(A[i] <= A[i+1])) series++;
    series++;
    return series;
}

void PrintMas(int* A, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void InsertSort(int* A, int n) {
    for (int i = 1; i < n; i++) {
        int temp = A[i];
        int j = i;
        while (j > 0) {
            Cf++;
            if (A[j-1] > temp) {
                A[j] = A[j-1];
                Mf++;
                j--;
            } else break;
        }
        A[j] = temp;
        Mf++;
    }
}

void ShellSort(int* A, int n, int* firstStep, int* lastStep) {
    int h[50], k = 0;
    int g = 1;
    while (g < n/3) { h[k++] = g; g = 3*g + 1; }

    if (k>0) {
        *firstStep = h[0];
        *lastStep = h[k-1];
    } else {
        *firstStep = 1;
        *lastStep = 1;
    }

    for (int idx = k-1; idx >=0; idx--) {
        int gap = h[idx];
        for (int i = gap; i < n; i++) {
            int temp = A[i];
            int j = i;
            while (j >= gap) {
                Cf++;
                if (A[j-gap] > temp) {
                    A[j] = A[j-gap];
                    Mf++;
                    j -= gap;
                } else break;
            }
            A[j] = temp;
            Mf++;
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    srand(time(NULL));

    printf("Демонстрация сортировки массива\n");
    int n_demo = 20;
    int A_demo[20];
    FillRand(A_demo, n_demo);

    printf("Исходный массив:\n");
    PrintMas(A_demo, n_demo);

    int sum_before = CheckSum(A_demo, n_demo);
    int series_before = RunNumber(A_demo, n_demo);

    Mf = 0; Cf = 0;
    ShellSort(A_demo, n_demo, &(int){0}, &(int){0});
    int sum_after = CheckSum(A_demo, n_demo);
    int series_after = RunNumber(A_demo, n_demo);

    printf("\nОтсортированный массив:\n");
    PrintMas(A_demo, n_demo);

    printf("\nКонтрольная сумма до: %d\n", sum_before);
    printf("Контрольная сумма после: %d\n", sum_after);
    printf("Число серий до сортировки: %d\n", series_before);
    printf("Число серий после сортировки: %d\n", series_after);
    printf("Фактические операции:\nMf (пересылки) = %ld\nCf (сравнения) = %ld\n", Mf, Cf);

    printf("\nИсследование трудоемкости ShellSort и InsertSort\n");
    int ns[] = {100, 200, 300, 400, 500};
    int n_tests = 5;

    printf("n\th1...hm\tInsert Mf+Cf\tShell Mf+Cf\n");

    for (int t = 0; t < n_tests; t++) {
        int n = ns[t];
        int A[600], B[600];
        FillRand(A,n);
        for (int i=0;i<n;i++) B[i] = A[i];

        int firstStep, lastStep;

        Mf = 0; Cf = 0;
        ShellSort(A,n,&firstStep,&lastStep);
        long shellT = Mf + Cf;

        Mf = 0; Cf = 0;
        InsertSort(B,n);
        long insertT = Mf + Cf;

        printf("%d\t%d  %d\t%ld\t\t%ld\n", n, firstStep, lastStep, insertT, shellT);
    }

    return 0;
}