#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Imagwzit/Weapon.h"

#define FORTYFIVE_DEGREES_DIRECTION 0.70710678118654752440084436210485
#define threshold 0.01

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjetSFMLTest
{
	TEST_CLASS(Test_Player)
	{
	public:
		/// <summary>
		/// Teste le constructeur de Weapon.
		/// </summary>
		TEST_METHOD(Test_Weapon_01)
		{
			// Initialisation...
			Projectile projectiles[1];
			Weapon weapon(projectiles);

			// Validation des résultats
			Assert::AreEqual(0, weapon.getAmmo());
			Assert::AreEqual(0, weapon.getFireRate());
		}

		/// <summary>
		/// Teste que la méthode fire active un projectile
		/// à la bonne place et à la bonne direction.
		/// </summary>
		TEST_METHOD(Test_fire_01)
		{
			// Initialisation...
			Projectile projectiles[1];
			projectiles[0].setType(ProjectileType::BulletT);
			Weapon weapon(projectiles);
			weapon.setType(WeaponType::HandGunT);
			weapon.addAmmo(1);

			sf::Vector2f position(0, 0);
			sf::Vector2f direction(0, 1);

			// Test de la méthode.
			weapon.fire(position, direction);

			// Validation des résultats
			Assert::IsTrue(projectiles[0].activated());
			Assert::AreEqual(position.x, projectiles[0].getPosition().x);
			Assert::AreEqual(position.y, projectiles[0].getPosition().y);
			Assert::AreEqual(direction.x, projectiles[0].getDirection().x);
			Assert::AreEqual(direction.y, projectiles[0].getDirection().y);
		}

		/// <summary>
		/// Teste que la méthode fire active le bon projectile du tableau des projectiles.
		/// </summary>
		TEST_METHOD(Test_fire_02)
		{
			// Initialisation...
			Projectile projectiles[2];
			projectiles[0].setType(ProjectileType::FlameT);
			projectiles[1].setType(ProjectileType::BulletT);
			Weapon weapon(projectiles);
			weapon.setType(WeaponType::HandGunT);
			weapon.addAmmo(1);

			sf::Vector2f position(0, 0);
			sf::Vector2f direction(0, 1);

			// Test de la méthode.
			weapon.fire(position, direction);

			// Validation des résultats
			Assert::IsFalse(projectiles[0].activated());
			Assert::IsTrue(projectiles[1].activated());
		}

		/// <summary>
		/// Teste que la méthode fire n'active pas un mauvais projectile.
		/// </summary>
		TEST_METHOD(Test_fire_03)
		{
			// Initialisation...
			Projectile projectiles[1];
			projectiles[0].setType(ProjectileType::FlameT);
			Weapon weapon(projectiles);
			weapon.setType(WeaponType::HandGunT);
			weapon.addAmmo(1);

			sf::Vector2f position(0, 0);
			sf::Vector2f direction(0, 1);

			// Test de la méthode.
			weapon.fire(position, direction);

			// Validation des résultats
			Assert::IsFalse(projectiles[0].activated());
		}

		/// <summary>
		/// Teste que la méthode fire passe par dessus les projectiles activés.
		/// </summary>
		TEST_METHOD(Test_fire_04)
		{
			// Initialisation...
			Projectile projectiles[2];
			projectiles[0].setType(ProjectileType::BulletT);
			projectiles[1].setType(ProjectileType::BulletT);
			Weapon weapon(projectiles);
			weapon.setType(WeaponType::HandGunT);
			weapon.addAmmo(2);

			sf::Vector2f position(0, 0);
			sf::Vector2f direction(0, 1);

			// Test de la méthode.
			weapon.fire(position, direction);
			weapon.addTime(weapon.getFireRate() + 1);
			weapon.fire(position, direction);

			// Validation des résultats
			Assert::IsTrue(projectiles[0].activated());
			Assert::IsTrue(projectiles[1].activated());
		}

		/// <summary>
		/// Teste que la méthode fire tire un tir de type "scatter" correctement.
		/// </summary>
		TEST_METHOD(Test_fire_05)
		{
			// Initialisation...
			Projectile projectiles[5];
			projectiles[0].setType(ProjectileType::BulletT);
			projectiles[1].setType(ProjectileType::ScatterT);
			projectiles[2].setType(ProjectileType::BulletT);
			projectiles[3].setType(ProjectileType::ScatterT);
			projectiles[4].setType(ProjectileType::ScatterT);
			Weapon weapon(projectiles);
			weapon.setType(WeaponType::ScatterGunT);
			weapon.addAmmo(3);
			weapon.addTime(weapon.getFireRate());

			sf::Vector2f position(0, 0);
			sf::Vector2f direction(1, 0);

			// Test de la méthode.
			weapon.fire(position, direction);

			// Validation des résultats
			Assert::IsFalse(projectiles[0].activated());

			Assert::IsTrue(projectiles[1].activated());
			Assert::AreEqual(position.x, projectiles[1].getPosition().x);
			Assert::AreEqual(position.y, projectiles[1].getPosition().y);
			Assert::IsTrue(abs((float)FORTYFIVE_DEGREES_DIRECTION - abs(projectiles[1].getDirection().x)) < threshold);
			Assert::IsTrue(abs((float)FORTYFIVE_DEGREES_DIRECTION - abs(projectiles[1].getDirection().y)) < threshold);

			Assert::IsFalse(projectiles[2].activated());

			Assert::IsTrue(projectiles[3].activated());
			Assert::AreEqual(position.x, projectiles[3].getPosition().x);
			Assert::AreEqual(position.y, projectiles[3].getPosition().y);
			Assert::AreEqual(direction.x, projectiles[3].getDirection().x);
			Assert::AreEqual(direction.y, projectiles[3].getDirection().y);

			Assert::IsTrue(projectiles[4].activated());
			Assert::AreEqual(position.x, projectiles[4].getPosition().x);
			Assert::AreEqual(position.y, projectiles[4].getPosition().y);
			Assert::IsTrue(abs((float)FORTYFIVE_DEGREES_DIRECTION - abs(projectiles[4].getDirection().x)) < threshold);
			Assert::IsTrue(abs((float)FORTYFIVE_DEGREES_DIRECTION - abs(projectiles[4].getDirection().y)) < threshold);
		}

		/// <summary>
		/// Teste que la méthode fire ne tire rien sans munition.
		/// </summary>
		TEST_METHOD(Test_fire_06)
		{
			// Initialisation...
			Projectile projectiles[1];
			projectiles[0].setType(ProjectileType::BulletT);
			Weapon weapon(projectiles);
			weapon.setType(WeaponType::MissileLauncherT);

			sf::Vector2f position(0, 0);
			sf::Vector2f direction(0, 1);

			// Test de la méthode.
			weapon.fire(position, direction);

			// Validation des résultats
			Assert::IsFalse(projectiles[0].activated());
		}
	}; 
}