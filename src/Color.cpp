#include "Color.h"

Color::Color() {
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}

Color::Color(float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color Color::fromInt(int r, int g, int b, int a) {
	return Color(float(r) / 255,
			     float(g) / 255,
				 float(b) / 255,
				 float(a) / 255);
}
