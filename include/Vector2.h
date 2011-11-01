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

	float dot(const Vector2 &vec) const;

	void operator+=(const Vector2 &vec);
	void operator-=(const Vector2 &vec);
	void operator*=(float t);
	void operator/=(float t);

	void operator=(const Vector2 &vec);
	bool operator==(const Vector2 &vec);
	bool operator!=(const Vector2 &vec);

	float magnitude() const;
	bool isZero() const;

	void normalize();
	Vector2 normalized() const;
	Vector2 perpendicular() const;
	Vector2 projected(const Vector2 &vec) const;

public:
	float x;
	float y;
};

std::ostream& operator<<(std::ostream &o, const Vector2 &a);

#endif /* end of include guard: VECTOR2_H */
