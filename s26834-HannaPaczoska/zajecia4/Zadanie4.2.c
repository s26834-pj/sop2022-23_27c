#include <stdio.h>

int max(int x, int y) {
    return (x > y) ? x : y;
}

int min(int x, int y) {
    return (x < y) ? x : y;
}

int sum(int x, int y) {
    return x + y;
}

int forAll(int *array, int size, int (*func)(int, int)) {
    int i;
    int result = array[0];
    for (i = 1; i < size; i++) {
        result = func(result, array[i]);
    }
    return result;
}

int main() {
    int array[] = {127, 34, 43, 78, 566};
    int size = sizeof(array) / sizeof(array[0]);

    int result = forAll(array, size, max);
    printf("Maksimum: %d\n", result);

    result = forAll(array, size, min);
    printf("Minimum: %d\n", result);

    result = forAll(array, size, sum);
    printf("Suma: %d\n", result);

    return 0;
}
