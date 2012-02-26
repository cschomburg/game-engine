#ifndef BOX2DCOMPAT_H
#define BOX2DCOMPAT_H

#include <Box2D/Box2D.h>

#include "Vector2.h"

b2Vec2 toBox2D(const Vector2 &vec);
Vector2 fromBox2D(const b2Vec2 &vec);

#endif /* end of include guard: BOX2DCOMPAT_H */
