#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Imagwzit/GameObject.h"
#include "../Imagwzit/Zombie.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjetSFMLTest
{
	// La méthode de test Test_GameObject utilise la classe Zombie pour faire ses tests,
	// vu que son constructeur est protégé.
	TEST_CLASS(Test_GameObject)
	{
	public:
		/// <summary>
		/// Teste le constructeur de GameObject.
		/// </summary>
		TEST_METHOD(Test_GameObject_01)
		{
			// Initialisation...
			Zombie movable;

			// Validation des résultats.
			Assert::AreEqual(1.0f, movable.getCollisionSphere().getRayon());
			Assert::AreEqual(0.0f, movable.getCollisionSphere().getPosX());
			Assert::AreEqual(0.0f, movable.getCollisionSphere().getPosY());
		}

		/// <summary>
		/// Teste si le changement de texture initialise bien le cercle de collision.
		/// </summary>
		TEST_METHOD(Test_setTexture_01)
		{
			// Initialisation...
			Zombie movable;

			// La texture fait 54 x 54 pixels.
			sf::Texture texture;
			texture.loadFromFile("..\\ImagwzitTest\\Sprites\\Test\\Zombie.png");

			// Appel de la méthode.
			movable.setTexture(texture);

			// Validation des résultats.
			Assert::AreEqual(54.0f / 2.0f, movable.getCollisionSphere().getRayon());
			Assert::AreEqual(0.0f, movable.getCollisionSphere().getPosX());
			Assert::AreEqual(0.0f, movable.getCollisionSphere().getPosY());
		}

		/// <summary>
		/// Teste si le changement de position affecte bien le cercle de collision.
		/// </summary>
		TEST_METHOD(Test_setPosition_01)
		{
			// Initialisation...
			Zombie movable;

			// Appel de la méthode.
			movable.setPosition(1, 2);

			// Validation des résultats.
			Assert::AreEqual(1.0f, movable.getCollisionSphere().getPosX());
			Assert::AreEqual(2.0f, movable.getCollisionSphere().getPosY());
		}

		/// <summary>
		/// Teste que le calcule d'angle se fait bien pour une position à droite.
		/// </summary>
		TEST_METHOD(Test_getAngleWith_float_float_01)
		{
			// Initialisation...
			Zombie movable1;
			int posX = 1;
			int posY = 1;

			movable1.setPosition(0, 0);

			// Appel de la méthode.
			float angle = movable1.getAngleWith(posX, posY);

			// Validation des résultats.
			Assert::AreEqual(45.0f, angle);
		}

		/// <summary>
		/// Teste que le calcule d'angle se fait bien pour une position à gauche.
		/// </summary>
		TEST_METHOD(Test_getAngleWith_float_float_02)
		{
			// Initialisation...
			Zombie movable1;
			int posX = -1;
			int posY = -1;

			movable1.setPosition(0, 0);

			// Appel de la méthode.
			float angle = movable1.getAngleWith(posX, posY);

			// Validation des résultats.
			Assert::AreEqual(225.0f, angle);
		}

		/// <summary>
		/// Teste que le calcule d'angle se fait bien pour une position au même endroit.
		/// </summary>
		TEST_METHOD(Test_getAngleWith_float_float_03)
		{
			// Initialisation...
			Zombie movable1;
			int posX = 0;
			int posY = 0;

			movable1.setPosition(0, 0);

			// Appel de la méthode.
			float angle = movable1.getAngleWith(posX, posY);

			// Validation des résultats.
			Assert::AreEqual(0.0f, angle);
		}

		/// <summary>
		/// Teste que le calcule d'angle se fait bien avec un objet à droite.
		/// </summary>
		TEST_METHOD(Test_getAngleWith_GameObject_01)
		{
			// Initialisation...
			Zombie movable1;
			Zombie movable2;

			movable1.setPosition(0, 0);
			movable2.setPosition(1, 1);

			// Appel de la méthode.
			float angle = movable1.getAngleWith(movable2);

			// Validation des résultats.
			Assert::AreEqual(45.0f, angle);
		}

		/// <summary>
		/// Teste que le calcule d'angle se fait bien pour une position à gauche.
		/// </summary>
		TEST_METHOD(Test_getAngleWith_GameObject_02)
		{
			// Initialisation...
			Zombie movable1;
			Zombie movable2;

			movable1.setPosition(0, 0);
			movable2.setPosition(-1, -1);

			// Appel de la méthode.
			float angle = movable1.getAngleWith(movable2);

			// Validation des résultats.
			Assert::AreEqual(225.0f, angle);
		}

		/// <summary>
		/// Teste que le calcule d'angle se fait bien pour une position au même endroit.
		/// </summary>
		TEST_METHOD(Test_getAngleWith_GameObject_03)
		{
			// Initialisation...
			Zombie movable1;
			Zombie movable2;

			movable1.setPosition(0, 0);
			movable2.setPosition(0, 0);

			// Appel de la méthode.
			float angle = movable1.getAngleWith(movable2);

			// Validation des résultats.
			Assert::AreEqual(0.0f, angle);
		}
	};
}