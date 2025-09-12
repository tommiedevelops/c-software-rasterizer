#ifndef GAME_TIME_H
#define GAME_TIME_H
#include <time.h>
#include <stdlib.h>

typedef struct GameTime {
	float delta_time; // unit: seconds
	float total_time; // unit: seconds
	clock_t last_time; // unit: cpu clock cycles
} GameTime;

float get_delta_time();
void time_init(struct GameTime* t);
void update_time(struct GameTime* t);
void print_time(struct GameTime* t);
void print_fps(struct GameTime* t);
#endif
