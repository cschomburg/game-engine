#include <SDL/SDL_opengl.h>

#include "Application.h"
#include "components/all.h"
#include "GameEngine.h"
#include "Convex.h"
#include "Vector2.h"

GameEngine::GameEngine() {
	m_level = 0;
	m_player = 0;
	m_camera = 0;

	m_lua = new LuaWrapper();
}

GameEngine::~GameEngine() {}

bool GameEngine::loadLevel(const char * file) {

	// Level
	m_level = new Object();
	m_level->createComponent<Positionable>()->setPos(Vector2(1000, 750));
	m_level->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(2000, 1500)));
	m_level->createComponent<Renderable>()->setGradient(Color::fromInt(255, 89, 0),
														Color::fromInt(180, 20, 0));
	m_objects.push_back(m_level);

	// Sun
	Object *sun = new Object();
	sun->createComponent<Positionable>()->setPos(Vector2(1000, 750));
	sun->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(512, 512)));
	sun->createComponent<Renderable>()->setTexture("res/images/sun.png");
	m_objects.push_back(sun);

	Convex conv;
	conv.points.push_back(Vector2(-100, 64));
	conv.points.push_back(Vector2(200, 32));
	conv.points.push_back(Vector2(50, -64));
	Object *test = new Object();
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
	Object *test2 = new Object();
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
	Object *island = new Object();
	island->createComponent<Positionable>()->setPos(Vector2(512, 327));
	island->createComponent<Shape>()->setShape(triangle);
	island->createComponent<Renderable>()->setTexture("res/images/island.png");
	island->createComponent<Collidable>();
	m_objects.push_back(island);

	// Tree
	Object *tree = new Object();
	tree->createComponent<Positionable>()->setPos(Vector2(512, 445));
	tree->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(100, 110)));
	tree->createComponent<Renderable>()->setTexture("res/images/tree.png");
	m_objects.push_back(tree);

	// Block
	Object *block = new Object();
	block->createComponent<Positionable>()->setPos(Vector2(300, 500));
	block->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(300, 300)));
	block->createComponent<Renderable>()->setGradient(Color::fromInt(0, 0, 0),
													  Color::fromInt(0, 0, 0));
	block->createComponent<Collidable>();
	m_objects.push_back(block);

	// Enemy
	Object *enemy = new Object();
	enemy->createComponent<Positionable>()->setPos(Vector2(422, 400));
	enemy->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(32, 32)));
	enemy->createComponent<Renderable>()->setTexture("res/images/foo.png");
	enemy->createComponent<Movable>();
	enemy->createComponent<Walkable>()->setAcceleration(Vector2(200, 0));
	enemy->createComponent<Tracker>();
	enemy->createComponent<Collidable>();
	m_objects.push_back(enemy);

	return true;
}

bool GameEngine::onInit() {
	if (!loadLevel("res/levels/level01.yaml"))
		return false;

	m_player = new Object();

	Object *enemy = m_objects.back();
	enemy->component<Tracker>()->setTracked(m_player);

	m_player->createComponent<Positionable>()->setPos(Vector2(572, 456));
	m_player->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(32, 32)));
	m_player->createComponent<Renderable>()->setTexture("res/images/foo.png");
	m_player->createComponent<Movable>();
	m_player->createComponent<Walkable>()->setAcceleration(Vector2(1000, 1000));
	m_player->createComponent<Collidable>();
	m_objects.push_back(m_player);
	
	m_camera = new Object();
	m_camera->createComponent<Positionable>();
	m_camera->createComponent<Tracker>()->setTracked(m_player);
	m_objects.push_back(m_camera);

	if (!m_lua->init())
		return false;
	if (!m_lua->loadFile("res/lua/init.lua"))
		return false;

	return true;
}

void GameEngine::onUpdate() {
	Uint8 * keystate = SDL_GetKeyState(0);
	float x = keystate[SDLK_RIGHT] - keystate[SDLK_LEFT];
	float y = 0; //keystate[SDLK_UP] - keystate[SDLK_DOWN];

	m_player->component<Walkable>()->setDirection(Vector2(x, y));

	for (std::vector<Object *>::iterator i = m_objects.begin(); i != m_objects.end(); ++i) {
		(*i)->onUpdate();
	}

	m_lua->update();
}

void GameEngine::onRender() {
	BaseEngine::onRender();

	Vector2 pos = m_camera->component<Positionable>()->pos();
	glTranslatef(-pos.x, -pos.y, 0);

	for (std::vector<Object *>::iterator i = m_objects.begin(); i != m_objects.end(); ++i) {
		Renderable *renderable = (*i)->component<Renderable>();
		if (renderable)
			renderable->onRender();
	}
}

void GameEngine::onExit() {
	Application::instance()->quit();
}

void GameEngine::onCleanup() {
	BaseEngine::onCleanup();

	delete m_lua;
	m_lua = 0;

	for (std::vector<Object *>::iterator i = m_objects.begin(); i != m_objects.end(); ++i) {
		delete (*i);
	}
	m_objects.clear();
	m_level = 0;
	m_player = 0;
	m_camera = 0;
}

bool GameEngine::checkCollision(Object *object, Vector2 *collVectorTotal) {
	Collidable *collidable = object->component<Collidable>();
	Shape *shape = object->component<Shape>();
	if (!collidable || !shape)
		return false;

	bool collides = false;
	Vector2 collVector;
	for (std::vector<Object *>::iterator i = m_objects.begin(); i != m_objects.end(); ++i) {
		if (collidable->collides(*i, &collVector)) {
			collides = true;
			if (collVectorTotal) {
				(*collVectorTotal) += collVector;
			}
		}
	}

	return collides;
}

void GameEngine::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	if (sym == SDLK_UP) {
		Walkable *walkable = m_player->component<Walkable>();
		if (walkable)
			walkable->jump(Vector2(0, 800));
	}
}

void GameEngine::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
}
