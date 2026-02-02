#include <stdio.h>
#include <string.h>
#include "display.h"

void Display(char *str)
{
    int len = strlen(str);

    printf("String: %s\n", str);
    printf("Total characters: %d\n", len);
}
