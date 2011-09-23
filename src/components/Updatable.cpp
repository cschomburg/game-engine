#include "components/Updatable.h"

Updatable::Updatable(ComponentType componentType, Object *object)
	: Component(componentType, object) {}

Updatable::~Updatable() {}
