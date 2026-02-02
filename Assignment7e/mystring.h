#include <stdio.h>
#include<string.h>
//#include "display.h"

int main()
{
    char str[256];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    /* remove newline added by fgets */
    str[strcspn(str, "\n")] = '\0';

    Display(str);

    return 0;
}
