//client
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef int (*math_func_t)(int, int);

int main()
{
    void *handle;
    math_func_t add, sub;
    char *error;

    
    handle = dlopen("./libops.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        return EXIT_FAILURE;
    }

    dlerror(); 

  
    add = (math_func_t)dlsym(handle, "Addition");
    error = dlerror();
    if (error) {
        fprintf(stderr, "dlsym error: %s\n", error);
        dlclose(handle);
        return EXIT_FAILURE;
    }

    sub = (math_func_t)dlsym(handle, "Substraction");
    error = dlerror();
    if (error) {
        fprintf(stderr, "dlsym error: %s\n", error);
        dlclose(handle);
        return EXIT_FAILURE;
    }

    
    printf("Addition(11, 21) = %d\n", add(11, 21));
    printf("Substraction(21, 11) = %d\n", sub(21,11));

  
    dlclose(handle);

    return EXIT_SUCCESS;
}
