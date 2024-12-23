#include "Camera.hpp"

Camera::Camera()
{
	m_zoom = 1;
}

int Camera::getZoom() const
{
	return m_zoom;
}

void Camera::setZoom(int zoom)
{
	m_zoom = zoom;
}

void Camera::zoomIn()
{
	m_zoom++;
}

void Camera::zoomOut()
{
	if (m_zoom > 1) {
		m_zoom--;
	}
}

void Camera::moveUp()
{
    m_center += Vector2D(0, -1);
}

void Camera::moveDown()
{
    m_center += Vector2D(0, 1);
}

void Camera::moveLeft()
{
    m_center += Vector2D(-1, 0);
}

void Camera::moveRight()
{
    m_center += Vector2D(1, 0);
}
