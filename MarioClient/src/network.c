#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "include/network.h"
#include "include/Mario.h"
#include "include/Enemy.h"
#include "include/packer.h"

int net_client_connect(char* addr, uint16_t port) {
    struct sockaddr_in net_server;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (net_socket == -1) {
        return 0;
    }
    net_server.sin_addr.s_addr = inet_addr(addr);
    net_server.sin_family = AF_INET;
    net_server.sin_port = htons(port);
    if(connect(net_socket, (struct sockaddr *)&net_server, sizeof(net_server)) < 0) {
        return 0;
    }
    return 1;
}

Mario *net_receive_packet() {
    char *server_reply = malloc(512);
    if (recv(net_socket, server_reply, sizeof(Packet), 0) == sizeof(Packet)) {
        char *buffer = malloc(512);
        memcpy(buffer, server_reply, sizeof(Packet));
        Packet *p = (Packet *) buffer;
        if (p->data_length != 0) {
            char *received_data = malloc(p->data_length + 1);
            recv(net_socket, received_data, p->data_length, 0);
            received_data[p->data_length] = 0;
            if(p->packet_id==1){
                int a4, a3, a1, a2, id;
                sscanf(received_data, "%i:%i:%i:%i:%i", &a1, &a2, &a3, &a4, &id);
                SDL_Rect pos;
                pos.x = a1-16;
                Mario *enemy = malloc(sizeof(Mario));
                Enemy_init(enemy,pos);
                enemy->currentAnimation = a2;
                enemy->currentFrame = a3;
                enemy->id = id;
                enemy->died = a4;
                free(received_data);
                free(server_reply);
                free(buffer);
                return enemy;
            }
            //accept mario
            if(p->packet_id==2){
                int a4, a1, a2, a3,id;
                sscanf(received_data, "%i:%i:%i:%i:%i", &a1, &a2, &a3, &a4,&id);
                Mario *hero = malloc(sizeof(Mario));
                Mario_init(hero);
                hero->position.x = a1;
                hero->position.y = a2;
                hero->currentAnimation = a3;
                hero->currentFrame = a4;
                hero->id = id;
                free(received_data);
                free(server_reply);
                free(buffer);
                return hero;
            }
            free(received_data);
            free(server_reply);
            free(buffer);
            return NULL;
        }
    }
    free(server_reply);
    return NULL;
}

char* packet_create(uint32_t packet_id, uint32_t data_length, char* data) {
    char* buffer = malloc(512);
    Packet *p = (Packet*) buffer;
    p->packet_id = packet_id;
    p->data_length = data_length;
    strcpy(p->data, data);
    return buffer;
}

void net_send_packet(char *packet, uint32_t length) {
    send(net_socket, packet, length, 0);
}

void net_send_mario(Mario *mario){
    char *player = malloc(512);
    packer_pack_player(player,mario);
    char *packet = packet_create(2,512, player);
    net_send_packet(packet, 512);
    free(packet);
    free(player);
}

void net_send_dead_enemy(int id){
    char *enemy = malloc(512);
    sprintf(enemy, "%i",id);
    char * packet = packet_create(1,512, enemy);
    net_send_packet(packet, 512);
    free(enemy);
    free(packet);
}