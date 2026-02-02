#include <stdio.h>
#include "perfect.h"

int main()
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (IsPerfect(num))
        printf("%d is a perfect number\n", num);
    else
        printf("%d is not a perfect number\n", num);

    return 0;
}
