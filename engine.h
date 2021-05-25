#ifndef ENGINE
#define ENGINE

#include <SDL2/SDL.h>
#include "simulation.h"


// TODO: this class should be refactored into smaller classes
class engine {
private:
	// engine
	float last_time = 0, curr_time;
	float time_ellapsed = 0;
	int screenW, screenH;

	// render


	// logic
	float rot = 0;
	float rotSpeed = 1;
	simulation sim;

private:
	void process_input();
	void process_event(SDL_Event* event);
	void init();
	void update();
	void redraw();

public:
	engine(int w, int h)
		: screenW(w), screenH(h)
	{
		SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas");
		SDL_CreateWindowAndRenderer(w, h, 0, nullptr, nullptr);
		init();
	}

	~engine()
	{
		SDL_Quit();
	}

	void loop()
	{
		curr_time = SDL_GetTicks();
		time_ellapsed = curr_time - last_time;

		process_input();
		update();
		redraw();

		last_time = curr_time;
	}
};




#endif /*ENGINE*/