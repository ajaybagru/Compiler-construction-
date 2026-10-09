#include <stdio.h>

#define PI 3.14159
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int num = 5;

    printf("Value of PI: %.5f\n", PI);
    printf("Square of %d: %d\n", num, SQUARE(num));
    printf("Max of 10 and 20: %d\n", MAX(10, 20));

    return 0;
}
