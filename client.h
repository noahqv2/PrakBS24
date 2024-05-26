typedef struct {
    int client_socket;
    int bytes_read;
} client_args;

void *handle_client(void *arg);

void write_to_client(int client_socket, char* str);
