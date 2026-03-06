#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *handle = dlopen("./libdynlib.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        return 1;
    }
    void (*hello_dyn)();
    *(void **) (&hello_dyn) = dlsym(handle, "hello_dyn");
    if (!hello_dyn) {
        fprintf(stderr, "dlsym error: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }
    hello_dyn();
    dlclose(handle);
    return 0;
}
