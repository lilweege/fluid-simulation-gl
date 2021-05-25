#include "engine.h"
#include <emscripten.h>

#include <functional>

std::function<void()> loop;
void em_loop() { loop(); }

int main()
{
	auto e = engine(500, 500);

	loop = [&] { e.loop(); };
	emscripten_set_main_loop(em_loop, -1, true);
	
	return EXIT_SUCCESS;
}
