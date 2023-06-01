#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LOCK_FILE_PATH "/tmp/lock"

void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Wykryto próbę uruchomienia drugiej instancji programu.\n");
    }
}

void cleanup() {
    /* Usuń plik blokady */
    remove(LOCK_FILE_PATH);
}

int main() {
    /* Sprawdź, czy plik blokady istnieje */
    FILE* lock_file = fopen(LOCK_FILE_PATH, "r");
    if (lock_file) {
        /* Plik blokady istnieje, wczytaj PID i wyślij sygnał SIGUSR1 */
        pid_t pid;
        fscanf(lock_file, "%d", &pid);
        fclose(lock_file);

        kill(pid, SIGUSR1);
        return 0;
    }

    /* Utwórz plik blokady i zapisz PID */
    lock_file = fopen(LOCK_FILE_PATH, "w");
    if (!lock_file) {
        printf("Nie można utworzyć pliku blokady.\n");
        return 1;
    }

    fprintf(lock_file, "%d", getpid());
    fclose(lock_file);

    /* Zarejestruj obsługę sygnałów */
    signal(SIGUSR1, signal_handler);
    signal(SIGINT, cleanup);

    /* Pętla nieskończona z opóźnieniem */
    while (1) {
        sleep(1);
    }

    return 0;
}
