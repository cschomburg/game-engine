cmake_minimum_required (VERSION 2.6)
project (game)

set (
	SOURCES
	src/Application.cpp
	src/BaseEngine.cpp
	src/Camera.cpp
	src/Color.cpp
	src/Entity.cpp
	src/GameEngine.cpp
	src/GameObject.cpp
	src/GlInterface.cpp
	src/Level.cpp
	src/Player.cpp
	src/Rect.cpp
	src/Resource.cpp
	src/ResourceManager.cpp
	src/Texture.cpp
	src/Vector2.cpp
	src/YamlLoader.cpp
	src/main.cpp

	src/lua/LuaWrapper.cpp
	include/lua/luna.h
	src/lua/LuaObject.cpp
	src/lua/LuaEntity.cpp
	src/lua/LuaEntity.cpp
	src/lua/LuaPlayer.cpp
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
	yaml-cpp
	lua
)

add_executable (
	game
	WIN32
	${SOURCES}
)
