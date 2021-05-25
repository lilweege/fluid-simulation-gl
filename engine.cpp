#include "engine.h"

#include <GL/gl.h>

void engine::process_input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
		process_event(&event);
}

void engine::process_event(SDL_Event* event)
{
	SDL_Keycode key = event->key.keysym.sym;
	if (event->key.type == SDL_KEYDOWN)
	{
		if (key == SDLK_LEFT)
			rot -= time_ellapsed * rotSpeed;
		else if (key == SDLK_RIGHT)
			rot += time_ellapsed * rotSpeed;
	}
}

void engine::init()
{
	// TODO: somehow draw a wireframe cube
	// glPolygonMode( GL_FRONT_AND_BACK, GL_LINES );
	
	sim = simulation();
}

void engine::update()
{
	sim.tick(time_ellapsed);
}

void engine::redraw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// uncomment if you like seizures
	// float r = rand() / float(RAND_MAX);
	// float g = rand() / float(RAND_MAX);
	// float b = rand() / float(RAND_MAX);
	// glClearColor(r, g, b, 1.0f);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

