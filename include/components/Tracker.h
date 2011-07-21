#ifndef TRACKER_H
#define TRACKER_H

#include "Component.h"

class Tracker : public Component {
public:
	Tracker(Object *object);
	virtual ~Tracker();

	void setTracked(Object *object);

	void onUpdate();

	static const ComponentType componentType;

private:
	Object *m_tracked;
};

#endif /* end of include guard: TRACKER_H */
