#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int  n = atoi(argv[1]); 
    pid_t pid = fork();

    if (argc != 2) {
        printf("Użycie: %s <liczba>\n", argv[0]);
        return 1;
    }

    if (pid < 0) {
        perror("Błąd");
        return 1;
    } else if (pid == 0) {
       int i;

        printf("Proces dziecka - nieparzyste: ");
        for (i = 1; i <= n; i += 2) {
            printf("%d ", i);
        }
        printf("\n");

        exit(0);
    } else {

        int i = 0; 
        int sum = 0;
        for (; i <= n; i++) {
            sum += i;
        }

       
        wait(NULL);

        printf("Proces parenta - suma: %d\n", sum);
    }

    return 0;
}
