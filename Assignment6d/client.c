#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef int (*math_func)(int, int);

int main(void)
{
    void *handle;
    math_func func;
    char *error;

   
    handle = dlopen("./libops.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return EXIT_FAILURE;
    }

    printf("Shared library loaded successfully.\n");

    
    dlerror();

    /* Case 1: Valid symbol */
    func = (math_func)dlsym(handle, "add");
    error = dlerror();
    if (error)
    {
        fprintf(stderr, "dlsym failed for 'add': %s\n", error);
    }
    else
    {
        printf("Function 'add' found. Result: %d\n", func(10, 20));
    }

   
    dlerror();

    /* Case 2: Invalid / missing symbol */
    func = (math_func)dlsym(handle, "multiply");  // does NOT exist
    error = dlerror();
    if (error)
    {
        fprintf(stderr,
                "dlsym failed for 'multiply': %s\n",
                error);
    }
    else
    {
        printf("Function 'multiply' found (unexpected).\n");
    }

   
    dlclose(handle);
    printf("Shared library closed.\n");

    return EXIT_SUCCESS;
}
