/*

Fichier cr�� par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vid�o III.

*/
#pragma once

#include "Activatable.h"
#include "Player.h"
#include <SFML/System.hpp>
#include "ZombieState.h"

/// <summary>
/// Repr�sente un zombie (un ennemi) dans le jeu.
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
	/// Cr�e un nouveau <see cref="Zombie"/>.
	/// </summary>
	Zombie();

	/// <summary>
	/// Update le zombie.
	/// Le fait bouger dans la direction du joueur.
	/// M�thode d�pr�ci�e.
	/// � la place, utilisez updateWithoutCollision.
	/// </summary>
	/// <param name="deltaT">La diff�rence de temps.</param>
	void update(const float deltaT);
	
	/// <summary>
	/// Update le zombie de telle sorte que les zombies
	/// ne se marchent pas dessus.
	/// </summary>
	/// <param name="deltaT">La diff�rence de temps.</param>
	/// <param name="allZombies">Un tableau contenant tous les zombies du jeu.</param>
	void updateWithoutCollision(const float deltaT, Zombie* allZombies);

	/// <summary>
	/// Retourne la cible du zombie.
	/// </summary>
	/// <returns>La cible du zombie.</returns>
	const sf::Vector2f& getTarget() const;
	
	/// <summary>
	/// Change la cible du zombie.
	/// La cible est stock�e en tant que position statique.
	/// Cette m�thode devrait �tre appel�e � chaque fois que la cible ce d�place.
	/// </summary>
	/// <param name="newTarget">La nouvelle cible du zombie.</param>
	/// <param name="mustComeCloser">True si le zombie doit s'approcher de la cible;
	///															 false s'il doit s'en �loigner.</param>
	void setTarget(const Player& newTarget, bool mustComeCloser = true);

	/// <summary>
	/// Change la cible du zombie.
	/// La cible est stock�e en tant que position statique.
	/// Cette m�thode devrait �tre appel�e � chaque fois que la cible ce d�place.
	/// </summary>
	/// <param name="newTarget">La nouvelle cible du zombie.</param>
	/// <param name="mustComeCloser">True si le zombie doit s'approcher de la cible;
	///															 false s'il doit s'en �loigner.</param>
	void setTarget(const sf::Vector2f& newTarget, bool mustComeCloser = true);
	
	/// <summary>
	/// Retourne l'�tat du zombie.
	/// </summary>
	/// <returns>L'�tat du zombie.</returns>
	ZombieState getState() const;

	/// <summary>
	/// Active le zombie dans les m�mes conditions qu'il �tait avant d'�tre
	/// d�sactiv�.
	/// </summary>
	void activate();

	/// <summary>
	/// Active le zombie.
	/// </summary>
	/// <param name="position">La nouvelle position du zombie activ�.</param>
	/// <param name="direction">La nouvelle position du zombie activ�.
	///													Si aucune direction n'est donn�e, la
	///													direction par d�faut est (0, 1)</param>
	void activate(const sf::Vector2f& position, const sf::Vector2f& direction = sf::Vector2f(0, 1));
};