/*

Fichier tir� de la correction de l'exercice 1 du cours Programmation 
de jeux vid�o III : Les sph�res de collision.

Les commentaires ont �t� ajout�s par William Lebel (1638175)

*/
#pragma once

/// <summary>
/// Repr�sente une sph�re de collision.
/// Sert � d�terminer la collsion entre deux objets.
/// </summary>
class CollisionSphere
{
public:	
	/// <summary>
	/// Cr�e une nouvelle <see cref="CollisionSphere"/>.
	/// </summary>
	CollisionSphere();
	
	/// <summary>
	/// Cr�e une nouvelle <see cref="CollisionSphere"/>.
	/// </summary>
	/// <param name="rayon">Le rayon de la sph�re.</param>
	/// <param name="posX">La position en X du centre de la sph�re.</param>
	/// <param name="posY">La position en Y du centre de la sph�re.</param>
	CollisionSphere(const float rayon, const float posX, const float posY);
	
	/// <summary>
	/// V�rifie la collision entre deux sph�res.
	/// Deux sph�res qui se fr�lent ne sont pas consid�r�s en collision.
	/// </summary>
	/// <param name="autreSphere">La sph�re avec laquelle v�rifier la collision.</param>
	/// <returns>True si les sph�res sont en collision; false sinon.</returns>
	bool verifierCollision(const CollisionSphere &autreSphere) const;
	
	/// <summary>
	/// Retourne le rayon de la sph�re.
	/// </summary>
	/// <returns>Le rayon de la sph�re.</returns>
	float getRayon() const;
	
	/// <summary>
	/// Retourne la position en X du centre de la sph�re.
	/// </summary>
	/// <returns>La position en X du centre de la sph�re.</returns>
	float getPosX() const;

	/// <summary>
	/// Retourne la position en Y du centre de la sph�re.
	/// </summary>
	/// <returns>La position en Y du centre de la sph�re.</returns>
	float getPosY() const;
	
	/// <summary>
	/// Change le rayon de la sph�re.
	/// </summary>
	/// <param name="rayon">Le nouveau rayon.</param>
	void setRayon(const float rayon);
	
	/// <summary>
	/// Change la position en X du centre de la sph�re.
	/// </summary>
	/// <param name="posX">La nouvelle position en X.</param>
	void setPosX(const float posX);

	/// <summary>
	/// Change la position en Y du centre de la sph�re.
	/// </summary>
	/// <param name="posX">La nouvelle position en Y.</param>
	void setPosY(const float posY);

private:
	float rayon;
	float posX;
	float posY;
};


