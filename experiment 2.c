#include <stdio.h>

int main() {
    int n = 10; // Number of terms to print
    int a = 0, b = 1, next;

    printf("Fibonacci Series: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", a);
        next = a + b; // 1. Calculate next term
        a = b;        // 2. Move 'b' to 'a'
        b = next;     // 3. Move 'next' to 'b'
    }

    return 0;
}
