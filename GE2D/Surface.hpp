#pragma once

#include <string>

class Surface {
private:
	std::string m_path;
	int m_baseWidth; // In base units
	int m_baseHeight; // In base units
public:
	Surface(const std::string& path, const int baseWidth, const int baseHeight);
	virtual ~Surface() = default;

	const std::string& getPath() const;
	int getBaseWidth() const;
	int getBaseHeight() const;
};