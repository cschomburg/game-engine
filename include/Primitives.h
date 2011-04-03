#ifndef PRIMITIVES_H
#define PRIMITIVES_H

struct Color {
	Color();
	Color(float r, float g, float b, float a = 1);
	static Color fromInt(int r, int g, int b, int a = 255);

	float r;
	float g;
	float b;
	float a;
};

#endif /* end of include guard: PRIMITIVES_H */
