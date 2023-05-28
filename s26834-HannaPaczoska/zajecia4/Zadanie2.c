#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 200

void reversePrint(int *arr, int size) {
    int i;
    for (i = size - 1; i >= 0; i--) {
        printf("%d\n", arr[i]);
    }
}

int main(int argc, char *argv[]) {
    FILE *file = NULL;
    int *arr = NULL;
    int size, i;

    if (argc > 1) {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("Plik uszkodzony.\n");
            return 1;
        }
    } else {
        printf("Podaj ilość: ");
        scanf("%d", &size);
        if (size <= 0 || size > MAX_SIZE) {
            printf("Nieprawidlowa ilość.\n");
            return 1;
        }

        arr = (int *)malloc(size * sizeof(int));
        if (arr == NULL) {
        printf("Błąd");
        return 1;
        }
        
        printf("Podaj liczby:\n");
        for (i = 0; i < size; i++) {
            if (scanf("%d", &arr[i]) != 1) {
                printf("Zły format.\n");
                free(arr);
                return 1;
            }
        }
    }

    if (file != NULL) {
        if (fscanf(file, "%d", &size) != 1) {
            printf("Nieprawidlowa ilość.\n");
            fclose(file);
            return 1;
        }

        if (size <= 0 || size > MAX_SIZE) {
            printf("Nieprawidlowa ilość.\n");
            fclose(file);
            return 1;
        }

        arr = (int *)malloc(size * sizeof(int));
        if (arr == NULL) {
        printf("Błąd");
        return 1;
        
        for (i = 0; i < size; i++) {
            if (fscanf(file, "%d", &arr[i]) != 1) {
                printf("Zły format.\n");
                fclose(file);
                free(arr);
                return 1;
            }
        }

        fclose(file);
    }

    reversePrint(arr, size);
    free(arr);

    return 0;
    }
}


