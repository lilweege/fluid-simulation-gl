#include "engine.h"

#include "shaders/helper.cpp"

// https://www.opengl-tutorial.org/beginners-tutorials/

void engine::init()
{

	// shaders
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


	// buffers
	for (int i = 0; i < N * N * N * 4; i += 4)
	{
		colorBuffer[i    ] = 0;
		colorBuffer[i + 1] = 0;
		colorBuffer[i + 2] = 0;
		colorBuffer[i + 3] = 1;
	}

	glGenBuffers(1, &colorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorBuffer), colorBuffer, GL_STATIC_DRAW);
	colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < N; ++k)
			{
				int idx = (N * N * i + N * j + k) * 3;
				// printf("%d\n", idx);
				vertexBuffer[idx    ] = i / float(N) * 2 - 1 + (1 / float(N));
				vertexBuffer[idx + 1] = j / float(N) * 2 - 1 + (1 / float(N));
				vertexBuffer[idx + 2] = k / float(N) * 2 - 1 + (1 / float(N));
			}

	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);
	posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);


	// matrix stuff
	projMat = glm::perspective(glm::radians(45.0f), float(screenW) / float(screenH), 0.1f, 100.0f);
	viewMat = glm::lookAt(
		glm::vec3(5,2,0), // camera pos world space
		glm::vec3(0,0,0), // look at pos
    	glm::vec3(0,1,0)  // head direction
    );
	matrixId = glGetUniformLocation(shaderProgram, "mvp");
	modelMat = glm::mat4(1.0f);
	mvpMat = projMat * viewMat * modelMat;
	glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvpMat[0][0]);


	// gl stuff
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS); // I think this is important
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

	// only do rotation if called for
	if (do_rot_y || do_rot_z)
	{
		if (do_rot_y) y_rot += delta_time * (l_pressed ? -rotSpeed : rotSpeed);
		if (do_rot_z) z_rot += delta_time * (d_pressed ? -rotSpeed : rotSpeed);
		
		modelMat = glm::rotate(glm::rotate(glm::mat4(1.0f),
			z_rot, glm::vec3(0, 0, 1.0)),
			y_rot, glm::vec3(0, 1.0, 0));
		mvpMat = projMat * viewMat * modelMat;
		glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvpMat[0][0]);
	}


	sim.tick(delta_time);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < N; ++k)
			{
				int idx = N * N * i + N * j + k;
				// colorBuffer[idx * 4 + 3] = sim.density[idx];
				colorBuffer[idx * 4 + 3] = sim.getDensity(i, j, k);
				// let the transparency of each 'black pixel' be the sampled particle density
			}
}

void engine::redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorBuffer), colorBuffer, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_POINTS, 0,  N * N * N);
}