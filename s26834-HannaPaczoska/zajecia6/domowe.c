#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_REQUEST_SIZE 4096
#define MAX_RESPONSE_SIZE 4096
#define LOG_FILE_PATH "http_server.log"

typedef struct {
    char address[16];
    int port;
} VirtualHost;

VirtualHost virtual_hosts[] = {
    {"localhost", 8080},
    {"example.com", 80},
   /*  Dodaj inne wirtualne hosty tutaj */
    {"", 0}  /*  Znak końca listy */
};

char forbidden_addresses[][16] = {
    "192.168.0.1",
    "10.0.0.2",
    /*  Dodaj inne zabronione adresy tutaj*/
};

int is_forbidden_address(const char* address) {
    int i = 0;
    while (strlen(forbidden_addresses[i]) > 0) {
        if (strcmp(forbidden_addresses[i], address) == 0) {
            return 1;  /*  Znaleziono zabroniony adres */
        }
        i++;
    }
    return 0;  /*  Adres nie jest zabroniony */
}

void log_event(const char* message) {
    FILE* log_file = fopen(LOG_FILE_PATH, "a");
    if (log_file) {
        fprintf(log_file, "%s\n", message);
        fclose(log_file);
    }
}

void handle_client(int client_socket, const char* client_ip, int client_port) {
    /*  Odbieranie żądania od klienta */
    char request[MAX_REQUEST_SIZE];
    ssize_t request_length = recv(client_socket, request, sizeof(request) - 1, 0);
    if (request_length == -1) {
        perror("Błąd podczas odbierania żądania");
        close(client_socket);
        exit(1);
    }

    request[request_length] = '\0';  /* Dodanie znaku null na końcu żądania*/

    /* Sprawdzanie, czy adres jest zabroniony */
    if (is_forbidden_address(client_ip)) {
        const char* forbidden_message = "403 Forbidden\n";
        send(client_socket, forbidden_message, strlen(forbidden_message), 0);
        close(client_socket);
        exit(0);
    }

    /*  Tworzenie odpowiedzi serwera */
    char response[MAX_RESPONSE_SIZE];
    snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\n"
                                          "Content-Type: text/html\r\n"
                                          "\r\n"
                                          "<html><body>"
                                          "<h1>Witaj, odwiedzający z adresu %s:%d!</h1>"
                                          "</body></html>",
                                          client_ip, client_port);

    /* Wysyłanie odpowiedzi do klienta */
    ssize_t response_length = strlen(response);
    ssize_t sent_length = send(client_socket, response, response_length, 0);
    if (sent_length == -1) {
        perror("Błąd podczas wysyłania odpowiedzi");
    } else if (sent_length < response_length) {
        printf("Nie udało się wysłać całej odpowiedzi\n");
    }

    /*  Logowanie zdarzenia */
    char log_message[128];
    snprintf(log_message, sizeof(log_message), "Połączono: %s:%d", client_ip, client_port);
    log_event(log_message);

    /*  Zamykanie gniazda klienta */
    close(client_socket);
    exit(0);
}

void handle_sigchld(int signal) {
    /*  Obsługa sygnału SIGCHLD */
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    /*  Tworzenie gniazda serwera */
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Błąd podczas tworzenia gniazda serwera");
        return 1;
    }

    /*  Ustalanie opcji SO_REUSEADDR */
    int reuse = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        perror("Błąd podczas ustawiania opcji SO_REUSEADDR");
        return 1;
    }

    /*  Konfiguracja adresu i portu serwera */
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(80);  /* Port HTTP*/

    /* Przypisywanie adresu i portu do gniazda serwera */
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Błąd podczas przypisywania adresu i portu do gniazda serwera");
        return 1;
    }

    /*  Nasłuchiwanie na połączenia */
    if (listen(server_socket, SOMAXCONN) == -1) {
        perror("Błąd podczas nasłuchiwania na połączenia");
        return 1;
    }

    /*  Obsługa sygnału SIGCHLD */
    signal(SIGCHLD, handle_sigchld);

    while (1) {
        /*  Akceptowanie połączenia od klienta */
        struct sockaddr_in client_address;
        socklen_t client_address_size = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);
        if (client_socket == -1) {
            perror("Błąd podczas akceptowania połączenia");
            continue;
        }

        /* Tworzenie nowego procesu dla obsługi klienta */
        pid_t pid = fork();
        if (pid == -1) {
            perror("Błąd podczas tworzenia procesu potomnego");
            close(client_socket);
            continue;
        } else if (pid == 0) {
            /* Proces potomny obsługuje klienta */
            close(server_socket);  /* Zamknięcie gniazda serwera w procesie potomnym */
            char client_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);
            int client_port = ntohs(client_address.sin_port);
            handle_client(client_socket, client_ip, client_port);
        } else {
            /* Proces macierzysty kontynuuje nasłuchiwanie na połączenia */
            close(client_socket);  /* Zamknięcie gniazda klienta w procesie macierzystym */
        }
    }

    /* Zamykanie gniazda serwera */
    close(server_socket);

    return 0;
}
