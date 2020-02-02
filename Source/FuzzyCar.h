#pragma once
#include "Sprite.h"
#include "Input.h"
#include "FuzzyLogic.h"

class FuzzyCar : public Sprite
{
public:
	FuzzyCar();
	~FuzzyCar();

	void Movement(Sprite line_sp);
	void CollisionBounds();
	float getVelocity();
	float getDistance();

private: 
	FuzzyLogic* fuzzyLogic; 
	float distance; 
	float velocity; 
	float scale; 
};

