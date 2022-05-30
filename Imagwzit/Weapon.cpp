/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#include "Weapon.h"
#include "Game.h"
#include <cstdio>
#include <SFML/System.hpp>
#include <chrono>

const int Weapon::InfiniteAmmo = std::numeric_limits<int>::max();

Weapon::Weapon(Projectile* availableProjectiles)
{
	this->availableProjectiles = availableProjectiles;
	ammo = 0;
	fireRate = 0;
	projectileType = ProjectileType::BulletT;
	millisecondsSinceLastFired = fireRate;
}

ProjectileType Weapon::getProjectileType() const
{
	return projectileType;
}

WeaponType Weapon::getType() const
{
	return type;
}

int Weapon::getFireRate() const
{
	return fireRate;
}

int Weapon::getAmmo() const
{
	return ammo;
}

void Weapon::setType(const WeaponType type)
{
	this->type = type;

	// Change pour les caractéristiques par défaut du type d'arme.
	switch (type)
	{
	case HandGunT:
		projectileType = ProjectileType::BulletT;
		ammo = HANDGUN_DEFAULT_AMMO;
		fireRate = HANDGUN_DEFAULT_FIRERATE;
		break;
	case SubmachineGunT:
		projectileType = ProjectileType::BulletT;
		ammo = SUBMACHINEGUN_DEFAULT_AMMO;
		fireRate = SUBMACHINEGUN_DEFAULT_FIRERATE;
		break;
	case FlamethrowerT:
		projectileType = ProjectileType::FlameT;
		ammo = FLAMETHROWER_DEFAULT_AMMO;
		fireRate = FLAMETHROWER_DEFAULT_FIRERATE;
		break;
	case ScatterGunT:
		projectileType = ProjectileType::ScatterT;
		ammo = SCATTERGUN_DEFAULT_AMMO;
		fireRate = SCATTERGUN_DEFAULT_FIRERATE;
		break;
	case MissileLauncherT:
		projectileType = ProjectileType::MissileT;
		ammo = MISSILELAUNCHER_DEFAULT_AMMO;
		fireRate = MISSILELAUNCHER_DEFAULT_FIRERATE;
		break;
	}
	millisecondsSinceLastFired = fireRate;
}

void Weapon::addAmmo(int nbrOfAmmo)
{
	if (ammo != InfiniteAmmo)
	{
		ammo += nbrOfAmmo;
	}
}

void Weapon::fire(const sf::Vector2f& origin, const sf::Vector2f& direction)
{
	// Si la fréquence de tir est respectée...
	if (millisecondsSinceLastFired >= fireRate)
	{
		// S'il nous reste des munitions...
		if (ammo > 0)
		{
			// On redémare le « timer » pour le tir.
			millisecondsSinceLastFired = 0;

			// On effectue un tir différent selon le type d'arme.
			switch (type)
			{
			case ScatterGunT:
				scatterFire(origin, direction);
				break;
			default:
				defaultFire(origin, direction);
				break;
			}

			// Si on n'a pas une infinité de munitions...
			if (ammo != InfiniteAmmo)
			{
				// On enlève une munition.
				ammo--;
			}
		}
	}
}

void Weapon::defaultFire(const sf::Vector2f& origin, const sf::Vector2f& direction)
{
	int indexOfAvailableProjectile = searchAvailableProjectile();
	// Si on a trouvé un projectile...
	if (indexOfAvailableProjectile != -1)
	{
		// On active le projectile
		availableProjectiles[indexOfAvailableProjectile].activate(
			origin,
			direction
		);
	}
}

void Weapon::scatterFire(const sf::Vector2f& origin, const sf::Vector2f& direction)
{
	float fireAngle = Movable::convertDirectionToAngle(direction);
	// Tire trois tirs avec des angles différents.
	sf::Vector2f rightScatterDirection = Movable::convertAngleToDirection(fireAngle + 45);
	Weapon::defaultFire(origin, rightScatterDirection);
	Weapon::defaultFire(origin, direction);
	sf::Vector2f leftScatterDirection = Movable::convertAngleToDirection(fireAngle - 45);
	Weapon::defaultFire(origin, leftScatterDirection);
}

void Weapon::addTime(const int milliseconds)
{
	if (millisecondsSinceLastFired + milliseconds <= fireRate)
	{
		millisecondsSinceLastFired += milliseconds;
	}
	else
	{
		millisecondsSinceLastFired = fireRate;
	}
}

int Weapon::searchAvailableProjectile() const
{
	int indexOfProjectile = -1;
	int currentIndex = 0;
	// Tant qu'on ne trouve pas de projectile qui correspond à la demande et
	// qu'on n'a pas fini de parcourir le tableau...
	while (indexOfProjectile == -1 && currentIndex < Game::NBR_OF_LOADED_PROJECTILES)
	{
		// Si on trouve un projectile qui n'est pas déjà activé et qui est du type de l'arme...
		if (! (availableProjectiles[currentIndex].activated()) &&
				availableProjectiles[currentIndex].getType() == projectileType)
		{
			// On sauvegarde sa position.
			indexOfProjectile = currentIndex;
		}
		++currentIndex;
	}
	return indexOfProjectile;
}

void Weapon::throwAllAmmo()
{
	if (ammo != InfiniteAmmo)
	{
		ammo = 0;
	}
}
