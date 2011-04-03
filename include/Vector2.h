#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2 {

	Vector2(float x = 0, float y = 0);

	Vector2 operator+(const Vector2 &vec) const;
	Vector2 operator-(const Vector2 &vec) const;
	Vector2 operator*(float t) const;
	Vector2 operator/(float t) const;

	void operator+=(const Vector2 &vec);
	void operator-=(const Vector2 &vec);
	void operator*=(float t);
	void operator/=(float t);

	void operator=(const Vector2 &vec);
	void operator==(const Vector2 &vec);
	void operator!=(const Vector2 &vec);

	float x;
	float y;
}

#endif /* end of include guard: VECTOR2_H */
