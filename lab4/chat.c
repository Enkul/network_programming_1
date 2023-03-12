#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080

int client_sockets[100];
int num_clients = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *handle_client(void *arg) {
    int client_socket = *(int*)arg;
    char buffer[1024] = {0};

    while (1) {
        int valread = read(client_socket, buffer, 1024);
        if (valread <= 0) {
            break;
        }

        pthread_mutex_lock(&lock);
        for (int i = 0; i < num_clients; i++) {
            if (client_sockets[i] != client_socket) {
                send(client_sockets[i], buffer, strlen(buffer), 0);
            }
        }
        pthread_mutex_unlock(&lock);

        memset(buffer, 0, 1024);
    }

    pthread_mutex_lock(&lock);
    for (int i = 0; i < num_clients; i++) {
        if (client_sockets[i] == client_socket) {
            client_sockets[i] = client_sockets[num_clients-1];
            num_clients--;
            break;
        }
    }
    pthread_mutex_unlock(&lock);

    close(client_socket);
    return NULL;
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("Connection");
        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, &new_socket);

        pthread_mutex_lock(&lock);
        client_sockets[num_clients] = new_socket;
        num_clients++;
        pthread_mutex_unlock(&lock);
    }

    return 0;
}
