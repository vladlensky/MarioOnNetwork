#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "packet.h"
#include "net.h"
#include "packer.h"
#include "../game/Enemy.h"
#include "../game/Mario.h"
#include "../game/JeuState.h"

net_server_state net_server_status;
net_client_descr_t clients[MAX_CONNECTIONS];
struct Mario **enemies;
int net_port_bind(uint16_t port) {
    struct sockaddr_in net_server;
    int net_socket;
    const int yes = 1;

    net_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (net_socket == -1) {
        fprintf(stderr, "net_port_bind(): socket creating fail!\n");
        return 0;
    }
    net_server.sin_family = AF_INET;
    net_server.sin_addr.s_addr = INADDR_ANY;
    net_server.sin_port = htons(port);
    setsockopt(net_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if (bind(net_socket, (struct sockaddr*)&net_server, sizeof(net_server)) < 0) {
        return 0;
    }
    return net_socket;
}

int net_server_start(uint16_t port) {
    const FILE const *fp;
    fp = fopen("../game/level", "r");
    size_t i = 0;
    while (i != H && fgets(FirstLevelMap[i], W+2,fp)){i++;}
    fclose(fp);
    SDL_Rect position;
    struct Mario** enemy =  malloc(sizeof(struct Mario**)* Enemies_count);
    for(size_t i = 0;i < Enemies_count;i++){
        enemy[i] = malloc((sizeof(struct Mario)));
        enemy[i]->id = i;
        position.x = 750 + i*300;
        Enemy_init(enemy[i],position);
    }
    enemies = enemy;
    int net_socket = net_port_bind(port);
    struct sockaddr_in net_client;
    int clients_count = 0;
    int net_new_socket = 0, net_c = 0;

    if (net_socket == 0) {
        fprintf(stderr, "[Server] Bind failed on port %i\n", port);
        return 0;
    }
    fprintf(stdout, "[Server] Binding success on port %i\n", port);

    listen(net_socket, MAX_CONNECTIONS);
    while((net_new_socket = accept(net_socket, (struct sockaddr*)&net_client, (socklen_t*)&net_c)) && clients_count < MAX_CONNECTIONS) {
        pthread_t net_receive_thread;

        clients[clients_count].socket = net_new_socket;
        clients[clients_count].mario = malloc(sizeof(struct Mario));
        Mario_init(clients[clients_count].mario);
        clients[clients_count].mario->id = clients_count;
        clients[clients_count].mario->position.x = 16 + clients_count*26;
        // sending client his id
        const char* handshake = packet_create_handshake(clients_count);
        send(net_new_socket, handshake, sizeof(Packet) + 1, 0);

        fprintf(stdout, "[Server] Client connected.\n");

        pthread_create(&net_receive_thread, NULL, (void *(*)(void *)) net_server_receive, (void*) &clients[clients_count]);
        if (clients_count == MAX_CONNECTIONS - 1) break;
        clients_count++;
    }

    pthread_t game_thread;
    pthread_create(&game_thread, NULL, (void *(*)(void *)) net_game_thread, clients);
    net_server_status = RUNNING;
    for(size_t i = 0;i < Enemies_count;i++)
        enemy[i]->lastUpdate = SDL_GetTicks();
    pthread_join(game_thread, NULL);
    return 0;
}

void net_server_sends(Packet* args,int socket) {
    if (args != NULL) {
        char *buffer;
        buffer = (char*) args;
        send(socket, buffer, sizeof(Packet) + args->data_length, 0);
    }
}

void net_game_thread(net_client_descr_t *clients) {
    for(size_t i = 0;i < MAX_CONNECTIONS;i++){
        char *player = malloc(512);
        packer_pack_player(player,clients[i].mario);
        Packet * packet = (Packet *) packet_create(2,512, player);
        net_server_sends(packet, clients[i].socket);
        free(packet);
        free(player);
    }
    while(net_server_status != SHUTDOWN) {
        for(size_t j = 0;j< Enemies_count;j++){
            Uint32 currentTime = SDL_GetTicks();
            Uint32 elapsedTime = currentTime - enemies[j]->lastUpdate;
            Enemy_update(enemies[j],elapsedTime);
        }
        for(size_t i = 0; i < MAX_CONNECTIONS; i++) {
            for(size_t j = 0;j<Enemies_count;j++) {
                char *enemy = malloc(512);
                packer_pack_enemy(enemy,enemies[j]);
                Packet * packet = (Packet *) packet_create(1,512, enemy);
                net_server_sends(packet, clients[i].socket);
                free(packet);
                free(enemy);
            }
            for(size_t j = 0;j< MAX_CONNECTIONS;j++)
                if(i!=j) {
                    char *player = malloc(512);
                    packer_pack_player(player,clients[j].mario);
                    Packet * packet = (Packet *) packet_create(2,512, player);
                    net_server_sends(packet, clients[i].socket);
                    free(packet);
                    free(player);
                }
        }
        usleep(30000);
    }
}

void net_server_receive(void* args) {
    net_client_descr_t *arguments = (net_client_descr_t*) args;
    const int sock = arguments->socket;
    char* client_reply = malloc(512);
    while(recv(sock, client_reply, sizeof(Packet), 0) > 0) {
        char* buffer = malloc(512);
        memcpy(buffer, client_reply, sizeof(Packet));
        Packet* p = (Packet*) buffer;
        if (p->data_length != 0) {
            char* received_data = malloc(p->data_length + 1);
            recv(sock, received_data, p->data_length, 0);
            received_data[p->data_length] = 0;
            //if enemy killed -> send here
            if(p->packet_id==1){
                int id;
                sscanf(received_data, "%i",  &id);
                if(id>=0&&id<Enemies_count){
                    enemies[id]->died = 1;
                }
            }
            //accept mario
            if(p->packet_id==2){
                int a4, a1, a2, a3,id;
                sscanf(received_data, "%i:%i:%i:%i:%i", &a1, &a2, &a3, &a4,&id);
                clients[id].mario->position.x = a1;
                clients[id].mario->position.y = a2;
                clients[id].mario->currentAnimation = a3;
                clients[id].mario->currentFrame = a4;
            }
            free(buffer);
            free(received_data);
        }
    }
    free(client_reply);
    close(arguments->socket);
}
