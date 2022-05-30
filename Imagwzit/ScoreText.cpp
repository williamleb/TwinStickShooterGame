/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#include "ScoreText.h"

ScoreText::ScoreText()
{
	timer = 0;
	spawned = false;
}

void ScoreText::addTime(const int nbrMilliseconds)
{
	if (spawned)
	{
		timer += nbrMilliseconds;

		// Si ça fait assez longtemps que le texte est activé, 
		// le le désactive.
		if (timer >= NBR_MILLISECONDS_OF_LIFETIME)
		{
			deSpawn();
		}
	}
}

void ScoreText::spawn(const char* text, const sf::Vector2f& position)
{
	timer = 0;
	spawned = true;
	setPosition(position);
	setString(text);
}

void ScoreText::deSpawn()
{
	if (spawned)
	{
		spawned = false;
	}
}

bool ScoreText::isSpawned() const
{
	return spawned;
}