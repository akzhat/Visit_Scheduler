#include <stdio.h>
#include <iostream>
#include <fstream>

void swap(int *A, int *B)
{
    int temp;
    temp = *A;
    *A = *B;
    *B = temp;
}

void scheduling(int A[], int size, int *a, int *b, int *final, int *maxl, int maxb)
{
    int this_maxl = 0, len[maxb];
    for (int i = 0; i <= maxb; i++)
    {
        len[i] = i;
    }

    int lb = 0, ub = maxb;
    while (lb <= ub)
    {
        int flag = 1;
        int mid = (lb + ub) / 2;
        int start = a[A[0]];
        for (int i = 1; i < size; i++)
        {
            start = a[A[i]] > (start + len[mid]) ? a[A[i]] : (start + len[mid]);
            if (start > b[A[i]])
            {
                ub = mid - 1;
                flag = 0;
                break;
            }
        }
        if (flag == 0)
        {
            continue;
        }
        else
        {
            this_maxl = len[mid];
            lb = mid + 1;
            continue;
        }
    }
}

void permutation_generate(int *A, int s, int f, int *a, int *b, int *final, int *maxl, int maxb)
{
    if (s == f)
    {
        scheduling(A, f + 1, a, b, final, maxl, maxb);
        return;
    }
    for (int i = s; i <= f; i++)
    {
        swap((A + i), (A + s));
        permutation_generate(A, s + 1, f, a, b, final, maxl, maxb);
        swap((A + i), (A + s));
    }
}

int main()
{
    int n, maxl = 0, maxb = 0;
    FILE *fp = fopen("input1.txt", "r+");
    if (fp == NULL)
        return -1;

    fscanf(fp, "%d", &n);

    int a[n];
    int b[n];

    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &a[i]);
        fscanf(fp, "%d", &b[i]);
        if (maxb < b[i])
            maxb = b[i];
    }

    for (int i = 0; i < n; i++)
    {
        a[i] *= 60;
        b[i] *= 60;
    }
    maxb *= 60;

    int A[n];
    for (int i = 0; i < n; i++)
    {
        A[i] = i;
    }

    int final[n];

    permutation_generate(A, 0, n - 1, a, b, final, &maxl, maxb);

    FILE *writer = fopen("output1.txt", "w+");

    int min = maxl / 60;
    int sec = maxl % 60;

    if (sec < 10)
    {
        fprintf(writer, "%d:0%d\n", min, sec);
    }
    else
    {
        fprintf(writer, "%d:%d\n", min, sec);
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(writer, "%d ", final[i]);
    }

    fclose(writer);
    fclose(fp);
    return 0;
}
