/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

/// <summary>
/// Le ScoreText est un text affiché dans le jeu
/// qui représente un score ajouté au joueur.
/// </summary>
/// <seealso cref="sf::Text" />
class ScoreText : public sf::Text
{
	static const int NBR_MILLISECONDS_OF_LIFETIME = 1000;

	int timer;

	bool spawned;

public:	
	/// <summary>
	/// Crée un nouveau <see cref="ScoreText"/>.
	/// </summary>
	ScoreText();
	
	/// <summary>
	/// Ajoute du temps au ScoreText.
	/// Permet de faire disparaître le ScoreText après
	/// un certain temps.
	/// </summary>
	/// <param name="nbrMilliseconds">Le nombre de millisecondes à ajouter.</param>
	void addTime(const int nbrMilliseconds);
	
	/// <summary>
	/// Ajoute le texte dans le jeu.
	/// </summary>
	/// <param name="text">Le texte à afficher.</param>
	/// <param name="position">La position du texte.</param>
	void spawn(const char* text, const sf::Vector2f& position);
	
	/// <summary>
	/// Fait disparaître le texte du jeu.
	/// </summary>
	void deSpawn();
	
	/// <summary>
	/// Indique si le texte est activé ou non.
	/// </summary>
	/// <returns>
	///   <c>true</c> si le texte est activé; <c>false</c> sinon.
	/// </returns>
	bool isSpawned() const;
};