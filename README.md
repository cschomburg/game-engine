game-engine
===========

My own experimental 2D game engine in C++, OpenGL and Lua. It serves as a learning experience and my entry into game development. The main goal is to try and experiment with different game design patterns and algorithms, not to develop a full game (although I certainly like to, eventually).

## Some facts

* uses C++ for the main engine subsystems, tries to be cross-platform
* uses Lua for game logic, user interface and level design
* uses OpenGL for graphics and Box2D for physics
* component-based approach for entities
* simple event-listener system with support for blocking coroutines
* on the fly world reloading when world file is modified
