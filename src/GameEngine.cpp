#include <SDL/SDL_opengl.h>

#include "Application.h"
#include "Convex.h"
#include "GameEngine.h"
#include "Object.h"
#include "Vector2.h"

#include "components/all.h"

#include "SubsystemThread.h"
#include "subsystems/PhysicsSubsystem.h"
#include "subsystems/GraphicsSubsystem.h"
#include "subsystems/LuaSubsystem.h"
#include "subsystems/InputSubsystem.h"
#include "subsystems/LogicSubsystem.h"

GameEngine::GameEngine() {
	m_level = 0;

	m_physics = new PhysicsSubsystem(this);
	m_graphics = new GraphicsSubsystem(this);
	m_lua = new LuaSubsystem(this);
	m_input = new InputSubsystem(this);
	m_logic = new LogicSubsystem(this);
}

GameEngine::~GameEngine() {
	delete m_physics;
	delete m_graphics;
	delete m_lua;
	delete m_input;
	delete m_logic;
}

bool GameEngine::init() {
	m_physics->init();
	m_graphics->init();
	m_lua->init();
	m_input->init();
	m_logic->init();

	if (!loadLevel("res/levels/level01.yaml"))
		return false;

	if (!m_lua->loadFile("res/lua/init.lua"))
		return false;

	SubsystemThread *thread = new SubsystemThread();
	thread->addSubsystem(m_physics);
	thread->start();
	m_threads.push_back(thread);

	thread = new SubsystemThread();
	thread->addSubsystem(m_lua);
	thread->addSubsystem(m_logic);
	thread->start();
	m_threads.push_back(thread);

	thread = new SubsystemThread();
	thread->addSubsystem(m_input);
	thread->start();
	m_threads.push_back(thread);

	return true;
}

void GameEngine::update() {
	m_graphics->update();
}

void GameEngine::destroy() {
	for (SubsystemThread *thread : m_threads) {
		thread->stop();
	}
	m_threads.clear();

	m_physics->destroy();
	m_graphics->destroy();
	m_lua->destroy();
	m_input->destroy();
	m_logic->destroy();

	for (Object *object : m_objects) {
		delete object;
	}
	m_objects.clear();
	m_level = 0;
}

bool GameEngine::loadLevel(std::string file) {

	// Level
	Object *m_level = new Object(this, "Level");
	m_level->createComponent<Positionable>()->setPos(Vector2(0, 0));
	m_level->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(20000, 15000)));
	m_level->createComponent<Renderable>()->setGradient(Color::fromInt(255, 89, 0),
														Color::fromInt(180, 20, 0));
	m_objects.push_back(m_level);

	// Sun
	Object *sun = new Object(this, "Sun");
	sun->createComponent<Positionable>()->setPos(Vector2(1000, 750));
	sun->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(512, 512)));
	sun->createComponent<Renderable>()->setTexture("res/images/sun.png");
	m_objects.push_back(sun);

	Convex conv;
	conv.points.push_back(Vector2(-100, 64));
	conv.points.push_back(Vector2(200, 32));
	conv.points.push_back(Vector2(50, -64));
	Object *test = new Object(this, "Conv");
	test->createComponent<Positionable>()->setPos(Vector2(722, 327));
	test->createComponent<Shape>()->setShape(conv);
	test->createComponent<Collidable>();
	test->createComponent<Renderable>()->setColor(Color(0, 0, 0));
	m_objects.push_back(test);

	// Conv2
	Convex conv2;
	conv2.points.push_back(Vector2(-40, -40));
	conv2.points.push_back(Vector2(0, 60));
	conv2.points.push_back(Vector2(100, -128));
	Object *test2 = new Object(this, "Conv2");
	test2->createComponent<Positionable>()->setPos(Vector2(722, 507));
	test2->createComponent<Shape>()->setShape(conv2);
	test2->createComponent<Collidable>();
	test2->createComponent<Renderable>()->setColor(Color(0, 0, 0));
	m_objects.push_back(test2);

	Convex triangle;
	triangle.points.push_back(Vector2(-100, 64));
	triangle.points.push_back(Vector2(100, 64));
	triangle.points.push_back(Vector2(0, -64));

	// Main Island
	Object *island = new Object(this, "Island");
	island->createComponent<Positionable>()->setPos(Vector2(512, 327));
	island->createComponent<Shape>()->setShape(triangle);
	island->createComponent<Renderable>()->setTexture("res/images/island.png");
	island->createComponent<Collidable>();
	m_objects.push_back(island);

	// Tree
	Object *tree = new Object(this, "Tree");
	tree->createComponent<Positionable>()->setPos(Vector2(512, 445));
	tree->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(100, 110)));
	tree->createComponent<Renderable>()->setTexture("res/images/tree.png");
	m_objects.push_back(tree);

	// Block
	Object *block = new Object(this, "Block");
	block->createComponent<Positionable>()->setPos(Vector2(300, 500));
	block->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(300, 300)));
	block->createComponent<Renderable>()->setGradient(Color::fromInt(0, 0, 0),
													  Color::fromInt(0, 0, 0));
	block->createComponent<Collidable>();
	m_objects.push_back(block);

	Object *player = new Object(this, "Player");
	player->createComponent<Positionable>()->setPos(Vector2(572, 456));
	player->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(32, 32)));
	player->createComponent<Renderable>()->setTexture("res/images/foo.png");
	player->createComponent<Movable>();
	player->createComponent<Walkable>()->setAcceleration(Vector2(1000, 1000));
	player->createComponent<Collidable>();
	m_objects.push_back(player);

	// Enemy
	Object *enemy = new Object(this, "Enemy");
	enemy->createComponent<Positionable>()->setPos(Vector2(422, 500));
	enemy->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(32, 32)));
	enemy->createComponent<Renderable>()->setTexture("res/images/foo.png");
	enemy->createComponent<Movable>();
	enemy->createComponent<Walkable>()->setAcceleration(Vector2(200, 0));
	enemy->createComponent<Tracker>()->setTracked(player);
	enemy->createComponent<Collidable>();
	m_objects.push_back(enemy);
	
	Object *camera = new Object(this, "Camera");
	camera->createComponent<Positionable>();
	camera->createComponent<Tracker>()->setTracked(player);
	m_objects.push_back(camera);

	m_graphics->setCamera(camera);
	m_input->setPlayer(player);
	m_lua->push("Object", player, "player");

	return true;
}

Object * GameEngine::level() const {
	return m_level;
}

PhysicsSubsystem * GameEngine::physics() const {
	return m_physics;
}

GraphicsSubsystem * GameEngine::graphics() const {
	return m_graphics;
}

LuaSubsystem * GameEngine::lua() const {
	return m_lua;
}

InputSubsystem * GameEngine::input() const {
	return m_input;
}

LogicSubsystem * GameEngine::logic() const {
	return m_logic;
}
