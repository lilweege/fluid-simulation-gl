#include <functional>

#define GL_GLEXT_PROTOTYPES
#include <emscripten.h>
#include <GLES3/gl3.h>
#include <SDL.h>


float last_time = 0, curr_time;
float time_ellapsed = 0;




float rot = 0;
float rotSpeed = 1;

void process_event(SDL_Event* event) {
	SDL_Keycode key = event->key.keysym.sym;
	if (event->key.type == SDL_KEYDOWN) {
		if (key == SDLK_LEFT) {
			rot -= time_ellapsed * rotSpeed;
		}
		else if (key == SDLK_RIGHT) {
			rot += time_ellapsed * rotSpeed;
		}
	}
}

void process_input() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		process_event(&event);
	}
}



void redraw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


}


std::function<void()> loop;
void main_loop() { loop(); }

int main() {
	SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas");
	SDL_CreateWindowAndRenderer(500, 500, 0, nullptr, nullptr);

loop = [&] {
	curr_time = SDL_GetTicks();
	time_ellapsed = curr_time - last_time;

	process_input();

	redraw();

	last_time = curr_time;
};

	emscripten_set_main_loop(main_loop, 60, true);
	
	SDL_Quit();
	return EXIT_SUCCESS;
}
