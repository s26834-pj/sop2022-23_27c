#include <stdio.h>
#include <stdlib.h>

int max(int x, int y) {
    return (x > y) ? x : y;
}

int min(int x, int y) {
    return (x < y) ? x : y;
}

int sum(int x, int y) {
    return x + y;
}

int main() {
    int (*functions[3])(int, int) = {max, min, sum};
    int id, element;

    int i;
    int v;

    printf("Podaj numer (0 - maksimum, 1 - minimum, 2 - suma): ");
    scanf("%d", &id);

    printf("Podaj liczbę elementów: ");
    scanf("%d", &element);

    int *numbers = (int *)malloc(element * sizeof(int));
    if (numbers == NULL) {
        printf("Błąd.\n");
        return 1;
    }

    printf("Podaj liczby:\n");
  
    for (i = 0; i < element; i++) {
        scanf("%d", &numbers[i]);
    }

    v = numbers[0];
    for (i = 1; i < element; i++) {
        v = functions[id](v, numbers[i]);
    }

    printf("Wynik: %d\n", v);

    free(numbers);

    return 0;
}
