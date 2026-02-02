#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char *argv[])
{
    void *handle;
    void *symbol;
    char *error;

    if (argc != 3)
    {
        fprintf(stderr,
                "Usage: %s <shared_library_path> <symbol_name>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    /* Load shared library */
    handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return EXIT_FAILURE;
    }

    /* Clear any existing errors */
    dlerror();

    /* Look up symbol */
    symbol = dlsym(handle, argv[2]);
    error = dlerror();

    if (error)
    {
        fprintf(stderr,
                "Symbol '%s' not found: %s\n",
                argv[2], error);
        dlclose(handle);
        return EXIT_FAILURE;
    }

    /* Symbol found */
    printf("Symbol '%s' found\n", argv[2]);
    printf("Address: %p\n", symbol);

    dlclose(handle);
    return EXIT_SUCCESS;
}
