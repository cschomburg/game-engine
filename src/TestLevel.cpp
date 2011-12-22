#include <cstdlib>
#include <sstream>

#include "Convex.h"
#include "components/all.h"
#include "GameEngine.h"
#include "Object.h"
#include "TestLevel.h"
#include "Vector2.h"

std::map<std::string, Object *> TestLevel::create(GameEngine *engine) {
	std::map<std::string, Object *> objects;

	Object *object;
	Body *body;
	Renderable *renderable;

	// Level
	object = new Object(engine, "Level");
	object->setType(ObjectType::Background);
	body = object->createComponent<Body>();
	body->setPos(Vector2(0, 0));
	renderable = object->createComponent<Renderable>();
	renderable->setGradient(Gradient(Color::fromInt(255, 89, 0),
	                                 Color::fromInt(180, 20, 0)));
	renderable->setZIndex(-1.0f);
	renderable->setShape(Convex::fromSize(Vector2(200, 150)));
	objects["Level"] = object;

	// Sun
	object = new Object(engine, "Sun");
	object->setType(ObjectType::Background);
	body = object->createComponent<Body>();
	body->setPos(Vector2(10, 7.5));
	renderable = object->createComponent<Renderable>();
	renderable->setShape(Convex::fromSize(Vector2(5.12, 5.12)));
	renderable->setTexture("res/images/sun.png");
	renderable->setZIndex(-0.8f);
	renderable->setParallax(Vector2(0.8f, 0.8f));
	renderable->setBlendMode(BlendMode::Add);
	objects["Sun"] = object;

	// Ground
	b2PolygonShape *poly = new b2PolygonShape();
	poly->SetAsBox(100, 1.5);
	object = new Object(engine, "Ground");
	object->setType(ObjectType::Static);
	body = object->createComponent<Body>();
	body->setPos(Vector2(0, 0));
	body->setShape(poly);
	renderable = object->createComponent<Renderable>();
	renderable->setShape(Convex::fromSize(Vector2(200, 3)));
	renderable->setColor(Color(0, 0, 0));
	objects["Ground"] = object;

	// Ground Tree
	object = new Object(engine, "GTree");
	object->setType(ObjectType::Background);
	body = object->createComponent<Body>();
	body->setPos(Vector2(5.12, 2.28));
	renderable = object->createComponent<Renderable>();
	renderable->setShape(Convex::fromSize(Vector2(1.5, 1.65)));
	renderable->setTexture("res/images/tree.png");
	renderable->setColor(Color(0, 0, 0));
	renderable->setParallax(Vector2(0.05, 0));
	objects["GTree"] = object;

	// Grass
	for (int i = 0; i < 50; i++) {
		std::stringstream name;
		name << "Grass" << i;
		std::stringstream file;
		file << "res/images/ground/grass" << (rand() % 3)+1 << ".png";
		object = new Object(engine, name.str());
		object->setType(ObjectType::Background);
		body = object->createComponent<Body>();
		body->setPos(Vector2(-2.0f+i*0.4f, 1.66));
		renderable = object->createComponent<Renderable>();
		renderable->setShape(Convex::fromSize(Vector2(0.77, 0.33)));
		renderable->setTexture(file.str());
		objects[name.str()] = object;
	}

	/*
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
	*/

	// Player
	poly = new b2PolygonShape();
	poly->SetAsBox(0.16, 0.16);
	object = new Object(engine, "Player");
	body = object->createComponent<Body>();
	body->setPos(Vector2(5.72, 6.56));
	body->setShape(poly);
	renderable = object->createComponent<Renderable>();
	renderable->setShape(Convex::fromSize(Vector2(0.32, 0.32)));
	renderable->setTexture("res/images/foo.png");
	objects["Player"] = object;

	// Enemy
	poly = new b2PolygonShape();
	poly->SetAsBox(0.16, 0.16);
	object = new Object(engine, "Player");
	body = object->createComponent<Body>();
	body->setPos(Vector2(4.22, 7));
	body->setShape(poly);
	renderable = object->createComponent<Renderable>();
	renderable->setShape(Convex::fromSize(Vector2(0.32, 0.32)));
	renderable->setTexture("res/images/foo.png");
	objects["Player"] = object;

	/*
	// Test blocks
	Object *block = new Object(engine, "Testblock1");
	block->createComponent<Positionable>()->setPos(Vector2(800, 200));
	block->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(32, 32)));
	block->createComponent<Renderable>()->setTexture("res/images/foo.png");
	block->createComponent<Movable>();
	block->createComponent<Collidable>();
	objects["Testblock1"] = block;

	block = new Object(engine, "Testblock2");
	block->createComponent<Positionable>()->setPos(Vector2(835, 200));
	block->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(32, 32)));
	block->createComponent<Renderable>()->setTexture("res/images/foo.png");
	block->createComponent<Movable>();
	block->createComponent<Collidable>();
	objects["Testblock2"] = block;

	block = new Object(engine, "Testblock3");
	block->createComponent<Positionable>()->setPos(Vector2(900, 200));
	block->createComponent<Shape>()->setShape(Convex::fromSize(Vector2(64, 64)));
	block->createComponent<Renderable>()->setTexture("res/images/foo.png");
	block->createComponent<Movable>();
	block->createComponent<Collidable>()->setWeight(4);
	objects["Testblock3"] = block;
	*/
	
	return objects;
}
