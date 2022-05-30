/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#pragma once
#include "GameObject.h"

/// <summary>
/// Représente un bonus qui peut être rammassé dans le jeu.
/// </summary>
/// <seealso cref="GameObject" />
class Bonus : public GameObject
{
	static const int BONUS_DEFAULT_LIFETIME = 10000;

	// Timer de vie en millisecondes.
	int timer;
	bool spawned;
	
protected:	
	/// <summary>
	/// Crée un nouveau <see cref="Bonus"/>.
	/// </summary>
	Bonus();

	/// <summary>
	/// Rammasse le bonus.
	/// Cette méthode est "protected", car chaque type de bonus
	/// pourrait vouloir demander ses propres paramètre pour la
	/// méthode pick (et donc, ils ne voudraient pas qu'on puisse
	/// appeler cette méthode publiquement).
	/// </summary>
	void pick();

public:	
	/// <summary>
	/// Retourne si le bonus est activé ou non.
	/// </summary>
	/// <returns> <c>true</c> si le bonus est activé;
	///	<c>false</c> sinon. </returns>
	bool isSpawned() const;	

	/// <summary>
	/// Active le bonus à la position spécifiée.
	/// </summary>
	/// <param name="position">The position.</param>
	void spawn(const sf::Vector2f& position);

	/// <summary>
	/// Update le bonus.
	/// </summary>
	/// <param name="deltaT">La différence de temps.</param>
	void update(const float deltaT);
	
	/// <summary>
	/// Fait disparaître le bonus du jeu.
	/// </summary>
	void deSpawn();
};