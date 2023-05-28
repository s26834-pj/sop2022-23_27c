#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid, ppid;

    pid = getpid();
    ppid = getppid();

    printf("PID: %d\n", pid);
    printf("PPID: %d\n", ppid);

    printf("Czekam na dane\n");

    char input[100];
    fgets(input, sizeof(input), stdin);

    printf("Dane: %s", input);

    return 0;
}
