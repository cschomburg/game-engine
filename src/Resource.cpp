#include "Resource.h"

Resource::Resource() {
	m_numUsed = 0;
}

Resource::~Resource() {
	if (m_numUsed > 0) {
		destroy();
	}
}

void Resource::init() {
	m_numUsed++;
	if (m_numUsed == 1) {
		load();
	}
}

void Resource::free() {
	m_numUsed--;
	if (m_numUsed == 0) {
		destroy();
	}
}

void Resource::load() {}
void Resource::destroy() {}
