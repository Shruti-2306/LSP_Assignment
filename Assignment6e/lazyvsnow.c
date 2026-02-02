#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

typedef int (*func_t)(void);

void test_lazy()
{
    void *handle;
    func_t f;
    char *err;

    printf("\n--- Loading with RTLD_LAZY ---\n");

    handle = dlopen("./libdemo.so", RTLD_LAZY);
    if (!handle)
    {
        printf("dlopen(LAZY) failed: %s\n", dlerror());
        return;
    }

    printf("Library loaded with RTLD_LAZY\n");

    dlerror();  // clear error
    f = (func_t)dlsym(handle, "missing_function");
    err = dlerror();

    if (err)
        printf("Error appears only at dlsym: %s\n", err);

    dlclose(handle);
}

void test_now()
{
    void *handle;

    printf("\n--- Loading with RTLD_NOW ---\n");

    handle = dlopen("./libdemo.so", RTLD_NOW);
    if (!handle)
    {
        printf("dlopen(NOW) failed immediately: %s\n", dlerror());
        return;
    }

    printf("Library loaded with RTLD_NOW (unexpected)\n");
    dlclose(handle);
}

int main()
{
    test_lazy();
    test_now();
    return 0;
}
