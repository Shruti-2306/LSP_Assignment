#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

typedef int (*count_func)(const char *);

int main(void)
{
    void *handle;
    count_func count_lower, count_upper, count_digit;
    char str[256];
    char *error;

    /* Take string input */
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';   // remove newline

    /* Load shared library */
    handle = dlopen("./libstringops.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return 1;
    }

    dlerror(); // clear old errors

    /* Load functions */
    count_lower = (count_func)dlsym(handle, "count_lowercase");
    count_upper = (count_func)dlsym(handle, "count_uppercase");
    count_digit = (count_func)dlsym(handle, "count_digits");

    error = dlerror();
    if (error)
    {
        fprintf(stderr, "dlsym failed: %s\n", error);
        dlclose(handle);
        return 1;
    }

    /* Call functions */
    printf("Lowercase letters: %d\n", count_lower(str));
    printf("Uppercase letters: %d\n", count_upper(str));
    printf("Digits: %d\n", count_digit(str));

    dlclose(handle);
    return 0;
}
