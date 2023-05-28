#include <stdio.h>


void fibonacciIterative(int n) {
    int i;
    int fib[n + 1];
    fib[0] = 0;
    fib[1] = 1;

    printf("Ciąg iteracyjnie: ");

    for (i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    for (i = 0; i <= n; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Podaj n: ");
    scanf("%d", &n);

    fibonacciIterative(n);

    return 0;
}
