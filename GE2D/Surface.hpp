#pragma once

#include <string>

class Surface {
private:
	std::string m_path;
	int m_baseWidth; // In tiles
	int m_baseHeight; // In tiles
	float m_x; // In the world's coordinate system
	float m_y; // In the world's coordinate system
public:
	Surface(const std::string& path, const int baseWidth, const int baseHeight, const float x, const float y);
	virtual ~Surface() = default;

	const std::string& getPath() const;
	int getBaseWidth() const;
	int getBaseHeight() const;
	float getX() const;
	float getY() const;
};