#include "Game.h"

Game::Game(sf::RenderWindow* hwnd)
{
	window = hwnd; 

	// Load in font
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Couldn't load font";
	}

	// Position text setup
	positionTxt.setFont(font);
	positionTxt.setCharacterSize(16);
	positionTxt.setString("Line Position: ");
	positionTxt.setFillColor(sf::Color::Magenta);

	// Velocity text setup
	velocityTxt.setFont(font);
	velocityTxt.setCharacterSize(16);
	velocityTxt.setString("Velocity: ");
	velocityTxt.setFillColor(sf::Color::Magenta);
	velocityTxt.setPosition(0.0f, 25.0f);
}

Game::~Game()
{
}

void Game::Update(Input input)
{
	// Update line and car
	line.Movement(input);
	fuzzyCar.Movement(line);
	fuzzyCar.CollisionBounds();

	// Update the text output based off current position of line and velocity 
	positionTxt.setString("Distance: " + std::to_string(fuzzyCar.getDistance()));
	velocityTxt.setString("Velocity: " + std::to_string(fuzzyCar.getVelocity()));
}

void Game::Render()
{
	// Render objects to screen 
	beginDraw();
	window->draw(line);
	window->draw(fuzzyCar);
	window->draw(positionTxt);
	window->draw(velocityTxt);
	endDraw();
}

void Game::beginDraw()
{
	window->clear(sf::Color::Black);
}

void Game::endDraw()
{
	window->display();
}