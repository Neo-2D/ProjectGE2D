#pragma once

class Camera {
private:
	int m_zoom;

public:
	Camera();
	
	int getZoom() const;
	void setZoom(int zoom);
	void zoomIn();
	void zoomOut();
};