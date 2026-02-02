#include <ctype.h>

/* Count lowercase letters */
int count_lowercase(const char *str)
{
    int count = 0;
    while (*str)
    {
        if (islower((unsigned char)*str))
            count++;
        str++;
    }
    return count;
}

/* Count uppercase letters */
int count_uppercase(const char *str)
{
    int count = 0;
    while (*str)
    {
        if (isupper((unsigned char)*str))
            count++;
        str++;
    }
    return count;
}

/* Count digits */
int count_digits(const char *str)
{
    int count = 0;
    while (*str)
    {
        if (isdigit((unsigned char)*str))
            count++;
        str++;
    }
    return count;
}
