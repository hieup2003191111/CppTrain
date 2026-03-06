#include <stdio.h>
#include "include/mylib.h"

int main() {
    hello();
    
    int result1 = add(10, 5);
    int result2 = subtract(10, 5);
    
    printf("10 + 5 = %d\n", result1);
    printf("10 - 5 = %d\n", result2);
    
    return 0;
}
