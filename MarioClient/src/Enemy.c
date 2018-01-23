#include <math.h>
#include "include/Mario.h"
#include "include/JeuState.h"
#include "SDL/SDL_image.h"
void Enemy_init(struct Mario * enemies, SDL_Rect offset)
{
    SDL_Rect * frames = NULL;
    enemies->currentAnimation = WALKING;
    enemies->direction = RIGHT;
    enemies->is_moving = 1;
    enemies->speed = 0.10;
    enemies->deathTime = 0;
    enemies->currentFrame = 0;
    enemies->position.x = 16+offset.x;
    enemies->position.y = 192;
    enemies->position.w = 16;
    enemies->position.h = 16;
    enemies->died = 0;
    frames = malloc(sizeof(*frames) * 2);
    frames[0].x = 0;
    frames[0].y = 0;
    frames[0].w = 16;
    frames[0].h = 16;
    frames[1].x = 19;
    frames[1].y = 0;
    frames[1].w = 16;
    frames[1].h = 16;
    enemies->animation[WALKING].frames = frames;
    enemies->animation[WALKING].countFrame = 2;
    enemies->animation[WALKING].delay = 320;
    frames = malloc(sizeof(*frames) * 1);
    frames[0].x = 57;
    frames[0].y = 0;
    frames[0].w = 17;
    frames[0].h = 17;
    frames[1].x = 57;
    frames[1].y = 0;
    frames[1].w = 17;
    frames[1].h = 17;
    enemies->animation[DIED_ENEMY].frames = frames;
    enemies->animation[DIED_ENEMY].countFrame = 2;
    enemies->animation[DIED_ENEMY].delay = 280;
}

void Enemy_update(struct Mario * mario, Uint32 timeElapsed){
    if(mario->died) {
        mario->currentAnimation = DIED_ENEMY;

        mario->deathTime+=timeElapsed;
        if(mario->deathTime>1600) {
            mario->currentFrame = 3;
        }
        return;
    }
    if(mario->direction == RIGHT)
    {
        mario->position.x += (mario->speed * timeElapsed);
        Collision(mario,2);
    }
    else{
        mario->position.x -= (mario->speed * timeElapsed);
        Collision(mario,2);
    }
    mario->lastUpdate += timeElapsed;
    if(mario->lastUpdate > mario->animation[mario->currentAnimation].delay)
    {
        mario->currentFrame = (mario->currentFrame + 1) % mario->animation[mario->currentAnimation].countFrame;
        mario->lastUpdate -= mario->animation[mario->currentAnimation].delay;
    }
}