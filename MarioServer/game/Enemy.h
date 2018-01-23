
#include "Mario.h"
#define Enemies_count 3

void Enemy_init(struct Mario * mario, SDL_Rect offset);
void Enemy_update(struct Mario * enemy, Uint32 timeElapsed);