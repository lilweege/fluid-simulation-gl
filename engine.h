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
	float last_time = 0, curr_time;
	float time_ellapsed = 0;
	int screenW, screenH;

	// render
	// https://www.opengl-tutorial.org/beginners-tutorials/
	GLfloat g_vertex_buffer_data[(36 + 64)*3];
	GLfloat g_color_buffer_data[(36 + 64)*4];
	GLuint vertexbuffer;
	GLint posAttrib;
	GLuint colorbuffer;
	GLint colAttrib;
	GLuint MatrixID;
	glm::mat4 projMat;
	glm::mat4 modelMat;
	glm::mat4 viewMat;
	glm::mat4 mvpMat;

	// logic
	float y_rot = 0, z_rot = 0;
	float rotSpeed = 0.001;
	simulation sim;

private:
	// void process_input();
	// void process_event(SDL_Event* event);
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

		// process_input();
		update();
		redraw();

		last_time = curr_time;
	}
};




#endif /*ENGINE*/