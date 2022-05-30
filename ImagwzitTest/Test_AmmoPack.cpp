#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Imagwzit/AmmoPack.h"
#include "../Imagwzit/Projectile.h"
#include "../Imagwzit/Weapon.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjetSFMLTest
{
	TEST_CLASS(Test_AmmoPack)
	{
	public:
		/// <summary>
		/// Teste que le ramassage de munitions se fait correctement.
		/// </summary>
		TEST_METHOD(Test_getComboValue_01)
		{
			// Initialisation...
			AmmoPack pack;
			pack.setWeaponType(WeaponType::SubmachineGunT);

			Projectile projectiles[1];
			Weapon weapon(projectiles);
			weapon.setType(WeaponType::SubmachineGunT);

			int ammoBefore = weapon.getAmmo();

			// Appel de la m�thode.
			pack.pick(weapon);
			int ammoAfter = weapon.getAmmo();

			// Validation des r�sultats.
			Assert::IsTrue(ammoBefore < ammoAfter);
		}

		/// <summary>
		/// Teste que le ramassage de munitions ne se fait pas
		/// si l'arme n'est pas du m�me type que le pack.
		/// </summary>
		TEST_METHOD(Test_pick_02)
		{
			// Initialisation...
			AmmoPack pack;
			pack.setWeaponType(WeaponType::FlamethrowerT);

			Projectile projectiles[1];
			Weapon weapon(projectiles);
			weapon.setType(WeaponType::SubmachineGunT);

			int ammoBefore = weapon.getAmmo();

			// Appel de la m�thode.
			pack.pick(weapon);
			int ammoAfter = weapon.getAmmo();

			// Validation des r�sultats.
			Assert::AreEqual(ammoBefore, ammoAfter);
		}
	};
}