#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef int (*math_func)(int, int);

int main()
{
    void *handle;
    math_func add, sub;
    char *error;

    /* Load shared library at runtime */
    handle = dlopen("./libops.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return 1;
    }

    /* Clear any existing error */
    dlerror();

    /* Fetch function address: Addition */
    add = (math_func)dlsym(handle, "Addition");
    error = dlerror();
    if (error)
    {
        fprintf(stderr, "dlsym failed: %s\n", error);
        dlclose(handle);
        return 1;
    }

    /* Fetch function address: Subtraction */
    sub = (math_func)dlsym(handle, "Subtraction");
    error = dlerror();
    if (error)
    {
        fprintf(stderr, "dlsym failed: %s\n", error);
        dlclose(handle);
        return 1;
    }

    /* Call functions */
    printf("Addition: %d\n", add(10, 5));
    printf("Subtraction: %d\n", sub(10, 5));

    /* Close the shared library */
    dlclose(handle);

    return 0;
}


//dlopen()
//Role:
//Loads a shared library at runtime
//Returns a handle to the loaded library
//RTLD_LAZY → symbols resolved only when used

//dlsym()
//Role:
//Fetches the address of a function or variable
//Returned pointer must be type-casted

//dlerror()
//Role:
//Returns a human-readable error message
//Must be called after dlopen / dlsym
//Returns NULL if no error

//dlclose()
//Role:
//Unloads the shared library
//Frees resources
//Should always be called before program exit