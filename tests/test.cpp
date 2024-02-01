#include <iostream>
using namespace std;

int main()
{
    int x = 4;
    int y = 6;
    int z = 8;

    x = y + z;
    y = x + z;
    z = x + y;

    // comment will be ignored

    int a = z + y - (x % y) + (x * z) + (y / 2) * (x - y * z); // Another Comment

    cout << (a + x + y + z) << endl; // prints -7938

    cout << (x + y) << endl; // prints 36

    int result = 2 * (x + y);

    cout << result << endl; // prints 72

    int c = 7;

    result = x - y * c;

    cout << result << endl; // prints -140

    a = 4;

    int b = 2;

    result = a * b;

    cout << result << endl; // prints 8

    cout << "string" << endl;

    return 0;
}
