#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

/* Function pointer type */
typedef int (*math_func)(int, int);

int main(void)
{
    void *handle;
    math_func funcs[3];     // array of function pointers
    const char *names[] = {"add", "sub", "mul"};
    int a = 10, b = 5;
    char *error;
    int i;

    /* Load shared library */
    handle = dlopen("./libmathops.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return 1;
    }

    dlerror(); // clear old errors

    /* Load function addresses into array */
    for (i = 0; i < 3; i++)
    {
        funcs[i] = (math_func)dlsym(handle, names[i]);
        error = dlerror();
        if (error)
        {
            fprintf(stderr, "dlsym failed for %s: %s\n", names[i], error);
            dlclose(handle);
            return 1;
        }
    }

    /* Invoke functions via array */
    for (i = 0; i < 3; i++)
    {
        printf("Function: %s\n", names[i]);
        printf("Address : %p\n", (void *)funcs[i]);
        printf("Result  : %d\n\n", funcs[i](a, b));
    }

    dlclose(handle);
    return 0;
}
