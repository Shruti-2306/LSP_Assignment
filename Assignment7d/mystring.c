#include "mystring.h"

/*
 * Returns length of string
 * If str is NULL, returns -1 (safe handling)
 */
int MyStrlen(const char *str)
{
    int len = 0;

    if (str == 0)   /* NULL check */
        return -1;

    while (str[len] != '\0')
        len++;

    return len;
}
