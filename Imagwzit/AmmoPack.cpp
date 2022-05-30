/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#include "AmmoPack.h"

AmmoPack::AmmoPack()
{
	nbrOfAddedAmmo = 0;
}

WeaponType AmmoPack::getWeaponType() const
{
	return weaponType;
}

void AmmoPack::setWeaponType(const WeaponType weaponType)
{
	this->weaponType = weaponType;

	// Change pour les caractéristiques du type.
	switch (weaponType)
	{
	case HandGunT:
		nbrOfAddedAmmo = HANDGUN_DEFAULT_AMMO_NBR;
		break;
	case SubmachineGunT:
		nbrOfAddedAmmo = SUBMACHINEGUN_DEFAULT_AMMO_NBR;
		break;
	case FlamethrowerT:
		nbrOfAddedAmmo = FLAMETHROWER_DEFAULT_AMMO_NBR;
		break;
	case ScatterGunT:
		nbrOfAddedAmmo = SCATTERGUN_DEFAULT_AMMO_NBR;
		break;
	case MissileLauncherT:
		nbrOfAddedAmmo = MISSILELAUNCHER_DEFAULT_AMMO_NBR;
		break;
	}
}

int AmmoPack::getNbr() const
{
	return nbrOfAddedAmmo;
}

void AmmoPack::pick(Weapon& weapon)
{
	// Ne rejoute que les munitions si l'arme
	// utilise les bons types de munitions.
	if (weapon.getType() == weaponType)
	{
		weapon.addAmmo(nbrOfAddedAmmo);
	}
	Bonus::pick();
}