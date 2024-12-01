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