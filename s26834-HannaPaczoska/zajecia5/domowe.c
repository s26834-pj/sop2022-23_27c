#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int processes = 0;

void child(int process_name, pid_t parent_pid) {
    pid_t pid = fork();
        if (pid < 0) {
        perror("B   ^b   ^ed fork");
        exit(1);

    } else if (pid == 0) {
        printf("Proces %d - PID: %d, PPID: %d\n", process_name, getpid(), parent_pid);
        if (process_name == 1) {
            child(2, getpid());
            child(3, getpid());
        } else if (process_name == 2) {
            child(4, getpid());
            child(5, getpid());
        } else if (process_name == 3) {
            child(6, getpid());
            child(7, getpid());
        }

        exit(0);
    } else {
        processes++;
    }
}

int main() {

    printf("Proces glowny - PID: %d\n", getpid());
    child(1, getpid());
    while (processes > 0) {
        wait(NULL);
        processes--;
    }
    return 0;
}
