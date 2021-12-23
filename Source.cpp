#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void random(int * arr, const int n)
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 2;
}

void print(int* arr, const int n)
{
    for (int i = 0; i < n; i++)
        printf("%d", arr[i]);
    printf("\n_______________________\n\n");
}

double test1(int* arr, const int n)
{
    double s = 0.0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 1)
            s += 1;
        else
            s += -1;
    }
    s /= sqrt(n);
    printf("S = %lf\n\n", s);
    return erfc(s / sqrt(2));
}

double test2(int* arr, const int n)
{
    double z = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 1)
            z++;
    }
    z /= n;
    printf("Z = %lf\n\n", z);
    if (fabs(z - 0.5) >= (2.0 / sqrt(n)))
        return 0.0;
    else
    {
        double v = 0;
        for (int i = 0, current = arr[0]; i < n - 1; i++)
        {
            if (arr[i] != arr[i + 1])
                v++;
        }
        printf("V = %lf\n\n", v);
        double p = fabs(v - 2.0 * n * z * (1.0 - z));
        p /= 2 * sqrt(2.0 * n) * z * (1.0 - z);
        return erfc(p);
    }
}

double test3(int * arr, const int n)
{
    int v[4] = {0 , 0 , 0, 0};
    for (int i = 0, end = i + 8; i < n; i += 8, end += 8)
    {
        int max = 0;
        for (int j = i, n = 0; j < end; j++)
        {
            printf("%d", arr[j]);
            if (arr[j] == 1) 
                n++;
            else 
                n = 0;
            if (n > max) 
                max = n;
        }
        printf(" | max 1 = %d\n", max);
        if (max <= 1)
            v[0]++;
        else
        {
            if (max == 2)
                v[1]++;
            else
                if (max == 3)
                    v[2]++;
                else
                    v[3]++;
        }
    }
    printf("\n\nV1 = %d\nV2 = %d\nV3 = %d\nV4 = %d\n\n", v[0], v[1], v[2], v[3]);
    const double pi[4] = { 0.2148, 0.3672, 0.2305, 0.1875 };
    double x = 0;
    for (int i = 0; i < 4; i++)
    {
        x += ((v[i] - 16 * pi[i]) * (v[i] - 16 * pi[i])) / 16 * pi[i];
    }
    return x;
}

int main()
{
    int arr[128];
    int n = 128;
    random(arr, n);
    print(arr, n);
    printf("TEST 1\nP value = %lf\n_______________________\n\n", test1(arr, n));
    printf("TEST 2\nP value = %lf\n_______________________\n\n", test2(arr, n));
    printf("\nTEST 3\nX^2 = %lf\n_______________________\n\n", test3(arr, n));
    return 0;
}