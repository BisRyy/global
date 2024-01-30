#include <stdio.h>

int main() {
    int x = 4;
    int y = 6;
    int z = 8;

    x = y + z;
    y = x + z;
    z = x + y;

    // comment will be ignored

    int a = z + y - (x % y) + (x * z) + (y / 2) * (x - y * z); // Another Comment

    printf(a + x + y + z); // prints -7938

    printf(x + y);  // prints 36

    int result = 2 * (x + y);

    printf(result); // prints 72

    int c = 7;

    result = x - y * c;

    printf(result); // prints -140

    a = 4;

    int b = 2;

    result = a * b;

    printf(result); // prints 8

    printf("string");

    return 0;
}
