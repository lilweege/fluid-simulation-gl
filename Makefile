# https://emscripten.org/docs/porting/multimedia_and_graphics/OpenGL-support.html
# GL_FLAGS = -s LEGACY_GL_EMULATION=1 -s GL_FFP_ONLY=1
# GL_FLAGS = -s FULL_ES2=1 -s FULL_ES3=1
GL_FLAGS = 
EM_FLAGS = --preload-file shaders/basic.vert --preload-file shaders/basic.frag


# RUN = python3 -m http.server
RUN_BROWSER_PATH = /mnt/c/Program\ Files/BraveSoftware/Brave-Browser/Application/brave.exe
RUN = emrun index.html --browser=$(RUN_BROWSER_PATH) 2> /dev/null


all: main.cpp engine.cpp engine.h simulation.cpp simulation.h
	em++ -std=c++17 -s USE_SDL=2 $(GL_FLAGS) $(EM_FLAGS) -O3 *.cpp -o index.js
	$(RUN)