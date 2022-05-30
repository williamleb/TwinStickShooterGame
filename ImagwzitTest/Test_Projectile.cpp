#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Imagwzit/Projectile.h"
#include "../Imagwzit/Zombie.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjetSFMLTest
{
	TEST_CLASS(Test_Projectile)
	{
	public:
		/// <summary>
		/// Teste quand il n'y a pas de collision avec un projectile et un zombie.
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
			Assert::IsFalse(projectile.collidesWith(zombie));
		}

		/// <summary>
		/// Teste quand il n'y a pas de collision quand un projectile et un zombie.
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
			Assert::IsFalse(projectile.collidesWith(zombie));
		}

		/// <summary>
		/// Teste quand il y a une collision à la limite avec un projectile et un zombie.
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
			Assert::IsTrue(projectile.collidesWith(zombie));
		}

		/// <summary>
		/// Teste quand il y a clairement une collision entre un projectile et un zombie.
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
			Assert::IsTrue(projectile.collidesWith(zombie));
		}
	};
}