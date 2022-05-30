/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#include "Bonus.h"

Bonus::Bonus()
{
	spawned = false;
	timer = 0;
}

void Bonus::spawn(const sf::Vector2f& position)
{
	setPosition(position);
	spawned = true;
}

bool Bonus::isSpawned() const
{
	return spawned;
}

void Bonus::pick()
{
	deSpawn();
}

void Bonus::update(const float deltaT)
{
	timer += deltaT * 1000;
	// Si le bonus a vécu plus ou autant de temps
	// qu'il a d'alloué, on le retire du jeu.
	if (timer >= BONUS_DEFAULT_LIFETIME)
	{
		deSpawn();
	}
}

void Bonus::deSpawn()
{
	spawned = false;
	timer = 0;
}