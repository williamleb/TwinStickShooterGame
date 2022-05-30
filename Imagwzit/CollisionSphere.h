/*

Fichier tiré de la correction de l'exercice 1 du cours Programmation 
de jeux vidéo III : Les sphères de collision.

Les commentaires ont été ajoutés par William Lebel (1638175)

*/
#pragma once

/// <summary>
/// Représente une sphère de collision.
/// Sert à déterminer la collsion entre deux objets.
/// </summary>
class CollisionSphere
{
public:	
	/// <summary>
	/// Crée une nouvelle <see cref="CollisionSphere"/>.
	/// </summary>
	CollisionSphere();
	
	/// <summary>
	/// Crée une nouvelle <see cref="CollisionSphere"/>.
	/// </summary>
	/// <param name="rayon">Le rayon de la sphère.</param>
	/// <param name="posX">La position en X du centre de la sphère.</param>
	/// <param name="posY">La position en Y du centre de la sphère.</param>
	CollisionSphere(const float rayon, const float posX, const float posY);
	
	/// <summary>
	/// Vérifie la collision entre deux sphères.
	/// Deux sphères qui se frôlent ne sont pas considérés en collision.
	/// </summary>
	/// <param name="autreSphere">La sphère avec laquelle vérifier la collision.</param>
	/// <returns>True si les sphères sont en collision; false sinon.</returns>
	bool verifierCollision(const CollisionSphere &autreSphere) const;
	
	/// <summary>
	/// Retourne le rayon de la sphère.
	/// </summary>
	/// <returns>Le rayon de la sphère.</returns>
	float getRayon() const;
	
	/// <summary>
	/// Retourne la position en X du centre de la sphère.
	/// </summary>
	/// <returns>La position en X du centre de la sphère.</returns>
	float getPosX() const;

	/// <summary>
	/// Retourne la position en Y du centre de la sphère.
	/// </summary>
	/// <returns>La position en Y du centre de la sphère.</returns>
	float getPosY() const;
	
	/// <summary>
	/// Change le rayon de la sphère.
	/// </summary>
	/// <param name="rayon">Le nouveau rayon.</param>
	void setRayon(const float rayon);
	
	/// <summary>
	/// Change la position en X du centre de la sphère.
	/// </summary>
	/// <param name="posX">La nouvelle position en X.</param>
	void setPosX(const float posX);

	/// <summary>
	/// Change la position en Y du centre de la sphère.
	/// </summary>
	/// <param name="posX">La nouvelle position en Y.</param>
	void setPosY(const float posY);

private:
	float rayon;
	float posX;
	float posY;
};


