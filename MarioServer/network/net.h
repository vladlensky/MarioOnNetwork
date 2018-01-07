#ifndef NETWORK_NET_H
#define NETWORK_NET_H
#include <stdint.h>
#include "../game/Mario.h"
#include "../network/packet.h"
#define MAX_CONNECTIONS 2
#define DEFAULT_PORT 26000

typedef enum {RUNNING, SHUTDOWN} net_server_state;
typedef struct net_client_descr_t {
    int socket;
    struct Queue *send;
    Mario *mario;
} net_client_descr_t;

int net_port_bind(uint16_t port);
int net_server_start(uint16_t port);
void net_server_receive(void *);
void net_server_sends(Packet* args,int socket) ;
void net_game_thread(net_client_descr_t *);

#endif // NETWORK_NET_H
