#include <stdio.h>
#include "addition.h"
#include "substraction.h"

int main()
{
    int a, b;

    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    printf("Addition: %d\n", Addition(a, b));
    printf("Substraction: %d\n", Substraction(a, b));

    return 0;
}
