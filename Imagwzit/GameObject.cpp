/*

Fichier cr�� par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vid�o III.

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
	// Change la collisionSphere d�pendemment du sprite --------------------

	// Le rayon est d�termin� en prenant la plus petite dimension.
	unsigned int textureWidth = texture.getSize().x;
	unsigned int textureHeight = texture.getSize().y;
	float radius = textureWidth <= textureHeight ? (float)textureWidth / 2.0f : (float)textureHeight / 2.0f;
	
	// D�finie le nouveau rayon de la sph�re de collision.
	collisionSphere.setRayon(radius);

	// Le nouvel origin du sprite se trouve au milieu de celui-ci.
	setOrigin(textureWidth / 2, textureHeight / 2);

	// App�le la m�thode correspondante de sf::Sprite ----------------------
	sf::Sprite::setTexture(texture, resetRect);
}

void GameObject::setPosition(float x, float y)
{
	// App�le la deuxi�me m�thode GameObject::setPosition.
	sf::Vector2f position(x, y);
	setPosition(position);
}

void GameObject::setPosition(const sf::Vector2f& position)
{
	// Change la collisionSphere d�pendemment de la nouvelle position ------
	collisionSphere.setPosX(position.x);
	collisionSphere.setPosY(position.y);

	// App�le la m�thode correspondate de sf::Sprite -----------------------
	sf::Sprite::setPosition(position);
}

bool GameObject::collidesWith(const GameObject& gameObject) const
{
	// V�rifie la collision entre la collisionSphere de l'objet et
	// la collisionSphere de l'autre objet.
	return collisionSphere.verifierCollision(gameObject.getCollisionSphere());
}

float GameObject::getAngleWith(const GameObject& gameObject) const
{
	// App�le la deuxi�me m�thode GameObject::getAngleWith.
	return getAngleWith(gameObject.getPosition().x, gameObject.getPosition().y);
}

float GameObject::getAngleWith(float x, float y) const
{
	// D�finit la distance en x pour ne pas avoir � faire une division par 0.
	float distX = (x - getPosition().x);
	if (distX == 0)
	{
		distX = ALMOST_0;
	}

	// D�termine l'angle
	float angle = atanf((y - getPosition().y) / distX);

	// Si la position est derri�re l'objet...
	if (x < getPosition().x)
	{
		// On ajoute un demi cercle � l'angle.
		angle += M_PI;
	}

	// Retourne l'angle en degr�s.
	return angle * RAD_TO_DEG;
}
