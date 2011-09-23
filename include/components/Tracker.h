#ifndef TRACKER_H
#define TRACKER_H

#include "components/Updatable.h"

class Tracker : public Updatable {
public:
	Tracker(Object *object);
	virtual ~Tracker();

	void setTracked(Object *object);

	void update();

	static const ComponentType componentType;

private:
	Object *m_tracked;
};

#endif /* end of include guard: TRACKER_H */
