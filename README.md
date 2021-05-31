# fluid-simulation-gl
a 3d realtime fluid dynamics simulation using opengl, compiled to javascript for the web browser using emscripten  
inspired by and based upon [Jos Stam's Real-Time Fluid Dynamics for Games](http://graphics.cs.cmu.edu/nsp/course/15-464/Fall09/papers/StamFluidforGames.pdf) and [Mike Ash's Fluid Simulation for Dummies](https://mikeash.com/pyblog/fluid-simulation-for-dummies.html)  

## try it out
live demo at https://luigi.codes/projects/fluid-simulation-gl/  
![screenshot 1](https://raw.githubusercontent.com/lilweege/fluid-simulation-gl/master/screenshots/ss1.png)  
![screenshot 2](https://raw.githubusercontent.com/lilweege/fluid-simulation-gl/master/screenshots/ss2.png)  


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
- I don't claim to fully understand all that goes into the magical methods and linear solvers within the simulation (and I became espescially annoyed with the porting from 2D to 3D at times), but it's fun if anything to play with despite it not even being correct in places
