#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef void (*hello_func)(void);

int main(void)
{
    void *handle;
    hello_func hello;
    char *error;

    
    handle = dlopen("./libmylib.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return 1;
    }

    dlerror(); 

    hello = (hello_func)dlsym(handle, "hello");
    error = dlerror();
    if (error)
    {
        fprintf(stderr, "dlsym failed: %s\n", error);
        dlclose(handle);
        return 1;
    }

    hello();

    dlclose(handle);
    return 0;
}
