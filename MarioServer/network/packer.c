#include <stdio.h>
#include <stdlib.h>
#include "packer.h"
#include "../game/Mario.h"


int packer_pack_player(char* buffer, struct Mario* p) {
    return sprintf(buffer, "%i:%i:%i:%i:%i", p->position.x, p->position.y, p->currentAnimation, p->currentFrame,p->id);
}

int packer_pack_enemy(char* buffer, struct Mario* e) {
    return sprintf(buffer, "%i:%i:%i:%i:%i", e->position.x,e->currentAnimation, e->currentFrame,e->died,e->id);
}