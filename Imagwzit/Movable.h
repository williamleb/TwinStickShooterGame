/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#pragma once
#include "GameObject.h"
#include <SFML/System.hpp>

/// <summary>
/// Représente un ojet qui peut bouger dans le jeu.
/// </summary>
/// <seealso cref="GameObject" />
class Movable : public GameObject
{
	sf::Vector2f direction;
	float speed;
	float angle;

protected:	
	/// <summary>
	/// Crée un nouveau <see cref="Movable"/>.
	/// </summary>
	Movable();

public:

	/// <summary>
	/// Update la position du movable.
	/// </summary>
	/// <param name="deltaT">La différence de temps.</param>
	void update(const float deltaT);

	// Get -----------------------------------------------------------------

	/// <summary>
	/// Retourne la vitesse du movable.
	/// </summary>
	/// <returns>La vitesse du movable.</returns>
	float getSpeed() const;
	
	/// <summary>
	/// Retourne l'angle du movable.
	/// </summary>
	/// <returns>L'angle du movable.</returns>
	float getAngle() const;
	
	/// <summary>
	/// Retourne la direction du movable.
	/// </summary>
	/// <returns>La direction du movable.</returns>
	const sf::Vector2f& getDirection() const;

	// Set -----------------------------------------------------------------
	
	/// <summary>
	/// Change la vitesse du movable.
	/// </summary>
	/// <param name="speed">La nouvelle vitesse.</param>
	void setSpeed(const float speed);
	
 	/// <summary>
	/// Change l'angle du movable.
	/// Change la direction dépendemment de l'angle.
	/// </summary>
	/// <param name="angle">Le nouvel angle.</param>
	/// <param name="changeSpriteAngle">True si on veut changer l'angle du sprite, false sinon.</param>
	void setAngle(const float angle, const bool changeSpriteAngle = true);
	
	/// <summary>
	/// Change la direction du movable.
	/// Change l'angle dépendemment de la direction.
	/// </summary>
	/// <param name="direction">True si on veut changer l'angle du sprite, false sinon.</param>
	void setDirection(const sf::Vector2f& direction, const bool changeSpriteAngle = true);

	// Méthodes statiques ---------------------------------------------------
	
	/// <summary>
	/// Convertit un angle en une direction.
	/// </summary>
	/// <param name="angle">L'angle à convertir.</param>
	/// <returns>La direction convertie.</returns>
	static sf::Vector2f& convertAngleToDirection(const float angle);
	
	/// <summary>
	/// Convertit une direction en un angle.
	/// </summary>
	/// <param name="direction">La direction à convertir.</param>
	/// <returns>L'angle converti.</returns>
	static float convertDirectionToAngle(const sf::Vector2f& direction);
};
