void Enemy_init(struct Mario * mario, SDL_Rect offset);
void Enemy_draw(struct Mario * mario, SDL_Surface * surface, SDL_Rect offset);
void Enemy_update(struct Mario * enemy, Uint32 timeElapsed);