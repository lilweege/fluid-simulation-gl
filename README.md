# fluid-simulation-gl
a 3d realtime fluid dynamics simulation using opengl, compiled to javascript for the web browser using emscripten  

## demo
see the live demo at https://luigi.codes/archive/fluid-simulation-gl/  

put screenshots here :)


## how do 🤷‍♂️
- download and install emscripten from http://emscripten.org/
- (optional) download external libraries (such as glm), add to build path
- write a program with some function to loop, call `emscripten_set_main_loop` with the function pointer
  - I use a std::function and capture list to avoid static declarations and associated pains
- compile with something similar to `em++ main.cpp -o index.html`
  - compile to index.js if you don't need the generated default html file
- run in browser with `emrun index.html` or `python -m http.server`
  - emrun spawns a new tab each time which I find useful

#### notes
- you don't need to use opengl if all you're after is 2d rendering; it's easiest to simply use SDL or nothing at all  
- I ran into problems with the canvas created by SDL stealing keyboard input, which I partially avoid with focus/blur on mouseover in conjunction with setting the `SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT` hint to id `"#canvas"`, I would be deligted to find a more elegant method  

