/*

Fichier cr�� par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vid�o III.

*/
#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "CollisionSphere.h"

/// <summary>
/// Repr�sente un objet de jeu qui peut �tre plac� dans celui-ci.
/// </summary>
/// <seealso cref="sf::Sprite" />
class GameObject : public sf::Sprite
{
	CollisionSphere collisionSphere;

protected:	
	/// <summary>
	/// Cr�e un nouveau <see cref="GameObject"/>.
	/// </summary>
	GameObject();

public:	
	/// <summary>
	/// Retourne la sph�re de collision de l'objet.
	/// </summary>
	/// <returns>La sph�re de collision de l'objet.</returns>
	const CollisionSphere& getCollisionSphere() const;
	
	/// <summary>
	/// Change la texture de l'objet.
	/// Override la m�thode correspondante de sf::Sprite.
	/// </summary>
	/// <param name="texture">La nouvelle texture de l'objet.</param>
	/// <param name="resetRect">Est-ce que le textureRect devrait �tre redimensionner selon la nouvelle texture?</param>
	void setTexture(const sf::Texture &texture, bool resetRect = false);
	
	/// <summary>
	/// Change la position de l'objet.
	/// Override la m�thode correspondante de sf::Sprite.
	/// </summary>
	/// <param name="x">La nouvelle position en x de l'objet.</param>
	/// <param name="y">La nouvelle position en y de l'objet.</param>
	void setPosition(float x, float y);
	
	/// <summary>
	/// Change la position de l'objet.
	/// Override la m�thode correspondante de sf::Sprite.
	/// </summary>
	/// <param name="position">La nouvelle position de l'objet.</param>
	void setPosition(const sf::Vector2f& position);
	
	/// <summary>
	/// Regarde si l'objet est en collision avec un autre objet.
	/// </summary>
	/// <param name="gameObject">L'objet avec lequel v�rifier la collision.</param>
	/// <returns>True s'il y a collision, false sinon.</returns>
	bool collidesWith(const GameObject& gameObject) const;
	
	/// <summary>
	/// Calcule l'angle entre l'objet et un autre objet.
	/// </summary>
	/// <param name="gameObject">L'objet avec lequel calculer l'angle.</param>
	/// <returns>L'angle entre l'objet et celui pass� en param�tre.</returns>
	float getAngleWith(const GameObject& gameObject) const;
	
	/// <summary>
	/// Calcule l'angle entre l'objet et une position sur le jeu.
	/// </summary>
	/// <param name="x">La position en x avec laquelle calculer l'angle.</param>
	/// <param name="y">La position en y avec laquelle calculer l'angle.</param>
	/// <returns>L'angle entre l'objet et la position.</returns>
	float getAngleWith(float x, float y) const;

};