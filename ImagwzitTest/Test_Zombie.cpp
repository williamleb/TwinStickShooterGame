#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Imagwzit/Player.h"
#include "../Imagwzit/Weapon.h"
#include "../Imagwzit/Inputs.h"
#include "../Imagwzit/Zombie.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjetSFMLTest
{
	TEST_CLASS(Test_Zombie)
	{
	public:
		/// <summary>
		/// Teste le constructeur de Zombie.
		/// </summary>
		TEST_METHOD(Test_Zombie_01)
		{
			// Initialisation...
			Zombie zombie;

			// Validation des résultats
			Assert::AreEqual(0.0f, zombie.getTarget().x);
			Assert::AreEqual(0.0f, zombie.getTarget().y);
		}

		/// <summary>
		/// Teste la définition de la nouvelle cible du zombie à droite.
		/// </summary>
		TEST_METHOD(Test_setTarget_Vector2f_01)
		{
			// Initialisation...
			Zombie zombie;
			zombie.setPosition(0, 0);

			// Test de la méthode.
			sf::Vector2f target(1, 0);
			zombie.setTarget(target);

			// Validation des résultats
			Assert::AreEqual(0.0f, zombie.getAngle());
		}

		/// <summary>
		/// Teste la définition de la nouvelle cible du zombie à droite 
		/// quand le zombie doit s'éloigner.
		/// </summary>
		TEST_METHOD(Test_setTarget_Vector2f_02)
		{
			// Initialisation...
			Zombie zombie;
			zombie.setPosition(0, 0);

			// Test de la méthode.
			sf::Vector2f target(1, 0);
			zombie.setTarget(target, false);

			// Validation des résultats
			Assert::AreEqual(180.0f, zombie.getAngle());
		}

		/// <summary>
		/// Teste la définition de la nouvelle cible du zombie à gauche.
		/// </summary>
		TEST_METHOD(Test_setTarget_Vector2f_03)
		{
			// Initialisation...
			Zombie zombie;
			zombie.setPosition(0, 0);

			// Test de la méthode.
			sf::Vector2f target(-1, 0);
			zombie.setTarget(target);

			// Validation des résultats
			Assert::AreEqual(180.0f, zombie.getAngle());
		}

		/// <summary>
		/// Teste la définition de la nouvelle cible du zombie à gauche
		/// quand le zombie doit s'éloigner.
		/// </summary>
		TEST_METHOD(Test_setTarget_Vector2f_04)
		{
			// Initialisation...
			Zombie zombie;
			zombie.setPosition(0, 0);

			// Test de la méthode.
			sf::Vector2f target(-1, 0);
			zombie.setTarget(target, false);

			// Validation des résultats
			Assert::AreEqual(360.0f, zombie.getAngle());
		}

		/// <summary>
		/// Teste la définition de la nouvelle cible joueur du zombie à droite.
		/// </summary>
		TEST_METHOD(Test_setTarget_Player_01)
		{
			// Initialisation...
			Projectile projectiles[1];
			Weapon weapon(projectiles);
			Inputs inputs;
			Player player(inputs, &weapon);
			player.setPosition(1, 0);

			Zombie zombie;
			zombie.setPosition(0, 0);

			// Test de la méthode.
			zombie.setTarget(player);

			// Validation des résultats
			Assert::AreEqual(0.0f, zombie.getAngle());
			Assert::AreEqual(1.0f, zombie.getTarget().x);
			Assert::AreEqual(0.0f, zombie.getTarget().y);
		}

		/// <summary>
		/// Teste la définition de la nouvelle cible joueur du zombie à droite 
		/// quand le zombie doit s'éloigner.
		/// </summary>
		TEST_METHOD(Test_setTarget_Player_02)
		{
			// Initialisation...
			Projectile projectiles[1];
			Weapon weapon(projectiles);
			Inputs inputs;
			Player player(inputs, &weapon);
			player.setPosition(1, 0);

			Zombie zombie;
			zombie.setPosition(0, 0);

			// Test de la méthode.
			zombie.setTarget(player, false);

			// Validation des résultats
			Assert::AreEqual(180.0f, zombie.getAngle());
			Assert::AreEqual(1.0f, zombie.getTarget().x);
			Assert::AreEqual(0.0f, zombie.getTarget().y);
		}

		/// <summary>
		/// Teste la définition de la nouvelle cible joueur du zombie à gauche.
		/// </summary>
		TEST_METHOD(Test_setTarget_Player_03)
		{
			// Initialisation...
			Projectile projectiles[1];
			Weapon weapon(projectiles);
			Inputs inputs;
			Player player(inputs, &weapon);
			player.setPosition(-1, 0);

			Zombie zombie;
			zombie.setPosition(0, 0);

			// Test de la méthode.
			zombie.setTarget(player);

			// Validation des résultats
			Assert::AreEqual(180.0f, zombie.getAngle());
			Assert::AreEqual(-1.0f, zombie.getTarget().x);
			Assert::AreEqual(0.0f, zombie.getTarget().y);
		}

		/// <summary>
		/// Teste la définition de la nouvelle cible joueur du zombie à gauche
		/// quand le zombie doit s'éloigner.
		/// </summary>
		TEST_METHOD(Test_setTarget_Player_04)
		{
			// Initialisation...
			Projectile projectiles[1];
			Weapon weapon(projectiles);
			Inputs inputs;
			Player player(inputs, &weapon);
			player.setPosition(-1, 0);

			Zombie zombie;
			zombie.setPosition(0, 0);

			// Test de la méthode.
			zombie.setTarget(player, false);

			// Validation des résultats
			Assert::AreEqual(360.0f, zombie.getAngle());
			Assert::AreEqual(-1.0f, zombie.getTarget().x);
			Assert::AreEqual(0.0f, zombie.getTarget().y);
		}

		/// <summary>
		/// Teste quand il n'y a pas de collision avec un zombie et un joueur.
		/// </summary>
		TEST_METHOD(Test_collidesWith_01)
		{
			// Initialisation...
			Projectile projectiles[1];
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
			Assert::IsFalse(zombie.collidesWith(player));
		}

		/// <summary>
		/// Teste quand il n'y a pas de collision quand un zombie et un joueur.
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
			Assert::IsFalse(zombie.collidesWith(player));
		}

		/// <summary>
		/// Teste quand il y a une collision à la limite avec un zombie et un joueur.
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
			playerT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Joueur.png");
			player.setTexture(playerT);
			player.setPosition(0, 0);

			sf::Texture zombieT;
			zombieT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Zombie.png");
			zombie.setTexture(zombieT);
			// 54 et 65 sont les dimensions des sprites du joueur et du zombie.
			zombie.setPosition(54.0f / 2.0f + 64.0f / 2.0f, 0);

			// Validation des résultats
			Assert::IsTrue(zombie.collidesWith(player));
		}

		/// <summary>
		/// Teste quand il y a clairement une collision entre un zombie et un joueur.
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
			Assert::IsTrue(zombie.collidesWith(player));
		}

		/// <summary>
		/// Teste quand il n'y a pas de collision avec un zombie et un projectile.
		/// </summary>
		TEST_METHOD(Test_collidesWith_05)
		{
			// Initialisation...
			Projectile projectile;
			Zombie zombie;

			sf::Texture projectileT;
			projectileT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Bullet.png");
			projectile.setTexture(projectileT);
			projectile.setPosition(0, 0);

			sf::Texture zombieT;
			zombieT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Zombie.png");
			zombie.setTexture(zombieT);
			zombie.setPosition(1000, 1000);

			// Validation des résultats
			Assert::IsFalse(zombie.collidesWith(projectile));
		}

		/// <summary>
		/// Teste quand il n'y a pas de collision quand un zombie et un projectile.
		/// </summary>
		TEST_METHOD(Test_collidesWith_06)
		{
			// Initialisation...
			Projectile projectile;
			Zombie zombie;

			sf::Texture projectileT;
			projectileT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Bullet.png");
			projectile.setTexture(projectileT);
			projectile.setPosition(0, 0);

			sf::Texture zombieT;
			zombieT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Zombie.png");
			zombie.setTexture(zombieT);
			// 54 et 8 représentent les dimensions des sprites du projectile et du zombie.
			zombie.setPosition(54.0f / 2.0f + 8.0f / 2.0f, 0);

			// Validation des résultats
			Assert::IsFalse(zombie.collidesWith(projectile));
		}

		/// <summary>
		/// Teste quand il y a une collision à la limite avec un zombie et un projectile.
		/// </summary>
		TEST_METHOD(Test_collidesWith_07)
		{
			// Initialisation...
			Projectile projectile;
			Zombie zombie;

			sf::Texture projectileT;
			projectileT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Bullet.png");
			projectile.setTexture(projectileT);
			projectile.setPosition(0, 0);

			sf::Texture zombieT;
			zombieT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Zombie.png");
			zombie.setTexture(zombieT);
			// 54 et 8 sont les dimensions des sprites du joueur et du projectile.
			zombie.setPosition(54.0f / 2.0f + 7.0f / 2.0f, 0);

			// Validation des résultats
			Assert::IsTrue(zombie.collidesWith(projectile));
		}

		/// <summary>
		/// Teste quand il y a clairement une collision entre un zombie et un projectile.
		/// </summary>
		TEST_METHOD(Test_collidesWith_08)
		{
			// Initialisation...
			Projectile projectile;
			Zombie zombie;

			sf::Texture projectileT;
			projectileT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Bullet.png");
			projectile.setTexture(projectileT);
			projectile.setPosition(0, 0);

			sf::Texture zombieT;
			zombieT.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Zombie.png");
			zombie.setTexture(zombieT);
			zombie.setPosition(1, 1);

			// Validation des résultats
			Assert::IsTrue(zombie.collidesWith(projectile));
		}
	};
}