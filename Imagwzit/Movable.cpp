/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#define _USE_MATH_DEFINES

#include "Movable.h"
#include <SFML/System.hpp>
#include <cmath>
#include "Constantes.h"

Movable::Movable()
{
	speed = 0;

	// Commence par défaut vers le haut.
	// Appelle setAngle pour modifier la direction de façon cohérente.
	setAngle(270);
}

float Movable::getSpeed() const
{
	return this->speed;
}

float Movable::getAngle() const
{
	return this->angle;
}

const sf::Vector2f& Movable::getDirection() const
{
	return this->direction;
}

void Movable::setSpeed(const float speed)
{
	this->speed = speed;
}

void Movable::setAngle(const float angle, const bool changeSpriteAngle)
{
	// Change la direction pour qu'elle soit cohérente avec l'angle --------
	this->direction = convertAngleToDirection(angle);

	// Change l'angle ------------------------------------------------------
	this->angle = angle;

	// Change l'angle du sprite si on l'a demandé.
	if (changeSpriteAngle)
	{
		setRotation(this->angle);
	}
}

void Movable::setDirection(const sf::Vector2f& direction, const bool changeSpriteAngle)
{
	// Change l'angle pour qu'il soit cohérent avec la direction -----------
	
	this->angle = convertDirectionToAngle(direction);

	// Change l'angle du sprite si on l'a demandé.
	if (changeSpriteAngle)
	{
		setRotation(this->angle);
	}

	// Change la direction -------------------------------------------------
	this->direction = sf::Vector2f(direction);

}

void Movable::update(const float deltaT)
{
	// Calcule le nombre de pixels que le movable doit bouger.
	float nbrOfPixels = speed * deltaT;

	// Calcule la nouvelle position du movable.
	sf::Vector2f newPos = getPosition() + ( direction * nbrOfPixels );

	// Change la position.
	setPosition(newPos);
}

sf::Vector2f& Movable::convertAngleToDirection(const float angle)
{
	sf::Vector2f direction(cosf(angle * DEG_TO_RAD), sinf(angle * DEG_TO_RAD));
	return direction;
}

float Movable::convertDirectionToAngle(const sf::Vector2f& direction)
{
	float angle = 0.0f;

	// Si la direction en x est de 0, on change la valeur pour ne pas qu'il
	// y ait division par 0.
	float dirX = direction.x;
	if (dirX == 0)
	{
		dirX = ALMOST_0;
	}

	angle = atanf(direction.y / dirX);

	// Rajoute un demi-cercle à l'angle si le x est négatif.
	if (dirX < 0)
	{
		angle += M_PI;
	}

	// Transforme l'angle en degrés.
	angle *= RAD_TO_DEG;

	return angle;
}
