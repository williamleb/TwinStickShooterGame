/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#pragma once
#include "Projectile.h"
#include <SFML/System.hpp>
#include <chrono>
#include "WeaponType.h"

/// <summary>
/// Représente une arme qui peut être utilisée par le joueur.
/// </summary>
class Weapon
{	
	// Caractéristiques des différentes armes.
	const int HANDGUN_DEFAULT_AMMO = Weapon::InfiniteAmmo;
	static const int HANDGUN_DEFAULT_FIRERATE = 500;
	static const int SUBMACHINEGUN_DEFAULT_AMMO = 0;
	static const int SUBMACHINEGUN_DEFAULT_FIRERATE = 100;
	static const int FLAMETHROWER_DEFAULT_AMMO = 0;
	static const int FLAMETHROWER_DEFAULT_FIRERATE = 25;
	static const int SCATTERGUN_DEFAULT_AMMO = 0;
	static const int SCATTERGUN_DEFAULT_FIRERATE = 250;
	static const int MISSILELAUNCHER_DEFAULT_AMMO = 0;
	static const int MISSILELAUNCHER_DEFAULT_FIRERATE = 500;

	// Un tableau des projectiles que peut utiliser l'arme.
	Projectile* availableProjectiles;

	ProjectileType projectileType;
	WeaponType type;
	int ammo;
	int millisecondsSinceLastFired;

	// Nombre de millisecondes avant le prochain tir.
	int fireRate;

public:	
	/// <summary>
	/// Crée un nouveau <see cref="Weapon"/> relié à une partie.
	/// </summary>
	/// <param name="availableProjectiles">Le tableau de projectiles de la partie.</param>
	Weapon(Projectile* availableProjectiles);

	/// <summary>
	/// Valeur qui représente une infinité de munitions.
	/// </summary>
	static const int InfiniteAmmo;
	
	/// <summary>
	/// Retourne le type de projectile que l'arme tire.
	/// </summary>
	/// <returns>Le type de projectile que l'arme tire.</returns>
	ProjectileType getProjectileType() const;
	
	/// <summary>
	/// Retourne le type de l'arme.
	/// </summary>
	/// <returns>Le type de l'arme.</returns>
	WeaponType getType() const;

	/// <summary>
	/// Retourne la cadence de tir de l'arme.
	/// </summary>
	/// <returns>La cadence de tir de l'arme.</returns>
	int getFireRate() const;	

	/// <summary>
	/// Retourne le nombre de munitions de l'arme.
	/// </summary>
	/// <returns>Le nombre de munitions de l'arme.</returns>
	int getAmmo() const;
	
	/// <summary>
	/// Change le type de l'arme.
	/// </summary>
	/// <param name="type">Le type de l'arme.</param>
	void setType(const WeaponType type);
	
	/// <summary>
	/// Ajoute des munitions à l'arme.
	/// </summary>
	/// <param name="nbrOfAmmo">Le nombre de munitions à ajouter.</param>
	void addAmmo(int nbrOfAmmo);
	
	/// <summary>
	/// Tire avec l'arme.
	/// </summary>
	/// <param name="origin">L'origine du tir.</param>
	/// <param name="direction">La direction du tir.</param>
	void fire(const sf::Vector2f& origin, const sf::Vector2f& direction);
	
	/// <summary>
	/// Ajoute du temps à l'arme, ce qui lui sert à savoir
	/// quand elle doit tirer.
	/// </summary>
	/// <param name="milliseconds">Le nombre de millisecondes à ajouter.</param>
	void addTime(const int milliseconds);

	/// <summary>
	/// Remet les munitions à 0.
	/// </summary>
	void throwAllAmmo();

private:	
	/// <summary>
	/// Recherche dans le tableau des projectiles du jeu pour un projectile à ativer.
	/// </summary>
	/// <returns>L'index du projectile choisi dans le tableau des projectiles du jeu;
	///					 -1 si aucun projectile n'a été trouvé.</returns>
	int searchAvailableProjectile() const;
	
	/// <summary>
	/// Effectue un tir normal (un tir vers l'avant).
	/// </summary>
	/// <param name="origin">L'origine du tir.</param>
	/// <param name="direction">La direction du tir.</param>
	void defaultFire(const sf::Vector2f& origin, const sf::Vector2f& direction);
	
	/// <summary>
	/// Effectue un tir de type "scatter" (3 tirs, un vers
	/// et les deux autres à 45 degrés de par et d'autre).
	/// </summary>
	/// <param name="origin">L'origine du tir.</param>
	/// <param name="direction">La direction du tir du milieu.</param>
	void scatterFire(const sf::Vector2f& origin, const sf::Vector2f& direction);
	

};