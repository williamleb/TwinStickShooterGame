/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#pragma once

#include "Activatable.h"
#include "Player.h"
#include <SFML/System.hpp>
#include "ZombieState.h"

/// <summary>
/// Représente un zombie (un ennemi) dans le jeu.
/// </summary>
/// <seealso cref="Activatable" />
class Zombie : public Activatable
{
	static const int ZOMBIE_DEFAULT_SPEED = 100;
	static const int NBR_MILLISECONDS_OF_SPAWNING = 1000;

	sf::Vector2f target;
	int spawningTimer;
	ZombieState state;

public:	
	/// <summary>
	/// Crée un nouveau <see cref="Zombie"/>.
	/// </summary>
	Zombie();

	/// <summary>
	/// Update le zombie.
	/// Le fait bouger dans la direction du joueur.
	/// Méthode dépréciée.
	/// À la place, utilisez updateWithoutCollision.
	/// </summary>
	/// <param name="deltaT">La différence de temps.</param>
	void update(const float deltaT);
	
	/// <summary>
	/// Update le zombie de telle sorte que les zombies
	/// ne se marchent pas dessus.
	/// </summary>
	/// <param name="deltaT">La différence de temps.</param>
	/// <param name="allZombies">Un tableau contenant tous les zombies du jeu.</param>
	void updateWithoutCollision(const float deltaT, Zombie* allZombies);

	/// <summary>
	/// Retourne la cible du zombie.
	/// </summary>
	/// <returns>La cible du zombie.</returns>
	const sf::Vector2f& getTarget() const;
	
	/// <summary>
	/// Change la cible du zombie.
	/// La cible est stockée en tant que position statique.
	/// Cette méthode devrait être appelée à chaque fois que la cible ce déplace.
	/// </summary>
	/// <param name="newTarget">La nouvelle cible du zombie.</param>
	/// <param name="mustComeCloser">True si le zombie doit s'approcher de la cible;
	///															 false s'il doit s'en éloigner.</param>
	void setTarget(const Player& newTarget, bool mustComeCloser = true);

	/// <summary>
	/// Change la cible du zombie.
	/// La cible est stockée en tant que position statique.
	/// Cette méthode devrait être appelée à chaque fois que la cible ce déplace.
	/// </summary>
	/// <param name="newTarget">La nouvelle cible du zombie.</param>
	/// <param name="mustComeCloser">True si le zombie doit s'approcher de la cible;
	///															 false s'il doit s'en éloigner.</param>
	void setTarget(const sf::Vector2f& newTarget, bool mustComeCloser = true);
	
	/// <summary>
	/// Retourne l'état du zombie.
	/// </summary>
	/// <returns>L'état du zombie.</returns>
	ZombieState getState() const;

	/// <summary>
	/// Active le zombie dans les mêmes conditions qu'il était avant d'être
	/// désactivé.
	/// </summary>
	void activate();

	/// <summary>
	/// Active le zombie.
	/// </summary>
	/// <param name="position">La nouvelle position du zombie activé.</param>
	/// <param name="direction">La nouvelle position du zombie activé.
	///													Si aucune direction n'est donnée, la
	///													direction par défaut est (0, 1)</param>
	void activate(const sf::Vector2f& position, const sf::Vector2f& direction = sf::Vector2f(0, 1));
};