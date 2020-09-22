#pragma once

void init_socket_library();
void* server_wait_for_client();
void* client_connect_to_server();

void socket_send(void* socket, const int buffer, bool another_turn);
char* translate_buff(const int buffer);

int socket_recv(void* socket);

