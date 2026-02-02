#include "perfect.h"
#include "helper.h"

/* Checks perfect number using helper function */
int IsPerfect(int No)
{
    int sum = SumOfFactors(No);  // call helper from libhelper
    return (sum == No);
}
