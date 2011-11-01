#ifndef TESTLEVEL_H
#define TESTLEVEL_H

#include <map>
#include <string>

class Object;
class GameEngine;

class TestLevel {
public:
	static std::map<std::string, Object *> create(GameEngine *engine);
};

#endif /* end of include guard: TESTLEVEL_H */
