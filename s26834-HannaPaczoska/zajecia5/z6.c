#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MESSAGE_LENGTH 200

void send_message(const char *message) {
    FILE *file = fopen("/tmp/chat.txt", "w");
    if (file == NULL) {
        printf("Błąd.\n");
        exit(1);
    }

    fputs(message, file);
    fclose(file);
}

void receive_message() {
    FILE *file = fopen("/tmp/chat.txt", "r");
    if (file == NULL) {
        printf("Błąd.\n");
        exit(1);
    }

    char  message[MAX_MESSAGE_LENGTH];
    if (fgets(message, sizeof(message), file) != NULL) {
        printf("Message: %s", message);
    }

    fclose(file);
}

int main() {
    char message[MAX_MESSAGE_LENGTH];

    while (1) {
        printf("Write message or 'exit' to exit: ");
        fgets(message, sizeof(message), stdin);

        if (strcmp(message, "exit\n") == 0) {
            break;
        }

        send_message(message);
        receive_message();
    }

    return 0;
}
