#pragma once
#include "Vector2D.hpp"

class Camera {
private:
	float m_zoom;
	Vector2D m_center = { 0, 0 };

public:
	Camera();
	
	float getZoom() const;
	void setZoom(float zoom);
	void zoomIn();
	void zoomOut();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    const Vector2D& getCenter() const { return m_center; }
    void setCenter(const Vector2D& center) { m_center = center; }
};