#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Otrzymano sygnał SIGUSR1\n");
        exit(0);
    }
}

int main() {
    printf("PID: %d\n", getpid());

    /* Zarejestruj obsługę sygnału */
    signal(SIGUSR1, signal_handler);

    /* Oczekiwanie na sygnał użytkownika w pętli nieskończonej */
    while (1) {
        /* Czekaj na sygnał */
        pause();
    }

    return 0;
}

