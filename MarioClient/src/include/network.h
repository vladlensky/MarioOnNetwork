#ifndef SI_CLIENT_NETWORK_H
#define SI_CLIENT_NETWORK_H

#include <stdint.h>
#include "Mario.h"
#define MAX_CONNECTIONS 2
#define DEFAULT_PORT 26000
#define DEFAULT_IP "127.0.0.1"
typedef struct Packet {
    uint32_t packet_id;
    uint32_t data_length;
    char data[0];
} Packet;

int net_socket;
int net_client_connect(char* addr, uint16_t port);
Mario* net_receive_packet();
char* packet_create(uint32_t packet_id, uint32_t data_length, char* data);
void net_send_packet(char* packet, uint32_t length);
void net_send_dead_enemy(int id);
void net_send_mario(Mario *mario);
#endif //SI_CLIENT_NETWORK_H
