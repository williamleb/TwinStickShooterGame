/*

Fichier cr�� par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vid�o III.

*/
#pragma once

#include "ProjectileType.h"
#include "Activatable.h"

/// <summary>
/// Repr�sente un projectile dans le jeu.
/// </summary>
class Projectile : public Activatable
{
	// Caract�ristiques des diff�rents projectiles
	static const int BULLET_SPEED = 1500;
	static const int BULLET_RANGE = 750;
	static const int FLAME_SPEED = 250;
	static const int FLAME_RANGE = 200;
	static const int MISSILE_SPEED = 1000;
	static const int MISSILE_RANGE = 750;
	static const int SCATTER_SPEED = 1500;
	static const int SCATTER_RANGE = 600;

	ProjectileType type;
	sf::Vector2f origin;
	float range;
public:	
	/// <summary>
	/// Cr�e un nouveau <see cref="Projetile"/>.
	/// </summary>
	/// <param name="type">Le type de projectile.</param>
	Projectile();

	/// <summary>
	/// Renvoie le type de projectile.
	/// </summary>
	/// <returns>Le type de projectile.</returns>
	ProjectileType getType() const;
	
	/// <summary>
	/// Retourne la port�e du projectile.
	/// </summary>
	/// <returns>La port�e du projectile.</returns>
	float getRange() const;

	/// <summary>
	/// Change le type de projectile.
	/// </summary>
	/// <returns>Le nouveau type de projectile.</returns>
	void setType(const ProjectileType type);

	/// <summary>
	/// Update le projectiles.
	/// Le d�sactive s'il va trop loin.
	/// </summary>
	/// <param name="deltaT">La diff�rence de temps.</param>
	void update(const float deltaT);

	/// <summary>
	/// Active le projectile.
	/// </summary>
	/// <param name="position">La nouvelle position du projectile activ�.</param>
	/// <param name="direction">La nouvelle position du projectile activ�.
	///													Si aucune direction n'est donn�e, la
	///													direction par d�faut est (0, 1)</param>
	void activate(const sf::Vector2f& position, const sf::Vector2f& direction = sf::Vector2f(0, 1));
};
