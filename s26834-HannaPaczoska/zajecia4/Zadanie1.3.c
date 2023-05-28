#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int liczba;
    int i, j, k;

    if (argc != 2) {
        printf("Podaj liczbę gwiazdek.\n");
        return 1;
    }

    liczba = atoi(argv[1]);

    if (liczba <= 0) {
        printf("Liczba gwiazdek musi być większa od zera.\n");
        return 1;
    }
    
    for (i = 1; i <= liczba; i++) {

    
        for (j = 0; j < liczba - i; j++) {
            printf(" ");
        }

    
        for (k = 0; k < (2 * i - 1); k++) {
            printf("*");
        }

        printf("\n");
    }

    return 0;
}
