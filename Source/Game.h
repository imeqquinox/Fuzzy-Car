#pragma once
#include <SFML\Graphics.hpp>
#include "Input.h"
#include "Line.h"
#include "FuzzyCar.h"

class Game
{
public:
	Game(sf::RenderWindow* hwnd);
	~Game();

	void Update(Input input);
	void Render();

private:
	sf::RenderWindow* window; 
	void beginDraw();
	void endDraw();

	Line line; 
	FuzzyCar fuzzyCar; 

	sf::Font font; 
	sf::Text positionTxt; 
	sf::Text velocityTxt; 
};

