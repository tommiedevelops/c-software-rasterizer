#ifndef GAME_TIME_H
#define GAME_TIME_H
#include <time.h>
#include <stdlib.h>

typedef struct GameTime {
	float delta_time; // unit: seconds
	float total_time; // unit: seconds
	clock_t last_time; // unit: cpu clock cycles
} GameTime;

double gameTime_deltaTime();
void gameTime_init(GameTime* t);
void gameTime_update(GameTime* t);
void gameTime_print_fps(GameTime* t);
#endif
