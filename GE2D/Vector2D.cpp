#include "Vector2D.hpp"


Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
	return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
	return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(const float scalar) const
{
	return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/(const float scalar) const
{
	return Vector2D(x / scalar, y / scalar);
}

bool Vector2D::equals(const Vector2D& other) const
{
	return x == other.x && y == other.y;
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2D& Vector2D::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2D& Vector2D::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

float Vector2D::dot(const Vector2D& other) const
{
	return x * other.x + y * other.y;
}

float Vector2D::cross(const Vector2D& other) const {
	return x * other.y - y * other.x;
}

Vector2D Vector2D::projectOnto(const Vector2D& other) const
{
	float dotProduct = dot(other);
	float magnitudeSquared = other.dot(other);

	if (magnitudeSquared == 0) {
		return Vector2D(0, 0);
	}

	return Vector2D(dotProduct / magnitudeSquared * other.x, dotProduct / magnitudeSquared * other.y);
}

float Vector2D::magnitude() const
{
	return sqrt(x * x + y * y);
}

float Vector2D::orientation() const
{
	return atan2(y, x);
}

Vector2D Vector2D::normalize() const
{
	float mag = magnitude();

	if (mag == 0)
	{
		return Vector2D(0, 0);
	}

	return Vector2D(x / mag, y / mag);
}

Vector2D Vector2D::rotate(float angle) const
{
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	return Vector2D(x * cosAngle - y * sinAngle, x * sinAngle + y * cosAngle);
}