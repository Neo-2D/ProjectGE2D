#pragma once

class GameObject {
public:
	virtual ~GameObject() = default;
		
	virtual bool init() = 0;
	virtual bool update() = 0;
};