#include <stdio.h>

void drukuj(FILE *file) {
    unsigned int a = 0;
    unsigned int byte;
    
    while ((byte = fgetc(file)) != EOF) {
        if (a % 16 == 0) {
            printf("%08X ", a);
        }
        
        printf("%02X ", byte);
        
        if (a % 16 == 7 || a % 16 == 15) {
            printf(" ");
        }
        
        a++;
        
        if (a % 16 == 0) {
            printf("\n");
        }
    }
    
    if (a % 16 != 0) {
        unsigned int spaces = (16 - a % 16) * 3;
        
        if (a % 16 <= 7) {
            spaces += 1;
        }
        unsigned int i;        
        for (i = 0; i < spaces; i++) {
            printf(" ");
        }
    }
    
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Podaj argument.\n");
        return 1;
    }
    
    FILE *file = fopen(argv[1], "rb");
    
    if (file == NULL) {
        printf("Plik uszkodzony.\n");
        return 1;
    }
    
    printf("Wczytanie pliku: %s\n", argv[1]);
    
    drukuj(file);
    
    printf("Zamknięcie pliku: %s\n", argv[1]);
    
    fclose(file);
    
    return 0;
}
