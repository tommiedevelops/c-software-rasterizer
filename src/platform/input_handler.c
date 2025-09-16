#include "input_handler.h"
#include <stdbool.h>
#include <SDL2/SDL.h>
bool func(SDL_Event event){

	while (SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT: return false;
			case SDL_MOUSEMOTION:
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) 
					return false;
				break;
		}
	}	

}

bool other_func(){
	const Uint8* kb = SDL_GetKeyboardState(NULL);

	if(kb[SDL_SCANCODE_W]) {
	}

	if(kb[SDL_SCANCODE_A]) {
	}

	if(kb[SDL_SCANCODE_S]) {
	}

	if(kb[SDL_SCANCODE_D]) {
	}

}

InputHandler* inputHandler_create() {
	// TODO
	return NULL;
}
void input_beginFrame(InputHandler* input) {
	// TODO
}
bool input_processEvent(SDL_Event* event) {
	// TODO
	return false;
}
void input_endFrame(InputHandler* input) {
	// TODO
}

