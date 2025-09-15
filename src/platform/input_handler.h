#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct InputHandler InputHandler;
InputHandler* inputHandler_create();
void input_beginFrame(InputHandler* input);
bool input_processEvent(SDL_Event* event);
void input_endFrame(InputHandler* input);

#endif
