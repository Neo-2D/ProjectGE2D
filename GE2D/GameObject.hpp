#pragma once

class GameObject {
public:
	virtual ~GameObject() = default;
		
	virtual void init() = 0;
	virtual void update() = 0;
};