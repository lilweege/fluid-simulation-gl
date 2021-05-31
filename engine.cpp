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
	// color buffers
	for (int i = 0; i < N * N * N * 4; i += 4)
	{
		// arbitrary colored smoke
		colorBuffer[i    ] = 0.52;
		colorBuffer[i + 1] = 0.45;
		colorBuffer[i + 2] = 0.66;
		colorBuffer[i + 3] = 1;
	}
	// cube (lines) black full alpha
	GLfloat cubeColorBuffer[16 * 4] = { 0 };
	for (int i = 0; i < 16 * 4; i += 4)
		cubeColorBuffer[i + 3] = 1;
	memcpy(colorBuffer + N * N * N * 4, cubeColorBuffer, sizeof(cubeColorBuffer));

	glGenBuffers(1, &colorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorBuffer), colorBuffer, GL_STATIC_DRAW);
	colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// vertex buffers
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

	// yeah repeating vertices is really bad
	// TODO: use an index buffer for this
	GLfloat cubeVertexBuffer[] = {
		-1.0, -1.0, -1.0, // 0 -
		-1.0, -1.0,  1.0, // 1
		-1.0,  1.0,  1.0, // 2
		-1.0,  1.0, -1.0, // 3
		-1.0, -1.0, -1.0, // 0 -
		 1.0, -1.0, -1.0, // 4 -
		 1.0, -1.0,  1.0, // 5
		 1.0,  1.0,  1.0, // 6
		 1.0,  1.0, -1.0, // 7
		 1.0, -1.0, -1.0, // 4 -
		 1.0,  1.0, -1.0, // 7
		-1.0,  1.0, -1.0, // 3
		-1.0,  1.0,  1.0, // 2
		 1.0,  1.0,  1.0, // 6
		 1.0, -1.0,  1.0, // 5
		-1.0, -1.0,  1.0, // 1
	};
	memcpy(vertexBuffer + N * N * N * 3, cubeVertexBuffer, sizeof(cubeVertexBuffer));

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


	// arbitrary setup that I found is at least somewhat interesting,
	// given the broken state of the simulation class
	if (state[SDL_SCANCODE_SPACE])
	{
		// emit fluid
		sim.addVelocity(Y, N/2, N/5, N/2, 100000 * delta_time);
		sim.addDensity(N/2, N/5, N/2, 0.00001f * N * N * N * delta_time);
	}
	// fade fluid
	for (int i = 1; i < N - 1; ++i)
		for (int j = 1; j < N - 1; ++j)
			for (int k = 1; k < N - 1; ++k)
				sim.addDensity(i, j, k, -0.000001f * delta_time);

	// do simulation stuff
	float step = delta_time / 10000000.0f;
	sim.tick(step);
	// new density values -> color buffer (transparency)
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < N; ++k)
				colorBuffer[(N * N * i + N * j + k) * 4 + 3] = sim.getDensity(i, j, k);
				// let the transparency of each 'gray pixel' be the sampled particle density
}

void engine::redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// glClearColor(0.0, 0.7, 1.0, 1.0f);
	glClearColor(1.0, 1.0, 1.0, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorBuffer), colorBuffer, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_POINTS, 0,  N * N * N); // points
	glDrawArrays(GL_LINE_STRIP, N * N * N, 16); // cube
}