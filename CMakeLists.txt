cmake_minimum_required(VERSION 2.6)
project(game)

set(
	SOURCES
	src/Application.cpp
	src/BaseEngine.cpp
	src/Color.cpp
	src/Component.cpp
	src/GameEngine.cpp
	src/Object.cpp
	src/Convex.cpp
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
	src/lua/LuaClass.cpp
	src/lua/LuaComponent.cpp
	src/lua/LuaObject.cpp

	src/main.cpp
)

file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

option(DEFINE_DEBUG "Build project with debugging code" OFF)
if(DEFINE_DEBUG)
	add_definitions(-DDEBUG_RENDERABLE)
endif(DEFINE_DEBUG)

Find_Package(SDL REQUIRED)
Find_Package(SDL_image REQUIRED)
Find_Package(OpenGL REQUIRED)
find_package(Boost 1.36.0 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

include_directories(${Boost_INCLUDE_DIRS})
include_directories( "include")

link_libraries(
	${SDL_LIBRARY}
	${SDLIMAGE_LIBRARY}
	${OPENGL_LIBRARIES}
	SDLmain
	lua
)

add_executable(
	game
	WIN32
	${SOURCES}
)
