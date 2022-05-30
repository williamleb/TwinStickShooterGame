#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Imagwzit/ComboManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjetSFMLTest
{
	TEST_CLASS(Test_ComboManager)
	{
	public:
		/// <summary>
		/// Teste que la valeur de combo est correcte au début.
		/// </summary>
		TEST_METHOD(Test_getComboValue_01)
		{
			// Initialisation...
			ComboManager combo;

			// Validation des résultats.
			Assert::AreEqual(0, combo.getComboValue());
		}

		/// <summary>
		/// Teste que la valeur de combo est correcte après y avoir ajouté 1.
		/// </summary>
		TEST_METHOD(Test_getComboValue_02)
		{
			// Initialisation...
			ComboManager combo;

			combo.addCombo();

			// Validation des résultats.
			Assert::AreEqual(1, combo.getComboValue());
		}

		/// <summary>
		/// Teste que la valeur de combo se rénitialise après un certain temps.
		/// </summary>
		TEST_METHOD(Test_getComboValue_03)
		{
			// Initialisation...
			ComboManager combo;

			combo.addCombo();
			combo.addMilliseconds(99999);

			// Validation des résultats.
			Assert::AreEqual(0, combo.getComboValue());
		}

		/// <summary>
		/// Teste que la valeur de combo s'additionne.
		/// </summary>
		TEST_METHOD(Test_getComboValue_04)
		{
			// Initialisation...
			ComboManager combo;

			combo.addCombo();
			combo.addCombo();
			combo.addCombo();

			// Validation des résultats.
			Assert::AreEqual(3, combo.getComboValue());
		}
	};
}