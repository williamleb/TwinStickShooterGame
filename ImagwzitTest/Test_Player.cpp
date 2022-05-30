#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Imagwzit/Player.h"
#include "../Imagwzit/Weapon.h"
#include "../Imagwzit/Inputs.h"
#include "../Imagwzit/Zombie.h"
#include "../Imagwzit/AmmoPack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjetSFMLTest
{		
	TEST_CLASS(Test_Player)
	{
	public:
		/// <summary>
		/// Teste le constructeur de Player.
		/// </summary>
		TEST_METHOD(Test_Player_01)
		{
			// Initialisation...
			Projectile projectiles[1];
			Weapon weapon(projectiles);
			Inputs inputs;
			Player player(inputs, &weapon);

			// Validation des résultats
			Assert::IsTrue(PlayerState::Alive == player.getState());
		}

		/// <summary>
		/// Teste que la méthode fire active un projectile.
		/// </summary>
		TEST_METHOD(Test_fire_01)
		{
			// Initialisation...
			Projectile projectiles[1];
			projectiles[0].setType(ProjectileType::BulletT);
			Weapon weapon(projectiles);
			weapon.setType(WeaponType::HandGunT);
			weapon.addAmmo(1);
			Inputs inputs;
			Player player(inputs, &weapon);
			
			// Test de la méthode.
			player.fire();

			// Validation des résultats
			Assert::IsTrue(projectiles[0].activated());
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
			Inputs inputs;
			Player player(inputs, &weapon);

			// Test de la méthode.
			player.fire();

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
			Inputs inputs;
			Player player(inputs, &weapon);

			// Test de la méthode.
			player.fire();

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
			Inputs inputs;
			Player player(inputs, &weapon);

			// Test de la méthode.
			player.fire();
			weapon.addTime(weapon.getFireRate() + 1);
			player.fire();

			// Validation des résultats
			Assert::IsTrue(projectiles[0].activated());
			Assert::IsTrue(projectiles[1].activated());
		}

		/// <summary>
		/// Teste que la perte d'une vie du joueur se fait correctement.
		/// </summary>
		TEST_METHOD(Test_loseALife_01)
		{
			// Initialisation...
			Projectile projectiles[2];
			Weapon weapon(projectiles);
			Inputs inputs;
			Player player(inputs, &weapon);
			int nbrOfLives = player.getNbrLives();

			// Test de la méthode.
			player.loseALife();

			// Validation des résultats
			Assert::AreEqual(nbrOfLives - 1, player.getNbrLives());
			Assert::IsTrue(PlayerState::Fainting == player.getState());
		}

		/// <summary>
		/// Teste quand il n'y a pas de collision avec un joueur et un zombie.
		/// </summary>
		TEST_METHOD(Test_collidesWith_01)
		{
			// Initialisation...
			Projectile projectiles[2];
			Weapon weapon(projectiles);
			Inputs inputs;
			Player player(inputs, &weapon);
			Zombie zombie;

			sf::Texture playerT;
			playerT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Joueur.png");
			player.setTexture(playerT);
			player.setPosition(0, 0);

			sf::Texture zombieT;
			zombieT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Zombie.png");
			zombie.setTexture(zombieT);
			zombie.setPosition(1000, 1000);

			// Validation des résultats
			Assert::IsFalse(player.collidesWith(zombie));
		}

		/// <summary>
		/// Teste quand il n'y a pas de collision quand un joueur frôle un zombie.
		/// </summary>
		TEST_METHOD(Test_collidesWith_02)
		{
			// Initialisation...
			Projectile projectiles[2];
			Weapon weapon(projectiles);
			Inputs inputs;
			Player player(inputs, &weapon);
			Zombie zombie;

			sf::Texture playerT;
			playerT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Joueur.png");
			player.setTexture(playerT);
			player.setPosition(0, 0);

			sf::Texture zombieT;
			zombieT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Zombie.png");
			zombie.setTexture(zombieT);
			// 54 et 65 représentent les dimensions des sprites du joueur et du zombie.
			zombie.setPosition(54.0f / 2.0f + 65.0f / 2.0f, 0);

			// Validation des résultats
			Assert::IsFalse(player.collidesWith(zombie));
		}

		/// <summary>
		/// Teste quand il y a une collision à la limite avec un joueur et un zombie.
		/// </summary>
		TEST_METHOD(Test_collidesWith_03)
		{
			// Initialisation...
			Projectile projectiles[2];
			Weapon weapon(projectiles);
			Inputs inputs;
			Player player(inputs, &weapon);
			Zombie zombie;

			sf::Texture playerT;
			bool valide1 = playerT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Joueur.png");
			player.setTexture(playerT);
			player.setPosition(0, 0);

			sf::Texture zombieT;
			bool valide2 = zombieT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Zombie.png");
			zombie.setTexture(zombieT);
			// 54 et 65 sont les dimensions des sprites du joueur et du zombie.
			zombie.setPosition(54.0f / 2.0f + 64.0f / 2.0f, 0);

			// Validation des résultats
			Assert::IsTrue(player.collidesWith(zombie));
		}

		/// <summary>
		/// Teste quand il y a clairement une collision entre un joueur et un zombie.
		/// </summary>
		TEST_METHOD(Test_collidesWith_04)
		{
			// Initialisation...
			Projectile projectiles[2];
			Weapon weapon(projectiles);
			Inputs inputs;
			Player player(inputs, &weapon);
			Zombie zombie;

			sf::Texture playerT;
			playerT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Joueur.png");
			player.setTexture(playerT);
			player.setPosition(0, 0);

			sf::Texture zombieT;
			zombieT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Zombie.png");
			zombie.setTexture(zombieT);
			zombie.setPosition(1, 1);

			// Validation des résultats
			Assert::IsTrue(player.collidesWith(zombie));
		}

		/// <summary>
		/// Teste quand il n'y a pas de collision avec un joueur et un pack de munitions.
		/// </summary>
		TEST_METHOD(Test_collidesWith_05)
		{
			// Initialisation...
			Projectile projectiles[1];
			Weapon weapon(projectiles);
			Inputs inputs;
			Player player(inputs, &weapon);
			AmmoPack pack;

			sf::Texture playerT;
			playerT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Joueur.png");
			player.setTexture(playerT);
			player.setPosition(0, 0);

			sf::Texture packT;
			packT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\BulletLogo.png");
			pack.setTexture(packT);
			pack.setPosition(1000, 1000);

			// Validation des résultats
			Assert::IsFalse(player.collidesWith(pack));
		}

		/// <summary>
		/// Teste quand il n'y a pas de collision quand un joueur frôle un pack de munitions.
		/// </summary>
		TEST_METHOD(Test_collidesWith_06)
		{
			// Initialisation...
			Projectile projectiles[2];
			Weapon weapon(projectiles);
			Inputs inputs;
			Player player(inputs, &weapon);
			AmmoPack pack;

			sf::Texture playerT;
			playerT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Joueur.png");
			player.setTexture(playerT);
			player.setPosition(0, 0);

			sf::Texture packT;
			packT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\BulletLogo.png");
			pack.setTexture(packT);
			// 50 et 65 représentent les dimensions des sprites du joueur et du pack de munitions.
			pack.setPosition(50.0f / 2.0f + 65.0f / 2.0f, 0);

			// Validation des résultats
			Assert::IsFalse(player.collidesWith(pack));
		}

		/// <summary>
		/// Teste quand il y a une collision à la limite avec un joueur et un pack de munitions.
		/// </summary>
		TEST_METHOD(Test_collidesWith_07)
		{
			// Initialisation...
			Projectile projectiles[2];
			Weapon weapon(projectiles);
			Inputs inputs;
			Player player(inputs, &weapon);
			AmmoPack pack;

			sf::Texture playerT;
			playerT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Joueur.png");
			player.setTexture(playerT);
			player.setPosition(0, 0);

			sf::Texture packT;
			packT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\BulletLogo.png");
			pack.setTexture(packT);
			// 50 et 65 sont les dimensions des sprites du joueur et du pack de munitions.
			pack.setPosition(50.0f / 2.0f + 64.0f / 2.0f, 0);

			// Validation des résultats
			Assert::IsTrue(player.collidesWith(pack));
		}

		/// <summary>
		/// Teste quand il y a clairement une collision entre un joueur et un zombie.
		/// </summary>
		TEST_METHOD(Test_collidesWith_08)
		{
			// Initialisation...
			Projectile projectiles[2];
			Weapon weapon(projectiles);
			Inputs inputs;
			Player player(inputs, &weapon);
			AmmoPack pack;

			sf::Texture playerT;
			playerT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Joueur.png");
			player.setTexture(playerT);
			player.setPosition(0, 0);

			sf::Texture packT;
			packT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\BulletLogo.png");
			pack.setTexture(packT);
			pack.setPosition(1, 1);

			// Validation des résultats
			Assert::IsTrue(player.collidesWith(pack));
		}
	};
}