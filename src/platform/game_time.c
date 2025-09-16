#include <stdio.h>
#include "game_time.h"

void gameTime_init(GameTime* t){
	if(t == NULL){
		perror("src/game_time.c/time_init: GameTime** is NULL");
		exit(EXIT_FAILURE);
	}
	t->delta_time = 0;
	t->total_time = 0;
	t->last_time = clock();
}

void gameTime_update(GameTime* t){
	if(t == NULL){
		perror("src/game_time.c/update_time: GameTime** is NULL");
		exit(EXIT_FAILURE);
	}	

	clock_t curr_time = clock();
	t->delta_time = (float)(curr_time - t->last_time) / CLOCKS_PER_SEC;
	t->last_time = curr_time;
	t->total_time += t->delta_time;
}

void gameTime_print_fps(GameTime* t){

	if(t == NULL){
		perror("src/game_time.c/update_time: GameTime** is NULL");
		exit(EXIT_FAILURE);
	}	
	int fps = 1 / t->delta_time;
	printf("fps = {%d}\n", fps);
}

double gameTime_deltaTime(GameTime* t){
	return t->delta_time;
}
