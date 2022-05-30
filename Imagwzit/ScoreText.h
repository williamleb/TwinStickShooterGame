/*

Fichier cr�� par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vid�o III.

*/
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

/// <summary>
/// Le ScoreText est un text affich� dans le jeu
/// qui repr�sente un score ajout� au joueur.
/// </summary>
/// <seealso cref="sf::Text" />
class ScoreText : public sf::Text
{
	static const int NBR_MILLISECONDS_OF_LIFETIME = 1000;

	int timer;

	bool spawned;

public:	
	/// <summary>
	/// Cr�e un nouveau <see cref="ScoreText"/>.
	/// </summary>
	ScoreText();
	
	/// <summary>
	/// Ajoute du temps au ScoreText.
	/// Permet de faire dispara�tre le ScoreText apr�s
	/// un certain temps.
	/// </summary>
	/// <param name="nbrMilliseconds">Le nombre de millisecondes � ajouter.</param>
	void addTime(const int nbrMilliseconds);
	
	/// <summary>
	/// Ajoute le texte dans le jeu.
	/// </summary>
	/// <param name="text">Le texte � afficher.</param>
	/// <param name="position">La position du texte.</param>
	void spawn(const char* text, const sf::Vector2f& position);
	
	/// <summary>
	/// Fait dispara�tre le texte du jeu.
	/// </summary>
	void deSpawn();
	
	/// <summary>
	/// Indique si le texte est activ� ou non.
	/// </summary>
	/// <returns>
	///   <c>true</c> si le texte est activ�; <c>false</c> sinon.
	/// </returns>
	bool isSpawned() const;
};