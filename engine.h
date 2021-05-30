#ifndef ENGINE
#define ENGINE

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GLES3/gl3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "simulation.h"

// TODO: this class should be refactored into smaller classes
class engine {
private:
	// engine
	float last_time = 0, curr_time, delta_time = 0;
	int screenW, screenH;

	// logic
	static const int N = 40;
	float y_rot = 0, z_rot = 0;
	float rotSpeed = 0.001;
	// TODO: pick correct values
	simulation sim{N, 1, 0.1};

	// render
	GLfloat
		colorBuffer[N * N * N * 4], // r, g, b, a
		vertexBuffer[N * N * N * 3]; // x, y, z
	GLuint
		vertexBufferId,
		colorBufferId,
		matrixId;
	GLint
		posAttrib,
		colAttrib;
	glm::mat4
		projMat,
		modelMat,
		viewMat,
		mvpMat;

private:

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
		delta_time = curr_time - last_time;

		update();
		redraw();

		last_time = curr_time;
	}
};




#endif /*ENGINE*/