#pragma once

#include <cmath>

class Vector2D {
private:
	float m_x;
	float m_y;

public:
	Vector2D(float x, float y);

	float getX() const;
	float getY() const;
	void setX(float x);
	void setY(float y);

	Vector2D operator+(const Vector2D& other) const;
	Vector2D operator-(const Vector2D& other) const;
	Vector2D operator*(const float scalar) const;
	Vector2D operator/(const float scalar) const;

	bool equals(const Vector2D& other) const;
	bool operator==(const Vector2D& other) const = delete;
	bool operator!=(const Vector2D& other) const = delete;

	Vector2D& operator+=(const Vector2D& other);
	Vector2D& operator-=(const Vector2D& other);
	Vector2D& operator*=(const float scalar);
	Vector2D& operator/=(const float scalar);

	float dot(const Vector2D& other) const;

	float magnitude() const;
	float orientation() const;

	Vector2D normalize() const;
	Vector2D rotate(float angle) const;
};