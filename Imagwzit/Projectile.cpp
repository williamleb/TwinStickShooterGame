/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#include "Projectile.h"

Projectile::Projectile()
{
	range = 0; 
	origin = sf::Vector2f();
}

ProjectileType Projectile::getType() const
{
	return type;
}

float Projectile::getRange() const
{
	return range;
}

void Projectile::setType(const ProjectileType type)
{
	this->type = type;

	// Change pour les caractéristiques par défaut du type de projectile.
	switch (type)
	{
	case ProjectileType::BulletT:
		setSpeed(BULLET_SPEED);
		range = BULLET_RANGE;
		break;
	case ProjectileType::FlameT:
		setSpeed(FLAME_SPEED);
		range = FLAME_RANGE;
		break;
	case ProjectileType::MissileT:
		setSpeed(MISSILE_SPEED);
		range = MISSILE_RANGE;
		break;
	case ProjectileType::ScatterT:
		setSpeed(SCATTER_SPEED);
		range = SCATTER_RANGE;
		break;
	}
}

void Projectile::update(const float deltaT)
{
	if (activated())
	{
		Movable::update(deltaT);

		// S'il est allé plus loin que son range, on le désactive.
		// (posX - origX)^2 + (posY - origY)^2 = dist^2
		sf::Vector2f pos = getPosition();
		if ( (pos.x - origin.x) * (pos.x - origin.x) + (pos.y - origin.y) * (pos.y - origin.y) > range * range)
		{
			deactivate();
		}
	}
}

void Projectile::activate(const sf::Vector2f& position, const sf::Vector2f& direction)
{
	// Détermine l'origine du missile (pour savoir si le missile a sorti de son range).
	origin = position;
	Activatable::activate(position, direction);
}
