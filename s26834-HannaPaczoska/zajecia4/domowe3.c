#include <stdio.h>


int fibonacciRecursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int main() {
    int n;
    int i;

    printf("Podaj n: ");
    scanf("%d", &n);

    printf("Ciąg rekurencyjnie: ");
    for (i = 0; i <= n; i++) {
        printf("%d ", fibonacciRecursive(i));
    }
    printf("\n");

    return 0;
}
