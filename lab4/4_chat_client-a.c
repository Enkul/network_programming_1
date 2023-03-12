#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    // Check for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <Server IP> <Server Port>\n", argv[0]);
        exit(1);
    }

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Set up the server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(1);
    }

    // Send a message to the server
    char message[1024] = "Hello, server!";
    if (send(sock, message, strlen(message), 0) == -1) {
        perror("Send failed");
        exit(1);
    }

    // Receive a message from the server
    while (1) {
        char buffer[1024];
        int num_bytes = recv(sock, buffer, sizeof(buffer), 0);
        if (num_bytes == -1) {
            perror("Receive failed");
            exit(1);
        }

        // Print the message received from the server
        buffer[num_bytes] = '\0';
        printf("Received message from server: %s\n", buffer);
        printf("Send message to server:");
        char message[1024];
        scanf("%s",&message);
        if (send(sock, message, strlen(message), 0) == -1) {
            perror("Send failed");
            exit(1);
        }
        // Close the socket
        
    }
    close(sock);
    return 0;
}
