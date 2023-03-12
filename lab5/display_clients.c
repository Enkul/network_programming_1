#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#define MAX_CLIENTS 10

void *handle_client(void *arg);

int main(int argc, char *argv[]) {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    pthread_t threads[MAX_CLIENTS];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt error");
        exit(EXIT_FAILURE);
    }

    // Bind socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind error");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen error");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port 8080\n");

    // Accept client connections and create a thread for each
    for (int i = 0; i < MAX_CLIENTS; i++) {
        pid_t pid = fork();
        if (pid == 0) {
        // This is the child process
            printf("Child process created: PID = %d, PPID = %d\n", getpid(), getppid());
        }
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Accept error");
            exit(EXIT_FAILURE);
        }
        printf("Client %d connected\n", i+1);
        pthread_create(&threads[i], NULL, handle_client, (void *)&client_fd);
    }

    // Join threads
    for (int i = 0; i < MAX_CLIENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

void *handle_client(void *arg) {
    int client_fd = *(int *)arg;
    char buffer[1024] = {0};
    int valread;

    // Read from client
    valread = read(client_fd, buffer, 1024);
    printf("Received: %s\n", buffer);

    // Write to client
    char *message = "Hello from server";
    send(client_fd, message, strlen(message), 0);

    printf("Client disconnected\n");

    close(client_fd);
    pthread_exit(NULL);
}
