# gge
Grid Game Engine. A simple game engine for hexagon grid games.

The game engine is based on SDL2 and hex grid implemenation from https://www.redblobgames.com/.
The game engine can be controlled with, and thus games written in, Chaiscript. 
For now only modules can be initiated and a grid created. 

I have a few ideas for some simple games based on hexagonal grids I'd like to make so that's why I'm making this game engine. 
It would of course be faster to use an existing game engine, but programming is fun and it's not like there is some deadline to be met. 

# src structure
The core components of the engine is just right in in `src/` *blows raspberry*.
`hex/` contains hex related classes. Both utilities and the hex class itself.
`in_game/` contains in game classes. Sligtly confusing seeing that hexes are part of the game but may reside in `hex/` instead. Sorry about that.
