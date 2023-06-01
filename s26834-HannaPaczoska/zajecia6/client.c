#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_FILENAME_LENGTH 256
#define BUFFER_SIZE 1024

int main() {
    /* Tworzenie gniazda */
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Błąd podczas tworzenia gniazda");
        exit(1);
    }

    /* Dane serwera */
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);  /* Port serwera */
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");  /* Adres IP serwera */

    /* Nawiązywanie połączenia */
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Błąd podczas nawiązywania połączenia z serwerem");
        exit(1);
    }

    /* Pobieranie nazwy pliku od użytkownika */
    char filename[MAX_FILENAME_LENGTH];
    printf("Podaj nazwę pliku do pobrania: ");
    fgets(filename, MAX_FILENAME_LENGTH, stdin);
    filename[strcspn(filename, "\n")] = '\0';  
    /* Usunięcie znaku nowej linii */

    /* Wysyłanie nazwy pliku do serwera */
    size_t filename_length = strlen(filename);
    if (send(client_socket, &filename_length, sizeof(size_t), 0) == -1) {
        perror("Błąd podczas wysyłania długości nazwy pliku");
        exit(1);
    }
    if (send(client_socket, filename, filename_length, 0) == -1) {
        perror("Błąd podczas wysyłania nazwy pliku");
        exit(1);
    }

    /* Odbieranie wielkości pliku */
    ssize_t file_size;
    if (recv(client_socket, &file_size, sizeof(ssize_t), 0) == -1) {
        perror("Błąd podczas odbierania wielkości pliku");
        exit(1);
    }

    /* Sprawdzanie, czy plik jest dostępny */
    if (file_size == -1) {
        printf("Plik '%s' nie istnieje na serwerze.\n", filename);
        close(client_socket);
        exit(0);
    }

    /* Odbieranie danych pliku */
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Błąd podczas otwierania pliku do zapisu");
        close(client_socket);
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    ssize_t received_bytes, total_bytes = 0;
    while (total_bytes < file_size) {
        received_bytes = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (received_bytes == -1) {
            perror("Błąd podczas odbierania danych pliku");
            fclose(file);
            close(client_socket);
            exit(1);
        }
        fwrite(buffer, 1, received_bytes, file);
        total_bytes += received_bytes;
    }

    printf("Pobieranie pliku '%s' zakończone.\n", filename);

    /* Zamykanie pliku i gniazda */
    fclose(file);
    close(client_socket);

    return 0;
}
