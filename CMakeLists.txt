cmake_minimum_required (VERSION 2.6)
project (game)

set (
	SOURCES
	src/Application.cpp
	src/BaseEngine.cpp
	src/Color.cpp
	src/Component.cpp
	src/GameEngine.cpp
	src/Object.cpp
	src/Polygon.cpp
	src/Rect.cpp
	src/Resource.cpp
	src/ResourceManager.cpp
	src/Texture.cpp
	src/Vector2.cpp

	src/components/Collidable.cpp
	src/components/Movable.cpp
	src/components/Positionable.cpp
	src/components/Renderable.cpp
	src/components/Shape.cpp
	src/components/Tracker.cpp
	src/components/Walkable.cpp

	src/lua/LuaWrapper.cpp

	src/main.cpp
)

Find_Package (SDL REQUIRED)
Find_Package (SDL_image REQUIRED)
Find_Package (OpenGL REQUIRED)

if (NOT SDL_FOUND)
	message (FATAL_ERROR "SDL not found!")
endif (NOT SDL_FOUND)

set(CMAKE_CXX_FLAGS "-g")

include_directories ( "include" )

link_libraries (
	${SDL_LIBRARY}
	${SDLIMAGE_LIBRARY}
	${OPENGL_LIBRARIES}
	SDLmain
	lua
)

add_executable (
	game
	WIN32
	${SOURCES}
)
