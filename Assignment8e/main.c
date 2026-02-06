#include <stdio.h>
#include "math.h"

int main(void)
{
    int a, b;

    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    printf("Add: %d\n", Add(a, b));
    printf("Sub: %d\n", Sub(a, b));
    printf("Mul: %d\n", Mul(a, b));
    printf("Div: %d\n", Div(a, b));

    return 0;
}
