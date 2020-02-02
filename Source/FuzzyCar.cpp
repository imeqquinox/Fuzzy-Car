#include "FuzzyCar.h"

FuzzyCar::FuzzyCar()
{
	// Init fuzzycar 
	setSize(sf::Vector2f(50, 50));
	setPosition(300, 400);
	setFillColor(sf::Color::Green);
	scale = 0.5f; 

	// Init fuzzylogic engine 
	fuzzyLogic = new FuzzyLogic();
	fuzzyLogic->Init();
}

FuzzyCar::~FuzzyCar()
{
}

// Collision bounds for the car so it doesn't go off screen 
void FuzzyCar::CollisionBounds()
{
	//Right Wall
	if (getPosition().x >= 640 - getSize().x)
	{
		setPosition(640 - getSize().x, getPosition().y);
	}

	//Left Wall
	if (getPosition().x <= 0)
	{
		setPosition(0, getPosition().y);
	}

	//Top Wall
	if (getPosition().y <= 0)
	{
		setPosition(getPosition().x, 0);
	}

	//Bottom Wall
	if (getPosition().y >= 480 - getSize().y)
	{
		setPosition(getPosition().x, 480 - getSize().y);
	}
}

// Move the car based of the position of the line and velocity 
void FuzzyCar::Movement(Sprite line_sp)
{
	distance = this->getPosition().x - line_sp.getPosition().x; 

	velocity = fuzzyLogic->Process(distance, velocity);

	this->move(-velocity * scale, 0.0f);
}

float FuzzyCar::getVelocity()
{
	return velocity; 
}

float FuzzyCar::getDistance()
{
	return distance;
}