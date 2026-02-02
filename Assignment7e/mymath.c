#include "mymath.h"

int MyAbs(int x)
{
    return x < 0 ? -x : x;
}

int MyMax(int a, int b)
{
    return a > b ? a : b;
}

int MyMin(int a, int b)
{
    return a < b ? a : b;
}

long MyFactorial(int n)
{
    long fact = 1;
    for (int i = 1; i <= n; i++)
        fact *= i;
    return fact;
}

int MyGCD(int a, int b)
{
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int MyLCM(int a, int b)
{
    return (a * b) / MyGCD(a, b);
}

double MyPow(double base, int exp)
{
    double result = 1.0;
    for (int i = 0; i < MyAbs(exp); i++)
        result *= base;
    return exp < 0 ? 1.0 / result : result;
}

double MySqrt(double n)
{
    double x = n, y = 1.0;
    double eps = 0.00001;
    while ((x - y) > eps) {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}
