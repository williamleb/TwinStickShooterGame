/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#define _USE_MATH_DEFINES

#include "GameObject.h"
#include "CollisionSphere.h"
#include <SFML/System.hpp>
#include <cmath>
#include "Constantes.h"

GameObject::GameObject()
{
	this->collisionSphere = CollisionSphere();
}

const CollisionSphere& GameObject::getCollisionSphere() const
{
	return this->collisionSphere;
}

void GameObject::setTexture(const sf::Texture &texture, bool resetRect)
{
	// Change la collisionSphere dépendemment du sprite --------------------

	// Le rayon est déterminé en prenant la plus petite dimension.
	unsigned int textureWidth = texture.getSize().x;
	unsigned int textureHeight = texture.getSize().y;
	float radius = textureWidth <= textureHeight ? (float)textureWidth / 2.0f : (float)textureHeight / 2.0f;
	
	// Définie le nouveau rayon de la sphère de collision.
	collisionSphere.setRayon(radius);

	// Le nouvel origin du sprite se trouve au milieu de celui-ci.
	setOrigin(textureWidth / 2, textureHeight / 2);

	// Appèle la méthode correspondante de sf::Sprite ----------------------
	sf::Sprite::setTexture(texture, resetRect);
}

void GameObject::setPosition(float x, float y)
{
	// Appèle la deuxième méthode GameObject::setPosition.
	sf::Vector2f position(x, y);
	setPosition(position);
}

void GameObject::setPosition(const sf::Vector2f& position)
{
	// Change la collisionSphere dépendemment de la nouvelle position ------
	collisionSphere.setPosX(position.x);
	collisionSphere.setPosY(position.y);

	// Appèle la méthode correspondate de sf::Sprite -----------------------
	sf::Sprite::setPosition(position);
}

bool GameObject::collidesWith(const GameObject& gameObject) const
{
	// Vérifie la collision entre la collisionSphere de l'objet et
	// la collisionSphere de l'autre objet.
	return collisionSphere.verifierCollision(gameObject.getCollisionSphere());
}

float GameObject::getAngleWith(const GameObject& gameObject) const
{
	// Appèle la deuxième méthode GameObject::getAngleWith.
	return getAngleWith(gameObject.getPosition().x, gameObject.getPosition().y);
}

float GameObject::getAngleWith(float x, float y) const
{
	// Définit la distance en x pour ne pas avoir à faire une division par 0.
	float distX = (x - getPosition().x);
	if (distX == 0)
	{
		distX = ALMOST_0;
	}

	// Détermine l'angle
	float angle = atanf((y - getPosition().y) / distX);

	// Si la position est derrière l'objet...
	if (x < getPosition().x)
	{
		// On ajoute un demi cercle à l'angle.
		angle += M_PI;
	}

	// Retourne l'angle en degrés.
	return angle * RAD_TO_DEG;
}
