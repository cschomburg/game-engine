#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

class GameEngine;

class Subsystem {
public:
	Subsystem(GameEngine *engine = 0);
	virtual ~Subsystem();

	GameEngine *engine() const;

	virtual bool init();
	virtual void update();
	virtual void destroy();

private:
	GameEngine *m_engine;
};


#endif /* end of include guard: SUBSYSTEM_H */
