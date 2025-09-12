#ifndef APP_H
#define APP_H

typedef struct App App;

App* app_create(void); // Renderer, SceneManager
void app_init(App* app); // Prepares the scene
void app_update(App* app, double dt); // Updates any time dependencies
void app_render(App* app); // Render the current frame
void app_shutdown(App* app); // Close window and clean up resources
void app_destroy(App* app); // Clean up app itself

#endif
