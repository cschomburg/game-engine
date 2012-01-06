cmake_minimum_required(VERSION 2.6)
project(game)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

option(DEFINE_DEBUG "Build project with debugging code" OFF)
option(LUAJIT "Use LuaJIT instead of normal Lua" ON)
option(MINGW32 "Crosscompile MinGW32 build" OFF)

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_THREAD_USE_LIB")
endif(WIN32)

if(BUILD_STATIC)
	if(WIN32)
		set(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a .dll.a ${CMAKE_FIND_LIBRARY_SUFFIXES})
	else(WIN32)
		set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
	endif(WIN32)
	set(LuaJIT_USE_STATIC_LIBS ON)
	set(Boost_USE_STATIC_LIBS ON)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif(BUILD_STATIC)

set(
	SOURCES
	src/GameEngine.cpp

	src/Color.cpp
	src/Convex.cpp
	src/Font.cpp
	src/GameState.cpp
		src/states/LevelState.cpp
		src/states/WorldManipulateState.cpp
	src/Math.cpp
	src/Rect.cpp
	src/Resource.cpp
	src/ResourceManager.cpp
	src/Texture.cpp
	src/Vector2.cpp

	src/Box2DCompat.cpp

	src/Subsystem.cpp
		src/subsystems/PhysicsSubsystem.cpp
		src/subsystems/GraphicsSubsystem.cpp
		src/subsystems/InputSubsystem.cpp
		src/subsystems/LuaSubsystem.cpp
		#src/subsystems/LogicSubsystem.cpp

	src/Component.cpp
		src/components/Body.cpp
		src/components/Renderable.cpp
		src/components/StaticPos.cpp

		include/interfaces/IPositionable.h

	src/LuaCall.cpp
	src/LuaClass.cpp
		src/lua/LuaBody.cpp
		src/lua/LuaComponent.cpp
		src/lua/LuaGameEngine.cpp
		src/lua/LuaGraphics.cpp
		src/lua/LuaRenderable.cpp
		src/lua/LuaStaticPos.cpp

	src/main.cpp
)

file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(DEFINE_DEBUG)
	add_definitions(-DDEBUG_RENDERABLE)
endif(DEFINE_DEBUG)

if(LUAJIT)
	find_package(LuaJIT REQUIRED)
else(LUAJIT)
	find_package(Lua51 REQUIRED)
endif(LUAJIT)

if(BUILD_STATIC)
	find_package(ZLIB REQUIRED)
	find_package(BZip2 REQUIRED)
endif(BUILD_STATIC)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Boost 1.36.0 REQUIRED)
find_package(Freetype REQUIRED)
find_package(Box2D REQUIRED)

#set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_CXX_COMPILER ccache)
#set(CMAKE_CXX_COMPILER_ARG1="g++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x -Wall")

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${FREETYPE_INCLUDE_DIRS})
include_directories(${BOX2D_INLUCE_DIR})
if(LUAJIT)
	include_directories(${LUAJIT_INCLUDE_DIR})
else(LUAJIT)
	include_directories(${LUA_INCLUDE_DIR})
endif(LUAJIT)
include_directories("include")

link_libraries(
	${SDL_LIBRARY}
	${SDLIMAGE_LIBRARY}
	${OPENGL_LIBRARIES}
	${FREETYPE_LIBRARIES}
	${BOX2D_LIBRARY}
	SDLmain
)
if(LUAJIT)
	link_libraries(${LUAJIT_LIBRARIES})
else(LUAJIT)
	link_libraries(${LUA_LIBRARIES})
endif(LUAJIT)
if(WIN32)
	link_libraries(
		boost_thread_win32-mt-s
		pthread
	)
endif(WIN32)
if (BUILD_STATIC)
	link_libraries(
		${ZLIB_LIBRARIES}
		${BZIP2_LIBRARIES}
	)
endif(BUILD_STATIC)

add_executable(
	game
	WIN32
	${SOURCES}
)
