#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef void (*func_t)(void);

int main(void)
{
    void *handle;
    func_t increment, display, reset;
    char *error;

    /* Load shared library */
    handle = dlopen("./libglob.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return 1;
    }

    /* Clear old errors */
    dlerror();

    increment = (func_t)dlsym(handle, "increment");
    display   = (func_t)dlsym(handle, "display");
    reset     = (func_t)dlsym(handle, "reset");

    error = dlerror();
    if (error)
    {
        fprintf(stderr, "dlsym failed: %s\n", error);
        dlclose(handle);
        return 1;
    }

    /* Demonstrate persistence */
    display();     // 0
    increment();
    increment();
    display();     // 2
    increment();
    display();     // 3
    reset();
    display();     // 0

    dlclose(handle);
    return 0;
}
