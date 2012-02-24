#ifndef SOLIDRENDERABLE_H
#define SOLIDRENDERABLE_H

#include "components/Renderable.h"

class SolidRenderable : public Renderable {
public:
	typedef std::shared_ptr<SolidRenderable> Ptr;

	SolidRenderable();
	virtual ~SolidRenderable();

	void render();
};

#endif /* end of include guard: SOLIDRENDERABLE_H */
