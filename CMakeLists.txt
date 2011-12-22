cmake_minimum_required(VERSION 2.6)
project(game)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

set(
	SOURCES
	src/Application.cpp
	src/Color.cpp
	src/Convex.cpp
	src/Font.cpp
	src/GameEngine.cpp
	src/GameState.cpp
		src/states/LevelState.cpp
	src/Math.cpp
	src/Object.cpp
	src/Rect.cpp
	src/Resource.cpp
	src/ResourceManager.cpp
	src/Texture.cpp
	src/Vector2.cpp

	src/Box2DCompat.cpp

	src/Subsystem.cpp
	src/SubsystemThread.cpp
		src/subsystems/PhysicsSubsystem.cpp
		src/subsystems/GraphicsSubsystem.cpp
		src/subsystems/InputSubsystem.cpp
		#src/subsystems/LuaSubsystem.cpp
		#src/subsystems/LogicSubsystem.cpp

	src/Component.cpp
		src/components/Body.cpp
		src/components/Renderable.cpp
		#src/components/Shape.cpp
		#src/components/Tracker.cpp
		#src/components/Updatable.cpp
		#src/components/Walkable.cpp

	#src/lua/LuaClass.cpp
	#src/lua/LuaComponent.cpp
	#src/lua/LuaObject.cpp
	#src/lua/LuaPositionable.cpp

	src/TestLevel.cpp
	src/main.cpp
)

file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

option(DEFINE_DEBUG "Build project with debugging code" OFF)
if(DEFINE_DEBUG)
	add_definitions(-DDEBUG_RENDERABLE)
endif(DEFINE_DEBUG)

find_package(Lua51 REQUIRED)
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Boost 1.36.0 REQUIRED)
find_package(Freetype REQUIRED)
find_package(Box2D REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x")

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${FREETYPE_INCLUDE_DIRS})
include_directories(${BOX2D_INLUCE_DIR})
include_directories(${LUA_INCLUDE_DIR})
include_directories("include")

link_libraries(
	${SDL_LIBRARY}
	${SDLIMAGE_LIBRARY}
	${OPENGL_LIBRARIES}
	${FREETYPE_LIBRARIES}
	${BOX2D_LIBRARY}
	${LUA_LIBRARY}
	SDLmain
)

add_executable(
	game
	WIN32
	${SOURCES}
)
