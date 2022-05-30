/*

Fichier cr�� par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vid�o III.

*/
#pragma once
#include "GameObject.h"

/// <summary>
/// Repr�sente un bonus qui peut �tre rammass� dans le jeu.
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
	/// Cr�e un nouveau <see cref="Bonus"/>.
	/// </summary>
	Bonus();

	/// <summary>
	/// Rammasse le bonus.
	/// Cette m�thode est "protected", car chaque type de bonus
	/// pourrait vouloir demander ses propres param�tre pour la
	/// m�thode pick (et donc, ils ne voudraient pas qu'on puisse
	/// appeler cette m�thode publiquement).
	/// </summary>
	void pick();

public:	
	/// <summary>
	/// Retourne si le bonus est activ� ou non.
	/// </summary>
	/// <returns> <c>true</c> si le bonus est activ�;
	///	<c>false</c> sinon. </returns>
	bool isSpawned() const;	

	/// <summary>
	/// Active le bonus � la position sp�cifi�e.
	/// </summary>
	/// <param name="position">The position.</param>
	void spawn(const sf::Vector2f& position);

	/// <summary>
	/// Update le bonus.
	/// </summary>
	/// <param name="deltaT">La diff�rence de temps.</param>
	void update(const float deltaT);
	
	/// <summary>
	/// Fait dispara�tre le bonus du jeu.
	/// </summary>
	void deSpawn();
};