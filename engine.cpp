#include "engine.h"

#include "shaders/helper.cpp"

// void engine::process_input()
// {
// 	SDL_Event event;
// 	while (SDL_PollEvent(&event))
// 		process_event(&event);
// }


// void engine::process_event(SDL_Event* event)
// {
// 	SDL_Keycode key = event->key.keysym.sym;
// 	if (event->key.type == SDL_KEYDOWN)
// 	{
// 		if (key == SDLK_LEFT)
// 			;
// 		else if (key == SDLK_RIGHT)
// 			;
// 	}
// }


void engine::init()
{

	const GLchar* vertexSource = fromFile("shaders/basic.vert");
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);
	// checkShader(vertexShader);

	const GLchar* fragmentSource = fromFile("shaders/basic.frag");
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);
	// checkShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);


	GLfloat initial_color[] = {
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0, 0, 0, 1.0f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
		0.5, 0, 0.5, 0.25f,
	};
	memcpy(g_color_buffer_data, initial_color, sizeof(g_color_buffer_data));
	
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);


	GLfloat initial_verts[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
	};
	memcpy(g_vertex_buffer_data, initial_verts, sizeof(initial_verts));

	int n = 4;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			for (int k = 0; k < n; ++k)
			{
				int idx = (36 + n * n * i + n * j + k) * 3;
				printf("%d\n", idx);
				g_vertex_buffer_data[idx    ] = i / float(n) * 2 - 1 + (1/float(n));
				g_vertex_buffer_data[idx + 1] = j / float(n) * 2 - 1 + (1/float(n));
				g_vertex_buffer_data[idx + 2] = k / float(n) * 2 - 1 + (1/float(n));
			}
		}
	}

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);


	projMat = glm::perspective(glm::radians(45.0f), float(screenW) / float(screenH), 0.1f, 100.0f);

	viewMat = glm::lookAt(
		glm::vec3(5,2,0), // Camera is at (), in World Space
		glm::vec3(0,0,0), // looks at
    	glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
	
	modelMat = glm::rotate(glm::rotate(glm::mat4(1.0f),
		y_rot, glm::vec3(0, 1.0, 0)),
		z_rot, glm::vec3(0, 0, 1.0));
	mvpMat = projMat * viewMat * modelMat;

	MatrixID = glGetUniformLocation(shaderProgram, "mvp");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvpMat[0][0]);



	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_PROGRAM_POINT_SIZE);
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT_AND_BACK);

}

void engine::update()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	bool r_pressed = state[SDL_SCANCODE_RIGHT];
	bool l_pressed = state[SDL_SCANCODE_LEFT];
	bool u_pressed = state[SDL_SCANCODE_UP];
	bool d_pressed = state[SDL_SCANCODE_DOWN];
	bool do_rot_y = r_pressed != l_pressed;
	bool do_rot_z = u_pressed != d_pressed;
	if (do_rot_y)
	{
		y_rot += time_ellapsed * (l_pressed ? -rotSpeed : rotSpeed);
	}
	if (do_rot_z)
	{
		z_rot += time_ellapsed * (d_pressed ? -rotSpeed : rotSpeed);
	}
	
	if (do_rot_y || do_rot_z) {
		modelMat = glm::rotate(glm::rotate(glm::mat4(1.0f),
			z_rot, glm::vec3(0, 0, 1.0)),
			y_rot, glm::vec3(0, 1.0, 0));
		mvpMat = projMat * viewMat * modelMat;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvpMat[0][0]);
	}

	// sim.tick(time_ellapsed);
}

void engine::redraw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawArrays(GL_LINES, 0, 36);
	glDrawArrays(GL_POINTS, 36, 100);
}