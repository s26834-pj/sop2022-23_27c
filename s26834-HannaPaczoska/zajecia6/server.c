#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_FILENAME_LENGTH 256
#define BUFFER_SIZE 1024
#define LOG_FILE_PATH "server.log"

void log_connection(const char* client_ip, int client_port, const char* filename) {
    FILE* log_file = fopen(LOG_FILE_PATH, "a");
    if (log_file) {
        fprintf(log_file, "Connected: %s:%d, File: %s\n", client_ip, client_port, filename);
        fclose(log_file);
    }
}

ssize_t get_file_size(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        return -1;
    }

    fseek(file, 0, SEEK_END);
    ssize_t file_size = ftell(file);
    fclose(file);

    return file_size;
}

int main() {
    /* Tworzenie gniazda nasłuchującego */
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Błąd podczas tworzenia gniazda");
        exit(1);
    }

    /* Ustawianie opcji gniazda */
    int option = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int)) == -1) {
        perror("Błąd podczas ustawiania opcji gniazda");
        exit(1);
    }

    /* Dane serwera */
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);  /* Port serwera */
    server_address.sin_addr.s_addr = INADDR_ANY;

    /* Przypisywanie gniazda do adresu i portu */
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Błąd podczas przypisywania gniazda do adresu i portu");
        exit(1);
    }

    /* Nasłuchiwanie na połączenia */
    if (listen(server_socket, 5) == -1) {
        perror("Błąd podczas nasłuchiwania na połączenia");
        exit(1);
    }

    /* Obsługa sygnału Ctrl+C (SIGINT) */
    signal(SIGINT, exit);

    printf("Serwer nasłuchuje na porcie 12345...\n");

    while (1) {
        /* Akceptowanie połączenia */
        struct sockaddr_in client_address;
        socklen_t client_address_length = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
        if (client_socket == -1) {
            perror("Błąd podczas akceptowania połączenia");
            continue;
        }

        /* Informacje o połączeniu */
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);
        int client_port = ntohs(client_address.sin_port);

        /* Odbieranie nazwy pliku */
        size_t filename_length;
        if (recv(client_socket, &filename_length, sizeof(size_t), 0) == -1) {
            perror("Błąd podczas odbierania długości nazwy pliku");
            close(client_socket);
            continue;
        }

        char filename[MAX_FILENAME_LENGTH];
        if (recv(client_socket, filename, filename_length, 0) == -1) {
            perror("Błąd podczas odbierania nazwy pliku");
            close(client_socket);
            continue;
        }
        filename[filename_length] = '\0';  /* Dodanie znaku null na końcu nazwy pliku */

        /* Logowanie połączenia */
        log_connection(client_ip, client_port, filename);

        /* Pobieranie wielkości pliku */
        ssize_t file_size = get_file_size(filename);

        /* Wysyłanie wielkości pliku */
        if (send(client_socket, &file_size, sizeof(ssize_t), 0) == -1) {
            perror("Błąd podczas wysyłania wielkości pliku");
            close(client_socket);
            continue;
        }

        /* Sprawdzanie, czy plik istnieje */
        if (file_size == -1) {
            close(client_socket);
            continue;
        }

        /* Wysyłanie danych pliku */
        int file = open(filename, O_RDONLY);
        if (file == -1) {
            perror("Błąd podczas otwierania pliku do odczytu");
            close(client_socket);
            continue;
        }

        char buffer[BUFFER_SIZE];
        ssize_t read_bytes, sent_bytes, total_bytes = 0;
        while ((read_bytes = read(file, buffer, BUFFER_SIZE)) > 0) {
            sent_bytes = send(client_socket, buffer, read_bytes, 0);
            if (sent_bytes == -1) {
                perror("Błąd podczas wysyłania danych pliku");
                close(file);
                close(client_socket);
                continue;
            }
            total_bytes += sent_bytes;
        }

        printf("Wysłano plik '%s' (%ld bajtów) do klienta %s:%d\n", filename, total_bytes, client_ip, client_port);

        /* Zamykanie pliku i gniazda */
        close(file);
        close(client_socket);
    }

    /* Zamykanie gniazda nasłuchującego */
    close(server_socket);

    return 0;
}
