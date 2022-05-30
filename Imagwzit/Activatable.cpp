/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#include "Activatable.h"
#include <SFML\System.hpp>

Activatable::Activatable()
{
	isActivated = false;
}

bool Activatable::activated() const
{
	return isActivated;
}

void Activatable::activate()
{
	isActivated = true;
}

void Activatable::activate(const sf::Vector2f& position,const sf::Vector2f& direction)
{
	isActivated = true;
	this->setPosition(position);
	this->setDirection(direction);
}

void Activatable::deactivate()
{
	isActivated = false;
}
