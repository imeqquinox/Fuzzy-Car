#include <iostream>
#include <SFML\Graphics.hpp>
#include <fl\Headers.h>
#include "Game.h"
#include "Input.h"
#include "FuzzyLogic.h"

using namespace std; 

void Menu();
void Gameplay();

void main(int agrc, char** argv[])
{
	cout << "CMP304: AI" << endl; 
	cout << "Lewis Wilson, ID:1600546" << endl; 

	Menu(); 
	Gameplay();
}

void Menu()
{
	// Set up input and fuzzy logic engine
	string txtInput;
	FuzzyLogic* testEngine = new FuzzyLogic();
	testEngine->Init();

	do
	{
		cout << "1. Test data" << endl;
		cout << "2. Gameplay" << endl;

		cin >> txtInput;

		// Test data input
		if (txtInput == "1")
		{
			float positionInput, velocityInput;

			cout << "Enter the position input (float): ";
			cin >> positionInput;

			cout << "Enter the velocity input (float): ";
			cin >> velocityInput;

			float value = testEngine->Process(positionInput, velocityInput);

			cout << value << endl;
		}

	} while (txtInput != "2");
}

void Gameplay()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "CMP 304");
	Game game(&window);
	Input input;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::KeyPressed:
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::MouseMoved:
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					input.setMouseLeftDown(true);
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRightDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRightDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}

		//Game state
		game.Update(input);
		game.Render();
	}
}