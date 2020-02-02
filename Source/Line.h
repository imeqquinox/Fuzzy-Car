#pragma once
#include <SFML\Graphics.hpp>
#include "Sprite.h"
#include "Input.h"

class Line : public Sprite
{
public:
	Line();
	~Line();

	void Movement(Input input);
};

