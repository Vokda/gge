# GGE
Grid Game Engine. A simple game engine for hexagon grid games. It is intended to be able handle squares
too someday.

The game engine is based on SDL2 and hex grid implemenation from https://www.redblobgames.com/.
The game engine can be controlled with, and thus games written in, Guile. 

It is still in its early stages of development so there are not many features.

# Why make GGE
I have a few ideas for some simple games based on hexagonal grids I'd like to make so that's why I'm making this game engine. 
It would of course be faster to use an existing game engine, but programming is fun and it's not like there is some deadline to be met. 

# file structure
The core components of the engine is just right in in `src/` *blows raspberry*.

`hex/` contains hex related classes. Both utilities and the hex class itself.

`script_handling/` contains necessary code for interfacing with the script engine. At the moment
only Guile is implemented. The GGE API can also be found there.

`build/` is where stuff is built and where you can find the GGE executable.

`docs/` contains "documentation".

`game/` contains games written for GGE.

`cmake/` contains cmake files for finding necessary libraries 

`build_tools/` contains some perl scripts that generate code. While not strictly necessary they lessen the amount of code needed to write.

# Requirements
* C++11 compiler or later
* CMake
* GNU Make
* SDL2 or later
* Guile 3.0 or later
## Optional
* Perl 5 (build tools)

# Build and Run
In the root of the repo...
1. Run `setup_build_env.sh`. Comment out build tools in the CMakefile if you want to skip that step.
2. Goto `build/`.
3. Run `make` (multithreaded compilation can be used for a faster compilation).
4. run `./gge games/test/` to test the engine.
5. Enjoy! Q or ESC can be used to quit. 
