#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef int (*arith_func)(int, int);

int main()
{
    void *handle;
    arith_func func;
    int choice, a, b;
    char *error;

   
    handle = dlopen("./libops.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        return 1;
    }

    printf("Choose operation:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    dlerror();  // clear old errors

    switch (choice)
    {
        case 1:
            func = (arith_func)dlsym(handle, "Addition");
            break;
        case 2:
            func = (arith_func)dlsym(handle, "Subtraction");
            break;
        case 3:
            func = (arith_func)dlsym(handle, "Multiplication");
            break;
        case 4:
            func = (arith_func)dlsym(handle, "Division");
            break;
        default:
            printf("Invalid choice\n");
            dlclose(handle);
            return 1;
    }

    error = dlerror();
    if (error)
    {
        fprintf(stderr, "dlsym error: %s\n", error);
        dlclose(handle);
        return 1;
    }

    printf("Result = %d\n", func(a, b));

    
    dlclose(handle);

    return 0;
}
