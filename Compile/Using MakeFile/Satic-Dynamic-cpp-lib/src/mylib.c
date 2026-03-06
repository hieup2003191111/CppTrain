#include <stdio.h>
#include "../include/mylib.h"

#ifdef _WIN32
    #define BUILDING_DLL
#endif

void hello() {
    printf("Hello from library!\n");
}

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}
