#ifndef MARIO_H
#define MARIO_H

#include <SDL/SDL.h>
#include <SDL/SDL_main.h>

#define BIG_OR_SMALL_ENUM(x) \
	DIRECTION_ENUM(x ## _BIG) \
	DIRECTION_ENUM(x ## _SMALL)

#define DIRECTION_ENUM(x) \
	x ## _LEFT, \
	x ## _RIGHT,

enum {
	WALKING,
	DIED_ENEMY,
	BIG_OR_SMALL_ENUM(IDLE)
	BIG_OR_SMALL_ENUM(WALKING)
	BIG_OR_SMALL_ENUM(JUMP)
	NUMBER_OF_ANIMATION
};

enum {
	RIGHT,
	LEFT
};

typedef struct {
	SDL_Rect * frames;
	int countFrame;
	Uint32 delay;
} Animation;

struct Mario {
	SDL_Surface * image;
	Animation animation[NUMBER_OF_ANIMATION];
	int currentAnimation;
	int currentFrame;
	Uint32 lastUpdate;
	SDL_Rect position;
	int direction;
	int is_moving;
	float speed;
	float acceleration;
	int type;
	int onGround;
	int lifesCount;
	int won;
	int died;
	int deathTime;
	int id;
};

void Mario_init(struct Mario * mario);
void Mario_move_left(struct Mario * mario, int move);
void Mario_move_right(struct Mario * mario, int move);
void Mario_jump(struct Mario * mario);
void Mario_down(struct Mario * mario,int down);
void Mario_update(struct Mario * mario, Uint32 timeElapsed);
void Mario_draw(struct Mario * mario, SDL_Surface * surface, SDL_Rect offset);
void Mario_clean(struct Mario * mario);
void Collision(struct Mario *mario,int coordinate);
#endif
