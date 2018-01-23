#include <math.h>
#include <SDL/SDL_image.h>
#include "Mario.h"
#include "JeuState.h"

void Mario_init(struct Mario * mario)
{
    SDL_Rect * frames = NULL;
    mario->currentAnimation = IDLE_SMALL_RIGHT;
    mario->direction = RIGHT;
    mario->is_moving = 0;
    mario->speed = 0.20;
    mario->died = 0;
    mario->currentFrame = 0;
    mario->position.x = 16;
    mario->position.y = 136;
    mario->position.w = 16;
    mario->position.h = 16;
    mario->acceleration = 0;
    mario->type = 0;
    mario->won = 0;
    mario->onGround =1;
    /* IDLE_SMALL_RIGHT */
    frames = malloc(sizeof(*frames));
    frames[0].x = 211;
    frames[0].y = 0;
    frames[0].w = 13;
    frames[0].h = 16;
    mario->animation[IDLE_SMALL_RIGHT].frames = frames;
    mario->animation[IDLE_SMALL_RIGHT].countFrame = 1;
    mario->animation[IDLE_SMALL_RIGHT].delay = 0;
    /* IDLE_SMALL_LEFT */
    frames = malloc(sizeof(*frames));
    frames[0].x = 181;
    frames[0].y = 0;
    frames[0].w = 13;
    frames[0].h = 16;
    mario->animation[IDLE_SMALL_LEFT].frames = frames;
    mario->animation[IDLE_SMALL_LEFT].countFrame = 1;
    mario->animation[IDLE_SMALL_LEFT].delay = 0;
    /* JUMP_SMALL_LEFT */
    frames = malloc(sizeof(*frames));
    frames[0].x = 28;
    frames[0].y = 0;
    frames[0].w = 14;
    frames[0].h = 16;
    mario->animation[JUMP_SMALL_LEFT].frames = frames;
    mario->animation[JUMP_SMALL_LEFT].countFrame = 1;
    mario->animation[JUMP_SMALL_LEFT].delay = 0;
    /* JUMP_SMALL_RIGHT */
    frames = malloc(sizeof(*frames));
    frames[0].x = 363;
    frames[0].y = 0;
    frames[0].w = 14;
    frames[0].h = 16;
    mario->animation[JUMP_SMALL_RIGHT].frames = frames;
    mario->animation[JUMP_SMALL_RIGHT].countFrame = 1;
    mario->animation[JUMP_SMALL_RIGHT].delay = 0;


    /* WALKING_SMALL_RIGHT */
    frames = malloc(sizeof(*frames) * 3);
    frames[0].x = 241;
    frames[0].y = 0;
    frames[0].w = 14;
    frames[0].h = 15;
    frames[1].x = 272;
    frames[1].y = 0;
    frames[1].w = 12;
    frames[1].h = 16;
    frames[2].x = 300;
    frames[2].y = 0;
    frames[2].w = 16;
    frames[2].h = 16;
    mario->animation[WALKING_SMALL_RIGHT].frames = frames;
    mario->animation[WALKING_SMALL_RIGHT].countFrame = 3;
    mario->animation[WALKING_SMALL_RIGHT].delay = 200;
    /* WALKING_SMALL_LEFT */
    frames = malloc(sizeof(*frames) * 3);
    frames[0].x = 151;
    frames[0].y = 0;
    frames[0].w = 14;
    frames[0].h = 15;
    frames[1].x = 122;
    frames[1].y = 0;
    frames[1].w = 12;
    frames[1].h = 16;
    frames[2].x = 90;
    frames[2].y = 0;
    frames[2].w = 16;
    frames[2].h = 16;
    mario->animation[WALKING_SMALL_LEFT].frames = frames;
    mario->animation[WALKING_SMALL_LEFT].countFrame = 3;
    mario->animation[WALKING_SMALL_LEFT].delay = 200;
    /*DIED*/
    frames = malloc(sizeof(*frames) );
    frames[0].x = 0;
    frames[0].y = 16;
    frames[0].w = 16;
    frames[0].h = 16;
    mario->animation[DIED_ENEMY].frames = frames;
    mario->animation[DIED_ENEMY].countFrame = 1;
    mario->animation[DIED_ENEMY].delay = 200;
}

void Mario_move_left(struct Mario * mario, int move)
{
    if(mario->died){
        return;
    }
    if(mario->is_moving == 1)
    {
        if(move == 0 && mario->direction == LEFT)
        {
            mario->is_moving = 0;
            mario->currentAnimation = IDLE_SMALL_LEFT;
            mario->currentFrame = 0;
        }
    }
    else
    {
        if(move == 1)
        {
            mario->is_moving = 1;
            mario->direction = LEFT;
            mario->currentAnimation = WALKING_SMALL_LEFT;
        }
    }
}

//void Mario_down(Mario *mario,int down){
//    if(mario->type==0)
//        return;
//}
void Mario_jump(struct Mario *mario){
    if(mario->died){
        return;
    }
    if(mario->acceleration!=0)
        return;
    mario->onGround = 0;
    mario->acceleration=-0.48;
}
void Mario_move_right(struct Mario * mario, int move)
{
    if(mario->died){
        return;
    }
    if(mario->is_moving == 1)
    {
        if(move == 0 && mario->direction == RIGHT)
        {
            mario->is_moving = 0;
            mario->currentAnimation = IDLE_SMALL_RIGHT;
            mario->currentFrame = 0;
        }
    }
    else
    {
        if(move == 1)
        {
            mario->is_moving = 1;
            mario->direction = RIGHT;
            mario->currentAnimation = WALKING_SMALL_RIGHT;
        }
    }
}
void checkIsFalling(struct Mario *mario){
    int k = mario->position.x/16;
    int j = (mario->position.x+15)/16;
    int i = (mario->position.y+16)/16;
    if ((FirstLevelMap[i][j]=='P') ||(FirstLevelMap[i][j]=='c')|| (FirstLevelMap[i][j]=='k') || (FirstLevelMap[i][j]=='0') || (FirstLevelMap[i][j]=='r') || (FirstLevelMap[i][j]=='t')){
        return;
    }
    if ((FirstLevelMap[i][k]=='P') ||(FirstLevelMap[i][j]=='c')|| (FirstLevelMap[i][k]=='k') || (FirstLevelMap[i][k]=='0') || (FirstLevelMap[i][k]=='r') || (FirstLevelMap[i][k]=='t')){
        return;
    }
    mario->onGround = 0;
    mario->acceleration = 0.02;
}

void Mario_update(struct Mario * mario, Uint32 timeElapsed)
{
    if(mario->died){
        mario->currentAnimation = DIED_ENEMY;
        mario->currentFrame = 0;
        return;
    }
    if(mario->is_moving == 1)
    {

        if(mario->acceleration!=0){
            Collision(mario, 1);
            if(mario->direction == RIGHT)
                mario->currentAnimation = JUMP_SMALL_RIGHT;
            else
                mario->currentAnimation = JUMP_SMALL_LEFT;
        }
        mario->lastUpdate += timeElapsed;
        if(mario->lastUpdate > mario->animation[mario->currentAnimation].delay)
        {
            mario->currentFrame = (mario->currentFrame + 1) % mario->animation[mario->currentAnimation].countFrame;
            mario->lastUpdate -= mario->animation[mario->currentAnimation].delay;
        }

        if(mario->direction == RIGHT)
        {
            mario->position.x += (mario->speed * timeElapsed);
            Collision(mario,0);
        }
        if(mario->direction == LEFT)
        {
            mario->position.x -= (mario->speed * timeElapsed);
            if(mario->position.x < 0)
                mario->position.x = 0;
            Collision(mario,0);

        }
    }
    if(mario->acceleration!=0){
        Collision(mario, 1);
        if(mario->position.y>192) {
            mario->position.y = 192;
            mario->acceleration = 0;
            mario->onGround = 1;
            if(mario->direction == RIGHT){
                if(mario->is_moving)
                    mario->currentAnimation = WALKING_SMALL_RIGHT;
                else
                    mario->currentAnimation = IDLE_SMALL_RIGHT;
            }
            if(mario->direction == LEFT){
                if(mario->is_moving)
                    mario->currentAnimation = WALKING_SMALL_LEFT;
                else
                    mario->currentAnimation = IDLE_SMALL_LEFT;
            }

            return;
        }
        if(mario->onGround==0) {
            if(mario->position.y>22) {
                mario->position.y = mario->position.y + mario->acceleration * timeElapsed;
            }
            else {
                mario->position.y = 23;
                mario->acceleration = 0.02;
            }
            mario->acceleration = mario->acceleration + 0.02;
        }
    }
    if(mario->onGround) checkIsFalling(mario);
}

void Mario_draw(struct Mario * mario, SDL_Surface * surface, SDL_Rect offset)
{
    int cf = mario->currentFrame;
    SDL_Rect tmp_pos = mario->position;
    tmp_pos.x -= offset.x;
    tmp_pos.y -= offset.y;
    SDL_BlitSurface(mario->image, &(mario->animation[mario->currentAnimation].frames[cf]), surface, &tmp_pos);
}

void Mario_clean(struct Mario * mario)
{
    SDL_FreeSurface(mario->image);
    free(mario->animation[IDLE_SMALL_RIGHT].frames);
}
void Collision(struct Mario *mario,int coordinate){
    int i;
    int j;
    int enemy = 0;
    int temp = 1;
    if(coordinate)temp = 0;
    for (i = mario->position.y/16 ; i<(mario->position.y+16)/16; i++)
        for (j = mario->position.x/16; j<=(mario->position.x+16)/16; j++)
        {
            if ((FirstLevelMap[i][j]=='c')||(FirstLevelMap[i][j]=='P') || (FirstLevelMap[i][j]=='k') || (FirstLevelMap[i][j]=='0') || (FirstLevelMap[i][j]=='r') || (FirstLevelMap[i][j]=='t'))
            {
                if(coordinate==1) {
                    if (mario->acceleration > 0&&(mario->position.x>(j-1)*16)) {
                        if(fabs(mario->acceleration-0.020000)>1e-6) {
                            mario->position.y = i * 16 - 16;
                            mario->acceleration = 0;
                            temp = 1;
                        }
                    }
                    if (mario->acceleration < 0 &&(mario->position.y)/16<=i&&(mario->position.x>(j-1)*16)) {
                        mario->position.y = i * 16 + 16;
                        mario->acceleration = 0.02;
                    }
                    continue;
                }
                if (mario->is_moving==1 && mario->direction==RIGHT && (mario->position.x+16)/16<=j)
                { mario->position.x =  j*16 -  16;enemy=1; }
                if (mario->is_moving==1 && mario->direction==LEFT && (mario->position.x)/16>=j)
                { mario->position.x =  j*16 +  16;enemy=1;}
            }

            if (FirstLevelMap[i][j]=='c') {
                /* TileMap[i][j]=' ';*/
            }
        }

    if(coordinate==2 && enemy==1) {
        if(mario->direction == LEFT)
            mario->direction = RIGHT;
        else
            mario->direction = LEFT;
    }
    if(!temp)mario->onGround = 0;
    else {
        mario->onGround = 1;
        if(mario->direction == RIGHT){
            if(mario->is_moving)
                mario->currentAnimation = WALKING_SMALL_RIGHT;
            else
                mario->currentAnimation = IDLE_SMALL_RIGHT;
        }
        if(mario->direction == LEFT){
            if(mario->is_moving)
                mario->currentAnimation = WALKING_SMALL_LEFT;
            else
                mario->currentAnimation = IDLE_SMALL_LEFT;
        }

    }
}