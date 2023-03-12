#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <math.h>
float evaluate_expression(char *exp);

float parse_number(char *exp, int *pos) {
    float num = 0;
    int decimal_point = 0;

    while (exp[*pos] >= '0' && exp[*pos] <= '9' || exp[*pos] == '.') {
        if (exp[*pos] == '.') {
            decimal_point = 1;
        } else {
            num = num * 10 + (exp[*pos] - '0');
            if (decimal_point) {
                decimal_point *= 10;
            }
        }
        (*pos)++;
    }

    if (decimal_point) {
        num /= decimal_point;
    }

    return num;
}

float parse_factor(char *exp, int *pos) {
    float result;
    int is_negative = 0;

    if (exp[*pos] == '-') {
        is_negative = 1;
        (*pos)++;
    }

    if (exp[*pos] == '(') {
        (*pos)++;
        result = evaluate_expression(exp);
        if (exp[*pos] != ')') {
            printf("Error: missing closing parenthesis\n");
            return NAN;
        }
        (*pos)++;
    } else {
        result = parse_number(exp, pos);
    }

    if (is_negative) {
        result = -result;
    }

    return result;
}

float parse_term(char *exp, int *pos) {
    float left, right;
    char op;

    left = parse_factor(exp, pos);

    while (exp[*pos] == '*' || exp[*pos] == '/') {
        op = exp[*pos];
        (*pos)++;
        right = parse_factor(exp, pos);
        if (op == '*') {
            left *= right;
        } else {
            left /= right;
        }
    }

    return left;
}

float parse_expression(char *exp, int *pos) {
    float left, right;
    char op;

    left = parse_term(exp, pos);

    while (exp[*pos] == '+' || exp[*pos] == '-') {
        op = exp[*pos];
        (*pos)++;
        right = parse_term(exp, pos);
        if (op == '+') {
            left += right;
        } else {
            left -= right;
        }
    }

    return left;
}

float evaluate_expression(char *exp) {
    int pos = 0;
    return parse_expression(exp, &pos);
}


#define MAX_CLIENTS 10
int main(int argc, char *argv[]) {
    // Check for correct number of arguments
    if (argc != 2) {
        printf("Usage: %s <Server Port>\n", argv[0]);
        exit(1);
    }

    // Create a socket
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Set up the server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    // Bind the socket to the server address
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_sock, MAX_CLIENTS) == -1) {
        perror("Listen failed");
        exit(1);
    }

    printf("Server started listening on port %s...\n", argv[1]);

    // Accept incoming connections
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_sock;
    char buffer[1024];
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_sock == -1) {
        perror("Accept failed");
        exit(1);
    }
    printf("Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
  
        // Receive a message from the client
    char exp[] = "1+1";
    
    int num_bytes = recv(client_sock, buffer, sizeof(buffer), 0);
    if (num_bytes == -1) {
        perror("Receive failed");
        exit(1);
    }
    // Print the message received from the client
    buffer[num_bytes] = '\0';

    printf("Received message from client: %s\n");
    printf("%s",buffer);
    float result = evaluate_expression(buffer);
    printf("%s = %.6f\n", buffer, result);
    sprintf(buffer, "%f", result);
    if (send(client_sock, buffer, strlen(buffer), 0) == -1) {
        perror("Send failed");
        exit(1);
    }
}