/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#include "EndMenu.h"
#include <sstream>

EndMenu::EndMenu()
{
	score = 0;
	totalTime = 0;
	previousViewX = 0;
	previousViewY = 0;
}

void EndMenu::initializeBackgroundImage(const sf::Texture& texture)
{
	background.setTexture(texture);
	background.setPosition(0, 0);
}

void EndMenu::initializeInstructions(const char* text, const sf::Font& font, const int fontSize, const int posX, const int posY, const sf::Color& color)
{
	instructions.setString(text);
	instructions.setFont(font);
	instructions.setCharacterSize(fontSize);
	instructions.setPosition(posX, posY);
	instructions.setColor(color);
	instructions.setOutlineColor(sf::Color::Black);
	instructions.setOutlineThickness(2);
}

void EndMenu::initializeScore(char* text, const sf::Font& font, const int fontSize, const int posX, const int posY, const sf::Color& color)
{
	scoreText = text;
	scoreTxt.setFont(font);
	scoreTxt.setCharacterSize(fontSize);
	scoreTxt.setPosition(posX, posY);
	scoreTxt.setColor(color);
	scoreTxt.setOutlineColor(sf::Color::Black);
	scoreTxt.setOutlineThickness(2);
}

void EndMenu::initializeTime(char* text, const sf::Font& font, const int fontSize, const int posX, const int posY, const sf::Color& color)
{
	timeText = text;
	totalTimeTxt.setFont(font);
	totalTimeTxt.setCharacterSize(fontSize);
	totalTimeTxt.setPosition(posX, posY);
	totalTimeTxt.setColor(color);
	totalTimeTxt.setOutlineColor(sf::Color::Black);
	totalTimeTxt.setOutlineThickness(2);
}

void EndMenu::adjustToView(const sf::View& view)
{
	float posViewX = view.getCenter().x - view.getSize().x / 2;
	float posViewY = view.getCenter().y - view.getSize().y / 2;

	background.setPosition(background.getPosition().x - previousViewX + posViewX,
		background.getPosition().y - previousViewY + posViewY);

	scoreTxt.setPosition(scoreTxt.getPosition().x - previousViewX + posViewX,
		scoreTxt.getPosition().y - previousViewY + posViewY);

	totalTimeTxt.setPosition(totalTimeTxt.getPosition().x - previousViewX + posViewX,
		totalTimeTxt.getPosition().y - previousViewY + posViewY);

	instructions.setPosition(instructions.getPosition().x - previousViewX + posViewX,
		instructions.getPosition().y - previousViewY + posViewY);

	previousViewX = posViewX;
	previousViewY = posViewY;
}

void EndMenu::setScore(const int score)
{
	this->score = score;
}

void EndMenu::setTime(const int totalTime)
{
	this->totalTime = totalTime;
}

bool EndMenu::show(sf::RenderWindow& window, bool& mustReplay)
{
	// Reçoit les inputs ----------------------------------------------------
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
				mustReplay = true;
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				mustRunGame = true;
				mustReplay = false;
			}
		}

		if (event.type == sf::Event::JoystickButtonPressed)
		{
			// Bouton 1: X (PS) ou A (XBox)
			if (event.joystickButton.button == 1)
			{
				mustRunGame = true;
				mustReplay = true;
			}
			// Bouton 2: O (PS) ou B (XBox)
			else if (event.joystickButton.button == 2)
			{
				mustRunGame = true;
				mustReplay = false;
			}
		}
	}

	// Calcul des textes de score et de temps -------------------------------
	std::stringstream completeScoreText;
	completeScoreText << scoreText << score;
	scoreTxt.setString(completeScoreText.str());

	std::stringstream completeTimeText;
	if ((int)totalTime % 60 < 10)
	{
		completeTimeText << timeText << (int)totalTime / 60 << ":0" << (int)totalTime % 60;
	}
	else
	{
		completeTimeText << timeText << (int)totalTime / 60 << ":" << (int)totalTime % 60;
	}
	totalTimeTxt.setString(completeTimeText.str());

	// Affiche à l'écran ---------------------------------------------------
	window.draw(background);
	window.draw(scoreTxt);
	window.draw(totalTimeTxt);
	window.draw(instructions);

	window.display();

	return mustRunGame;
}