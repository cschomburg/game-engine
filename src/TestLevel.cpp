#include "Convex.h"
#include "components/all.h"
#include "GameEngine.h"
#include "Object.h"
#include "TestLevel.h"
#include "Vector2.h"

std::map<std::string, Object *> TestLevel::create(GameEngine *engine) {
	std::map<std::string, Object *> objects;

	// Level
	Object *level = new Object(engine, "Level");
	level->createComponent<Positionable>()->setPos(Vector2(0, 0));
	level->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(20000, 15000)));
	level->createComponent<Renderable>()->setGradient(Gradient(Color::fromInt(255, 89, 0),
														         Color::fromInt(180, 20, 0)));
	level->component<Renderable>()->setZIndex(-1.0f);
	objects["Level"] = level;

	// Sun
	Object *sun = new Object(engine, "Sun");
	sun->createComponent<Positionable>()->setPos(Vector2(1000, 750));
	sun->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(512, 512)));
	sun->createComponent<Renderable>()->setTexture("res/images/sun.png");
	sun->component<Renderable>()->setParallax(Vector2(0.8f, 0.8f));
	sun->component<Renderable>()->setBlendMode(BlendMode::Add);
	objects["Sun"] = sun;


	// Ground level
	Convex conv;
	conv.points.push_back(Vector2(0, 300));
	conv.points.push_back(Vector2(20000, 300));
	conv.points.push_back(Vector2(20000, 0));
	conv.points.push_back(Vector2(0, 0));
	Object *ground= new Object(engine, "Conv");
	ground->createComponent<Positionable>()->setPos(Vector2(-10000, -150));
	ground->createComponent<Shape>()->setShape(conv);
	ground->createComponent<Collidable>();
	ground->createComponent<Renderable>()->setColor(Color(0, 0, 0));
	objects["Ground"] = ground;

	// Ground Tree
	Object *gtree = new Object(engine, "GTree");
	gtree->createComponent<Positionable>()->setPos(Vector2(512, 228));
	gtree->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(150, 165)));
	gtree->createComponent<Renderable>()->setTexture("res/images/tree.png");
	gtree->component<Renderable>()->setColor(Color(0, 0, 0, 0.9));
	gtree->component<Renderable>()->setParallax(Vector2(0.05, 0));
	objects["GTree"] = gtree;

	// Grass
	Object *grass = new Object(engine, "Grass");
	grass->createComponent<Positionable>()->setPos(Vector2(512, 166));
	grass->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(77, 33)));
	grass->createComponent<Renderable>()->setTexture("res/images/ground/grass3.png");
	objects["Grass"] = grass;

	Object *grass2 = new Object(engine, "Grass2");
	grass2->createComponent<Positionable>()->setPos(Vector2(400, 175));
	grass2->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(101, 53)));
	grass2->createComponent<Renderable>()->setTexture("res/images/ground/grass1.png");
	objects["Grass"] = grass;

	// Test boxes
	Object *box1 = new Object(engine, "Box1");
	box1->createComponent<Positionable>()->setPos(Vector2(12, 166));
	box1->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(100, 100)));
	box1->createComponent<Renderable>()->setColor(Color(0, 0, 0, 0.3f));
	box1->component<Renderable>()->setParallax(Vector2(0.6f, 0.6f));
	objects["Box1"] = box1;

	Object *box2 = new Object(engine, "Box2");
	box2->createComponent<Positionable>()->setPos(Vector2(12, 166));
	box2->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(75, 75)));
	box2->createComponent<Renderable>()->setColor(Color(0, 0, 0, 0.6f));
	box2->component<Renderable>()->setParallax(Vector2(0.4f, 0.4f));
	objects["Box2"] = box2;

	Convex triangle;
	triangle.points.push_back(Vector2(-100, 64));
	triangle.points.push_back(Vector2(100, 64));
	triangle.points.push_back(Vector2(0, -64));

	// Main Island
	Object *island = new Object(engine, "Island");
	island->createComponent<Positionable>()->setPos(Vector2(512, 527));
	island->createComponent<Shape>()->setShape(triangle);
	island->createComponent<Renderable>()->setTexture("res/images/island.png");
	island->createComponent<Collidable>();
	objects["Island"] = island;

	// Tree
	Object *tree = new Object(engine, "Tree");
	tree->createComponent<Positionable>()->setPos(Vector2(512, 645));
	tree->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(100, 110)));
	tree->createComponent<Renderable>()->setTexture("res/images/tree.png");
	objects["Tree"] = tree;

	// Island background
	Object *island2 = new Object(engine, "Island2");
	island2->createComponent<Positionable>()->setPos(Vector2(812, 427));
	island2->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(150, 96)));
	island2->createComponent<Renderable>()->setTexture("res/images/island.png");
	island2->component<Renderable>()->setColor(Color::fromInt(0, 0, 0, 128));
	island2->component<Renderable>()->setParallax(Vector2(0.5f, 0.5f));
	objects["Island2"] = island2;

	// Tree background
	Object *tree2 = new Object(engine, "Tree2");
	tree2->createComponent<Positionable>()->setPos(Vector2(812, 602.5));
	tree2->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(75, 80)));
	tree2->createComponent<Renderable>()->setTexture("res/images/tree.png");
	tree2->component<Renderable>()->setColor(Color::fromInt(0, 0, 0, 128));
	tree2->component<Renderable>()->setParallax(Vector2(0.5f, 0.5f));
	objects["Tree2"] = tree2;

	Object *player = new Object(engine, "Player");
	player->createComponent<Positionable>()->setPos(Vector2(572, 656));
	player->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(32, 32)));
	player->createComponent<Renderable>()->setTexture("res/images/foo.png");
	player->createComponent<Movable>();
	player->createComponent<Walkable>()->setAcceleration(Vector2(1000, 1000));
	player->createComponent<Collidable>();
	objects["Player"] = player;

	// Enemy
	Object *enemy = new Object(engine, "Enemy");
	enemy->createComponent<Positionable>()->setPos(Vector2(422, 700));
	enemy->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(32, 32)));
	enemy->createComponent<Renderable>()->setTexture("res/images/foo.png");
	enemy->createComponent<Movable>();
	enemy->createComponent<Walkable>()->setAcceleration(Vector2(200, 0));
	enemy->createComponent<Tracker>()->setTracked(player);
	enemy->createComponent<Collidable>();
	objects["Enemy"] = enemy;
	
	Object *camera = new Object(engine, "Camera");
	camera->createComponent<Positionable>();
	camera->createComponent<Tracker>()->setTracked(player);
	objects["Camera"] = camera;

	return objects;
}
