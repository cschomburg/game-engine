#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

class Vector2 {
public:
	Vector2(float x = 0, float y = 0);

	Vector2 operator+(const Vector2 &vec) const;
	Vector2 operator-(const Vector2 &vec) const;
	Vector2 operator*(float t) const;
	Vector2 operator*(const Vector2& vec) const;
	Vector2 operator/(float t) const;

	void operator+=(const Vector2 &vec);
	void operator-=(const Vector2 &vec);
	void operator*=(float t);
	void operator/=(float t);

	void operator=(const Vector2 &vec);
	bool operator==(const Vector2 &vec);
	bool operator!=(const Vector2 &vec);

	float magnitude() const;
	Vector2 normalize() const;

public:
	float x;
	float y;
};

std::ostream& operator<<(std::ostream &o, const Vector2 &a);

#endif /* end of include guard: VECTOR2_H */
