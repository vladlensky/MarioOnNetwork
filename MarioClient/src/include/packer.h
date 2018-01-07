#ifndef NETWORK_PACKER_H
#define NETWORK_PACKER_H

#include "Mario.h"
int packer_pack_player(char* buffer, Mario* p);
int packer_pack_enemy(char* buffer, Mario* e);

#endif // NETWORK_PACKER_H
