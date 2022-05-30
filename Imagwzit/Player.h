/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#pragma once

#include "Movable.h"
#include "Inputs.h"
#include "Weapon.h"
#include "PlayerState.h"

/// <summary>
/// Représente une personne jouable dans le jeu.
/// </summary>
/// <seealso cref="Movable" />
class Player : public Movable
{
	static const int NBR_MILLISECONDS_INVINCIBILITY = 3000;
	static const int NBR_MILLISECONDS_FAINT = 2000;
	static const int DEFAULT_NBR_OF_LIVES = 5;
	static const int PLAYER_DEFAULT_SPEED = 200;
	
	int lives;
	const Inputs& inputs;
	Weapon* currentWeapon;
	PlayerState state;
	
	// Indique si le joueur utilise une manette (true)
	// ou le duo clavier/souris (false).
	bool usingController;

	// Timers pour les différents états.
	int faintingTimer;
	int invincibilityTimer;

public:	
	/// <summary>
	/// Crée un nouveau <see cref="Player"/>.
	/// </summary>
	/// <param name="inputs">Les inputs utilisés par le jeu.</param>
	/// <param name="weapon">Un pointeur sur l'arme du joueur.</param>
	Player(Inputs& inputs, Weapon* weapon);
	
	/// <summary>
	/// Tire avec l'arme du joueur.
	/// </summary>
	void fire();
	
	/// <summary>
	/// Retourne l'arme présente du joueur.
	/// </summary>
	/// <returns>L'arme présente du joueur.</returns>
	const Weapon* getCurrentWeapon() const;
	
	/// <summary>
	/// Change l'arme du joueur.
	/// </summary>
	/// <param name="weapon">Un pointeur sur la nouvelle arme du joueur.</param>
	void changeWeapon(Weapon* weapon);
	
	/// <summary>
	/// Retourne l'état du joueur.
	/// </summary>
	/// <returns>L'état du joueur.</returns>
	PlayerState getState() const;
	
	/// <summary>
	/// Retourne le nombre du vies du joueur.
	/// </summary>
	/// <returns>Le nombre du vies du joueur.</returns>
	int getNbrLives() const;
	
	/// <summary>
	/// Fait perdre une vie au joueur.
	/// </summary>
	void loseALife();
	
	/// <summary>
	/// Fait gagner une vie au joueur.
	/// </summary>
	void addALife();

	/// <summary>
	/// Update le joueur.
	/// </summary>
	/// <param name="deltaT">La différence de temps.</param>
	void update(const float deltaT);
	
	/// <summary>
	/// Définit si le joueur utilise la manette ou non.
	/// </summary>
	/// <param name="isUsingController">True si le joueur doit utiliser la manette; false sinon.</param>
	void isUsingController(const bool usingController);
};
