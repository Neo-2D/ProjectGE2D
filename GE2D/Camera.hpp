#pragma once
#include "Vector2D.hpp"

class Camera {
private:
	int m_zoom;
	Vector2D m_center = { 0, 0 };

public:
	Camera();
	
	int getZoom() const;
	void setZoom(int zoom);
	void zoomIn();
	void zoomOut();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void moveCenter(double deltaX, double deltaY);

    const Vector2D& getCenter() const { return m_center; }
};