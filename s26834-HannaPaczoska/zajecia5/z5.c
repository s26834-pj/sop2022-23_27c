#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;
    int status;
    int i;
    printf("Proces główny - PID: %d\n", getpid());

    for (i = 1; i <= 20; i++) {
        child_pid = fork();

        if (child_pid < 0) {
            perror("Błąd");
            exit(1);
        } else if (child_pid == 0) {

            printf("Proces dziecka %d - PID: %d, PPID: %d\n", i, getpid(), getppid());

            exit(0);
        }
    }

    while ((child_pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            printf("Proces dziecka %d zakończony:  %d\n", child_pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Proces potomny %d zakończony: %d\n", child_pid, WTERMSIG(status));
        }
    }

    return 0;
}
