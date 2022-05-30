/*

Fichier cr�� par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vid�o III.

*/
#pragma once
#include "Bonus.h"
#include "Weapon.h"

/// <summary>
/// Repr�sente un pack de munitions dans le jeu.
/// Un pack de munitions, lorsque rammass�, ajoute
/// des munitions � une arme.
/// </summary>
/// <seealso cref="Bonus" />
class AmmoPack : public Bonus
{
	// Caract�ristiques de chaque pack de munitions.
	static const int HANDGUN_DEFAULT_AMMO_NBR = 0;
	static const int SUBMACHINEGUN_DEFAULT_AMMO_NBR = 50;
	static const int FLAMETHROWER_DEFAULT_AMMO_NBR = 75;
	static const int SCATTERGUN_DEFAULT_AMMO_NBR = 25;
	static const int MISSILELAUNCHER_DEFAULT_AMMO_NBR = 20;

	// Le type d'arme pour lequel les munitions
	// fonctionnent.
	WeaponType weaponType;
	// Le nombre de munitions ajout�es.
	int nbrOfAddedAmmo;

public:	
	/// <summary>
	/// Cr�e un nouveau <see cref="AmmoPack"/>.
	/// </summary>
	AmmoPack();
	
	/// <summary>
	/// Retourne le type d'arme pour lequel les
	/// munitions du pack de munitions fonctionnent.
	/// </summary>
	/// <returns>Le type d'arme pour lequel ajouter des munitions.</returns>
	WeaponType getWeaponType() const;
	
	/// <summary>
	/// Change le type d'arme pour lequel des munitions
	/// peuvent �tre ajouter.
	/// Charge �galement les caract�ristiques de base
	/// pour ce type d'arme dans le pack de munitions.
	/// </summary>
	/// <param name="weaponType">Le nouveau type d'arme pour lequel des munitions
	///													 peuvent �tre ajout�es.</param>
	void setWeaponType(const WeaponType weaponType);
	
	/// <summary>
	/// Retourne le nombre de munitions que le pack de munitions ajoute.
	/// </summary>
	/// <returns>Le nombre de munitions ajout�s.</returns>
	int getNbr() const;

	/// <summary>
	/// Rammasse des munitions pour l'arme sp�cifi�e.
	/// L'arme doit �tre du m�me type que le bonus pour
	/// lui donner les munitions.
	/// </summary>
	/// <param name="weapon">L'arme � laquelle ajouter des munitions (l'attribut de l'arme est modifi�e).
	///												Elle doit �tre du m�me type que le bonus. Sinon
	///												aucune munition ne lui sera ajout�.</param>
	void pick(Weapon& weapon);
};