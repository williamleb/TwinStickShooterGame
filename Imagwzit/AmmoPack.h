/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#pragma once
#include "Bonus.h"
#include "Weapon.h"

/// <summary>
/// Représente un pack de munitions dans le jeu.
/// Un pack de munitions, lorsque rammassé, ajoute
/// des munitions à une arme.
/// </summary>
/// <seealso cref="Bonus" />
class AmmoPack : public Bonus
{
	// Caractéristiques de chaque pack de munitions.
	static const int HANDGUN_DEFAULT_AMMO_NBR = 0;
	static const int SUBMACHINEGUN_DEFAULT_AMMO_NBR = 50;
	static const int FLAMETHROWER_DEFAULT_AMMO_NBR = 75;
	static const int SCATTERGUN_DEFAULT_AMMO_NBR = 25;
	static const int MISSILELAUNCHER_DEFAULT_AMMO_NBR = 20;

	// Le type d'arme pour lequel les munitions
	// fonctionnent.
	WeaponType weaponType;
	// Le nombre de munitions ajoutées.
	int nbrOfAddedAmmo;

public:	
	/// <summary>
	/// Crée un nouveau <see cref="AmmoPack"/>.
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
	/// peuvent être ajouter.
	/// Charge également les caractéristiques de base
	/// pour ce type d'arme dans le pack de munitions.
	/// </summary>
	/// <param name="weaponType">Le nouveau type d'arme pour lequel des munitions
	///													 peuvent être ajoutées.</param>
	void setWeaponType(const WeaponType weaponType);
	
	/// <summary>
	/// Retourne le nombre de munitions que le pack de munitions ajoute.
	/// </summary>
	/// <returns>Le nombre de munitions ajoutés.</returns>
	int getNbr() const;

	/// <summary>
	/// Rammasse des munitions pour l'arme spécifiée.
	/// L'arme doit être du même type que le bonus pour
	/// lui donner les munitions.
	/// </summary>
	/// <param name="weapon">L'arme à laquelle ajouter des munitions (l'attribut de l'arme est modifiée).
	///												Elle doit être du même type que le bonus. Sinon
	///												aucune munition ne lui sera ajouté.</param>
	void pick(Weapon& weapon);
};