/*

	Fichier cr�� par William Lebel (1638175)

	Dans le cadre du cours Programmation de jeux vid�o III.

*/
#pragma once

#include "Movable.h"
#include <SFML/System.hpp>

/// <summary>
/// Repr�sente un objet qui peut �tre activ� dans le jeu.
/// </summary>
/// <seealso cref="Movable" />
class Activatable : public Movable
{
	bool isActivated;

protected:	
	/// <summary>
	/// Cr�e un nouveau <see cref="Activatable"/>.
	/// Par d�faut, les objets activables sont d�sactiv�s.
	/// </summary>
	Activatable();

public:	
	/// <summary>
	/// Regarde si l'activable est activ�.
	/// </summary>
	/// <returns>True si l'objet est activ�; false sinon.</returns>
	bool activated() const;
	
	/// <summary>
	/// Active l'objet dans les m�mes conditions qu'il �tait avant d'�tre
	/// d�sactiv�.
	/// </summary>
	void activate();
	
	/// <summary>
	/// Active l'objet.
	/// </summary>
	/// <param name="position">La nouvelle position de l'objet activ�.</param>
	/// <param name="direction">La nouvelle position de l'objet activ�.
	///													Si aucune direction n'est donn�e, la
	///													direction par d�faut est (0, 1)</param>
	void activate(const sf::Vector2f& position, const sf::Vector2f& direction = sf::Vector2f(0, 1));
	
	/// <summary>
	/// D�sactive l'objet.
	/// </summary>
	void deactivate();
};