/*

	Fichier créé par William Lebel (1638175)

	Dans le cadre du cours Programmation de jeux vidéo III.

*/
#pragma once

#include "Movable.h"
#include <SFML/System.hpp>

/// <summary>
/// Représente un objet qui peut être activé dans le jeu.
/// </summary>
/// <seealso cref="Movable" />
class Activatable : public Movable
{
	bool isActivated;

protected:	
	/// <summary>
	/// Crée un nouveau <see cref="Activatable"/>.
	/// Par défaut, les objets activables sont désactivés.
	/// </summary>
	Activatable();

public:	
	/// <summary>
	/// Regarde si l'activable est activé.
	/// </summary>
	/// <returns>True si l'objet est activé; false sinon.</returns>
	bool activated() const;
	
	/// <summary>
	/// Active l'objet dans les mêmes conditions qu'il était avant d'être
	/// désactivé.
	/// </summary>
	void activate();
	
	/// <summary>
	/// Active l'objet.
	/// </summary>
	/// <param name="position">La nouvelle position de l'objet activé.</param>
	/// <param name="direction">La nouvelle position de l'objet activé.
	///													Si aucune direction n'est donnée, la
	///													direction par défaut est (0, 1)</param>
	void activate(const sf::Vector2f& position, const sf::Vector2f& direction = sf::Vector2f(0, 1));
	
	/// <summary>
	/// Désactive l'objet.
	/// </summary>
	void deactivate();
};