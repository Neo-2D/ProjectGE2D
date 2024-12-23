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

void Camera::moveCenter(double deltaX, double deltaY) {
    /*Very sus logic there must be something better.Need to combine zoom factor with
	  mouse movement (that needs to be changed because otherwise it's too fast)*/
    float moveFactor = m_zoom > 5 ? 0.5 : 0.05;
	m_center += Vector2D(deltaX / (m_zoom / moveFactor), deltaY / (m_zoom / moveFactor));
}
