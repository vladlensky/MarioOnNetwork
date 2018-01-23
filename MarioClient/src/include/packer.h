#ifndef NETWORK_PACKER_H
#define NETWORK_PACKER_H

#include "Mario.h"
int packer_pack_player(char* buffer, struct Mario* p);
int packer_pack_enemy(char* buffer, struct Mario* e);

#endif // NETWORK_PACKER_H
