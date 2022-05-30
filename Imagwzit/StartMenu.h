/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#pragma once

#include <SFML\Graphics.hpp>
#include <string>

/// <summary>
/// Représente le menu de début.
/// Le menu de fin affiche les commandes du jeu et
/// propose au joueur de jouer à la manette ou au clavier/souris.
/// </summary>
class StartMenu
{
	sf::Sprite controllerHelp;
	sf::Sprite keyboardAndMouseHelp;
	sf::Sprite background;
	sf::Text instructions;
	sf::Event event;
	float previousViewX;
	float previousViewY;

public:	
	/// <summary>
	/// Crée un nouveau <see cref="StartMenu"/>.
	/// </summary>
	StartMenu();
	
	/// <summary>
	/// Initialise l'image de fond.
	/// </summary>
	/// <param name="texture">La texture de l'image de fond.</param>
	void initializeBackgroundImage(const sf::Texture& texture);
	
	/// <summary>
	/// Initialise l'aide aux commandes à la manette.
	/// </summary>
	/// <param name="texture">La texture de l'aide.</param>
	/// <param name="posX">La position en X de l'aide.</param>
	/// <param name="posY">La position en Y de l'aide.</param>
	void initializeControllerHelp(const sf::Texture& texture, const int posX, const int posY);

	/// <summary>
	/// Initialise l'aide aux commandes au clavier/souris.
	/// </summary>
	/// <param name="texture">La texture de l'aide.</param>
	/// <param name="posX">La position en X de l'aide.</param>
	/// <param name="posY">La position en Y de l'aide.</param>
	void initializeKeyboardAndMouseHelp(const sf::Texture& texture, const int posX, const int posY);

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
	/// Ajuste la position des éléments de l'écran de fin pour qu'ils s'intègre à la vue.
	/// </summary>
	/// <param name="view">La vue.</param>
	void adjustToView(const sf::View& view);

	/// <summary>
	/// Affiche l'écran de début de jeu et permet au joueur de choisir
	/// s'il veut jouer à la manette ou au clavier/souris.
	/// </summary>
	/// <param name="window">Le contexte de dessin.</param>
	/// <param name="usesController">Une référence sur un booléen.
	///													 Lorsque le joueur a fait un choix, vaut true si
	///													 le joueur veut jouer à la manette; false s'il
	///													 veut jouer au clavier/souris.</param>
	/// <returns>True si le joueur a fait un choix, false sinon.</returns>
	bool show(sf::RenderWindow& window, bool& usesController);

};