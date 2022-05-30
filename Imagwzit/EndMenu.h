/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#pragma once

#include <SFML\Graphics.hpp>
#include <string>

/// <summary>
/// Représente le menu de fin.
/// Le menu de fin affiche le score et le temps final et
/// propose au joueur de refaire une autre partie ou de quitter.
/// </summary>
class EndMenu
{
	sf::Sprite background;
	sf::Text scoreTxt;
	sf::Text totalTimeTxt;
	sf::Text instructions;
	sf::Event event;
	int score;
	int totalTime;
	char* scoreText;
	char* timeText;
	float previousViewX;
	float previousViewY;

public:	
	/// <summary>
	/// Crée un nouveau <see cref="EndMenu"/>.
	/// </summary>
	EndMenu();
	
	/// <summary>
	/// Initialise l'image de fond.
	/// </summary>
	/// <param name="texture">La texture de l'image de fond.</param>
	void initializeBackgroundImage(const sf::Texture& texture);
	
	/// <summary>
	/// Initialise le texte d'instructions.
	/// </summary>
	/// <param name="text">Le texte d'instructions.</param>
	/// <param name="font">La police du texte d'instructions.</param>
	/// <param name="fontSize">La taille de la police du texte d'instructions.</param>
	/// <param name="posX">La position en X du texte d'instructions.</param>
	/// <param name="posY">La position en Y du texte d'instructions.</param>
	/// <param name="color">La couleur d texte d'instructions.</param>
	void initializeInstructions(const char* text, const sf::Font& font, const int fontSize, const int posX, const int posY, const sf::Color& color);
	
	/// <summary>
	/// Initialise le texte du score.
	/// </summary>
	/// <param name="text">Le texte d'introduction au score (le texte sera affiché ainsi: 
	///											«introduction au score»«score»".</param>
	/// <param name="font">La police du texte du score.</param>
	/// <param name="fontSize">La taille de la police du texte du score.</param>
	/// <param name="posX">La position en X du texte du score.</param>
	/// <param name="posY">La position en Y du texte du score.</param>
	/// <param name="color">La couleur d texte du score.</param>
	void initializeScore(char* text, const sf::Font& font, const int fontSize, const int posX, const int posY, const sf::Color& color);

	/// <summary>
	/// Initialise le texte du temps.
	/// </summary>
	/// <param name="text">Le texte d'introduction au temps (le texte sera affiché ainsi: 
	///											«introduction au temps»«tempsTotal»".</param>
	/// <param name="font">La police du texte du temps.</param>
	/// <param name="fontSize">La taille de la police du texte du temps.</param>
	/// <param name="posX">La position en X du texte du temps.</param>
	/// <param name="posY">La position en Y du texte du temps.</param>
	/// <param name="color">La couleur d texte du temps.</param>
	void initializeTime(char* text, const sf::Font& font, const int fontSize, const int posX, const int posY, const sf::Color& color);
	
	/// <summary>
	/// Ajuste la position des éléments de l'écran de fin pour qu'ils s'intègre à la vue.
	/// </summary>
	/// <param name="view">La vue.</param>
	void adjustToView(const sf::View& view);
	
	/// <summary>
	/// Change le score.
	/// Doit être appelé en fin de partie, avant d'afficher l'écran de fin.
	/// </summary>
	/// <param name="score">Le score de fin de partie du joueur.</param>
	void setScore(const int score);
	
	/// <summary>
	/// Change le temps de jeu.
	/// Doit être appelé en fin de partie, avant d'afficher l'écran de fin.
	/// </summary>
	/// <param name="totalTime">Le temps total de jeu du joueur.</param>
	void setTime(const int totalTime);
	
	/// <summary>
	/// Affiche l'écran de fin de jeu et permet au joueur de choisir
	/// s'il veut refaire une partie ou non.
	/// </summary>
	/// <param name="window">Le contexte de dessin.</param>
	/// <param name="mustReplay">Une référence sur un booléen.
	///													 Lorsque le joueur a fait un choix, vaut true si
	///													 le joueur veut refaire une partie; false sinon.</param>
	/// <returns>True si le joueur a fait un choix, false sinon.</returns>
	bool show(sf::RenderWindow& window, bool& mustReplay);

};