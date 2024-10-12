#include "Vector2D.hpp"

Vector2D::Vector2D(float x, float y) : m_x(x), m_y(y) {}

float Vector2D::getX() const
{
	return m_x;
}

float Vector2D::getY() const
{
	return m_y;
}

void Vector2D::setX(float x)
{
	m_x = x;
}

void Vector2D::setY(float y)
{
	m_y = y;
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
	return Vector2D(m_x + other.m_x, m_y + other.m_y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
	return Vector2D(m_x - other.m_x, m_y - other.m_y);
}

Vector2D Vector2D::operator*(const float scalar) const
{
	return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D Vector2D::operator/(const float scalar) const
{
	return Vector2D(m_x / scalar, m_y / scalar);
}

bool Vector2D::equals(const Vector2D& other) const
{
	return m_x == other.m_x && m_y == other.m_y;
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
	m_x += other.m_x;
	m_y += other.m_y;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
	m_x -= other.m_x;
	m_y -= other.m_y;
	return *this;
}

Vector2D& Vector2D::operator*=(const float scalar)
{
	m_x *= scalar;
	m_y *= scalar;
	return *this;
}

Vector2D& Vector2D::operator/=(const float scalar)
{
	m_x /= scalar;
	m_y /= scalar;
	return *this;
}

float Vector2D::dot(const Vector2D& other) const
{
	return m_x * other.m_x + m_y * other.m_y;
}

float Vector2D::magnitude() const
{
	return sqrt(m_x * m_x + m_y * m_y);
}

float Vector2D::orientation() const
{
	return atan2(m_y, m_x);
}

Vector2D Vector2D::normalize() const
{
	float mag = magnitude();

	if (mag == 0)
	{
		return Vector2D(0, 0);
	}

	return Vector2D(m_x / mag, m_y / mag);
}

Vector2D Vector2D::rotate(float angle) const
{
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	return Vector2D(m_x * cosAngle - m_y * sinAngle, m_x * sinAngle + m_y * cosAngle);
}