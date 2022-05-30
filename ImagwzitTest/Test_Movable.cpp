#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Imagwzit/Movable.h"
#include "../Imagwzit/Zombie.h"

#define Bottom_Left_Direction -0.70710678118654752440084436210485
#define threshold 0.01

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjetSFMLTest
{
	// La méthode de test Test_Movable utilise un Zombie pour faire ses tests,
	// vue que son constructeur est protégé.
	TEST_CLASS(Test_Movable)
	{
	public:
		/// <summary>
		/// Teste le constructeur de Movable.
		/// </summary>
		TEST_METHOD(Test_Movable_01)
		{
			// Initialisation...
			Zombie movable;

			// Validation des résultats.
			Assert::AreEqual(270.0f, movable.getAngle());
			Assert::IsTrue(abs(0.0f - movable.getDirection().x) < threshold);
			Assert::IsTrue(abs(-1.0f - movable.getDirection().y) < threshold);
		}

		/// <summary>
		/// Teste la conversion d'angle en direction pour un angle vers la droite.
		/// </summary>
		TEST_METHOD(Test_convertAngleToDirection_01)
		{
			// Appel de la métode.
			sf::Vector2f direction = Movable::convertAngleToDirection(0);

			// Validation des résultats.
			Assert::IsTrue(abs(1.0f - direction.x) < threshold);
			Assert::IsTrue(abs(0.0f - direction.y) < threshold);
		}

		/// <summary>
		/// Teste la conversion d'angle en direction pour un angle en bas à gauche.
		/// </summary>
		TEST_METHOD(Test_convertAngleToDirection_02)
		{
			// Appel de la métode.
			sf::Vector2f direction = Movable::convertAngleToDirection(225);

			// Validation des résultats.
			Assert::IsTrue(abs((float)Bottom_Left_Direction - direction.x) < threshold);
			Assert::IsTrue(abs((float)Bottom_Left_Direction- direction.y) < threshold);

		}

		/// <summary>
		/// Teste la conversion d'angle en direction pour un angle plus grand que 360 degrés.
		/// </summary>
		TEST_METHOD(Test_convertAngleToDirection_03)
		{
			// Appel de la métode.
			sf::Vector2f direction = Movable::convertAngleToDirection(450);

			// Validation des résultats.
			Assert::IsTrue(abs(0.0f - direction.x) < threshold);
			Assert::IsTrue(abs(1.0f - direction.y) < threshold);
		}

		/// <summary>
		/// Teste la conversion de direction en angle pour une direction vers la droite.
		/// </summary>
		TEST_METHOD(Test_convertDirectionToAngle_01)
		{
			// Appel de la métode.
			sf::Vector2f direction(1, 0);
			float angle = Movable::convertDirectionToAngle(direction);

			// Validation des résultats.
			Assert::IsTrue(abs(0.0f - angle) < threshold);
		}

		/// <summary>
		/// Teste la conversion de direction en angle pour une direction en bas à gauche.
		/// </summary>
		TEST_METHOD(Test_convertDirectionToAngle_02)
		{
			// Appel de la métode.
			sf::Vector2f direction(Bottom_Left_Direction, Bottom_Left_Direction);
			float angle = Movable::convertDirectionToAngle(direction);

			// Validation des résultats.
			Assert::IsTrue(abs(225.0f - angle) < threshold);
		}

		/// <summary>
		/// Teste la conversion de direction en angle pour une direction nulle.
		/// </summary>
		TEST_METHOD(Test_convertDirectionToAngle_03)
		{
			// Appel de la métode.
			sf::Vector2f direction(0, 0);
			float angle = Movable::convertDirectionToAngle(direction);

			// Validation des résultats.
			Assert::IsTrue(abs(0.0f - angle) < threshold);
		}

		/// <summary>
		/// Teste la définition d'un angle.
		/// </summary>
		TEST_METHOD(Test_setAngle_01)
		{
			// Initialisation...
			Zombie movable;

			// Appel de la métode.
			movable.setAngle(35);
			sf::Vector2f direction = Movable::convertAngleToDirection(35);

			// Validation des résultats.
			Assert::IsTrue(abs(movable.getAngle() - movable.getRotation()) < threshold);
			Assert::IsTrue(abs(direction.x - movable.getDirection().x) < threshold);
			Assert::IsTrue(abs(direction.y - movable.getDirection().y) < threshold);
		}

		/// <summary>
		/// Teste la définition d'un angle sans changer l'angle du sprite.
		/// </summary>
		TEST_METHOD(Test_setAngle_02)
		{
			// Initialisation...
			Zombie movable;

			// Appel de la métode.
			movable.setAngle(35.24f, false);
			sf::Vector2f direction = Movable::convertAngleToDirection(35.24f);

			// Validation des résultats.
			Assert::AreNotEqual(movable.getAngle(), movable.getRotation());
			Assert::IsTrue(abs(direction.x - movable.getDirection().x) < threshold);
			Assert::IsTrue(abs(direction.y - movable.getDirection().y) < threshold);
		}

		/// <summary>
		/// Teste la définition d'une direction.
		/// </summary>
		TEST_METHOD(Test_setDirection_01)
		{
			// Initialisation...
			Zombie movable;

			// Appel de la métode.
			sf::Vector2f direction(-1.0f, 0.0f);
			movable.setDirection(direction);
			float angle = Movable::convertDirectionToAngle(direction);

			// Validation des résultats.
			Assert::IsTrue(abs(angle - movable.getRotation()) < threshold);
			Assert::IsTrue(abs(angle - movable.getAngle()) < threshold);
		}

		/// <summary>
		/// Teste la définition d'un angle sans changer l'angle du sprite.
		/// </summary>
		TEST_METHOD(Test_setDirection_02)
		{
			// Initialisation...
			Zombie movable;

			// Appel de la métode.
			sf::Vector2f direction(Bottom_Left_Direction, Bottom_Left_Direction);
			movable.setDirection(direction, false);
			float angle = Movable::convertDirectionToAngle(direction);

			// Validation des résultats.
			Assert::AreNotEqual(angle, movable.getRotation());
			Assert::IsTrue(abs(angle - movable.getAngle()) < threshold);
		}
	};
}