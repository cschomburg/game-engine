#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include "Primitives.h"
#include "Prop.h"
#include "Vector2.h"

typedef std::vector<Prop *> propVector;

class Level {
public:
	Level();
	virtual ~Level();

	void setSize(int width, int height);
	void setBackground(Color colorA, Color colorB);
	void addProp(Prop * prop);

	void onInit();
	void onRender();

private:
	Vector2 m_size;

	Color m_bgColorA;
	Color m_bgColorB;

	propVector m_props;

	Prop * m_sun;
	Prop * m_island;
	Prop * m_tree;
};

#endif /* end of include guard: LEVEL_H */
