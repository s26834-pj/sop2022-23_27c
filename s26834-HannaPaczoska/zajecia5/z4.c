#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void create(int level) {
    if (level > 20) {
        return;
    }
    pid_t pid = fork();

    if (pid < 0) {
        perror("Błąd");
        exit(1);
    } else if (pid == 0) {

        printf("Proces dziecka %d - PID: %d, PPID: %d\n", level, getpid(), getppid());

        wait(NULL);

        exit(0);
    } else {

        wait(NULL);

        printf("Proces parenta %d - PID: %d, PPID: %d\n", level - 1, getpid(), getppid());

        create(level + 1);
    }
}

int main() {
    printf("Proces główny - PID: %d\n", getpid());

    create(1);

    return 0;
}
