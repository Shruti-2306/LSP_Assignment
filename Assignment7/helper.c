#include "helper.h"

/* Compute sum of proper factors */
int SumOfFactors(int No)
{
    int sum = 0;
    for (int i = 1; i <= No / 2; i++)
    {
        if (No % i == 0)
            sum += i;
    }
    return sum;
}
