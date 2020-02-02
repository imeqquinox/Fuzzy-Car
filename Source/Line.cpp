#include "Line.h"

Line::Line()
{
	// Init line object
	setSize(sf::Vector2f(20, 1500));
	setPosition(320, 0);
	setFillColor(sf::Color::Cyan);
}

Line::~Line()
{
}

void Line::Movement(Input input)
{
	// Move line based off position of mouse 
	setPosition(input.getMouseX(), 0.0f);
}
