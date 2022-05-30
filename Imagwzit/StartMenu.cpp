/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#include "StartMenu.h"
#include <SFML/System.hpp>

StartMenu::StartMenu()
{
	previousViewX = 0;
	previousViewY = 0;
}

void StartMenu::initializeBackgroundImage(const sf::Texture& texture)
{
	background.setTexture(texture);
	background.setPosition(0, 0);
}

void StartMenu::initializeControllerHelp(const sf::Texture& texture, const int posX, const int posY)
{
	controllerHelp.setTexture(texture);
	controllerHelp.setPosition(posX, posY);
}

void StartMenu::initializeKeyboardAndMouseHelp(const sf::Texture& texture, const int posX, const int posY)
{
	keyboardAndMouseHelp.setTexture(texture);
	keyboardAndMouseHelp.setPosition(posX, posY);
}

void StartMenu::initializeInstructions(const char* text, const sf::Font& font, const int fontSize, const int posX, const int posY, const sf::Color& color)
{
	instructions.setString(text);
	instructions.setFont(font);
	instructions.setCharacterSize(fontSize);
	instructions.setPosition(posX, posY);
	instructions.setColor(color);
	instructions.setOutlineColor(sf::Color::Black);
	instructions.setOutlineThickness(2);
}

void StartMenu::adjustToView(const sf::View& view)
{
	float posViewX = view.getCenter().x - view.getSize().x / 2;
	float posViewY = view.getCenter().y - view.getSize().y / 2;

	background.setPosition(background.getPosition().x - previousViewX + posViewX,
		background.getPosition().y - previousViewY + posViewY);

	controllerHelp.setPosition(controllerHelp.getPosition().x - previousViewX + posViewX,
		controllerHelp.getPosition().y - previousViewY + posViewY);

	keyboardAndMouseHelp.setPosition(keyboardAndMouseHelp.getPosition().x - previousViewX + posViewX,
		keyboardAndMouseHelp.getPosition().y - previousViewY + posViewY);

	instructions.setPosition(instructions.getPosition().x - previousViewX + posViewX,
		instructions.getPosition().y - previousViewY + posViewY);

	previousViewX = posViewX;
	previousViewY = posViewY;
}

bool StartMenu::show(sf::RenderWindow& window, bool& usesController)
{
	// Reçoit les inputs ---------------------------------------------------
	bool mustRunGame = false;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Return)
			{
				mustRunGame = true;
				usesController = false;
			}
		}

		if (event.type == sf::Event::JoystickButtonPressed)
		{
			// Bouton 1: X (PS) ou A (XBox)
			if (event.joystickButton.button == 1)
			{
				mustRunGame = true;
				usesController = true;
			}
		}
	}
	
	// Affiche à l'écran ----------------------------------------------------
	window.draw(background);
	window.draw(controllerHelp);
	window.draw(keyboardAndMouseHelp);
	window.draw(instructions);

	window.display();

	return mustRunGame;
}