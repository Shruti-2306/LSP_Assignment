#include <stdio.h>
#include "helper.h"

int main(void)
{
    int a, b, result;

    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    result = Add(a, b);

    printf("Addition: %d\n", result);

    return 0;
}
