/*

Fichier tiré de la correction de l'exercice 1 du cours Programmation 
de jeux vidéo III : Les sphères de collision.

*/
#include <cmath>  //sqrt
#include <cstdlib> //rand
#include "CollisionSphere.h"

CollisionSphere::CollisionSphere()
{
	this->rayon = 1;
	this->posX = 0;
	this->posY = 0;
}

CollisionSphere::CollisionSphere(const float rayon, const float posX, const float posY)
{
	this->rayon = rayon;
	this->posX = posX;
	this->posY = posY;
}

bool CollisionSphere::verifierCollision(const CollisionSphere &autreSphere) const
{
	float LigneX = this->posX - autreSphere.posX;
	float LigneY = this->posY - autreSphere.posY;

	float distance = sqrt(LigneX * LigneX + LigneY * LigneY);

	// Deux sphères qui se touchent mais ne sont pas en 
	// intersection en sont pas considérées en collision
	if (distance < this->rayon + autreSphere.rayon)
	{
		return true;
	}

	return false;
}

float CollisionSphere::getRayon() const
{
	return rayon;
}

float CollisionSphere::getPosX() const
{
	return posX;
}

float CollisionSphere::getPosY() const
{
	return posY;
}

void CollisionSphere::setRayon(const float rayon)
{
	this->rayon = rayon;
}

void CollisionSphere::setPosX(const float posX)
{
	this->posX = posX;
}

void CollisionSphere::setPosY(const float posY)
{
	this->posY = posY;
}