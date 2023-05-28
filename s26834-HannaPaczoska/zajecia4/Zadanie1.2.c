#include <stdio.h>

int main() {
    int n, liczba, suma = 0;
    int i;

    printf("Podaj ilość liczb: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        printf("Podaj liczbę %d: ", i);
        scanf("%d", &liczba);
        suma += liczba;
    }

    printf("Suma: %d\n", suma);

    return suma;
}
