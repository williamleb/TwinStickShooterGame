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
		/// Teste que la valeur de combo est correcte au d�but.
		/// </summary>
		TEST_METHOD(Test_getComboValue_01)
		{
			// Initialisation...
			ComboManager combo;

			// Validation des r�sultats.
			Assert::AreEqual(0, combo.getComboValue());
		}

		/// <summary>
		/// Teste que la valeur de combo est correcte apr�s y avoir ajout� 1.
		/// </summary>
		TEST_METHOD(Test_getComboValue_02)
		{
			// Initialisation...
			ComboManager combo;

			combo.addCombo();

			// Validation des r�sultats.
			Assert::AreEqual(1, combo.getComboValue());
		}

		/// <summary>
		/// Teste que la valeur de combo se r�nitialise apr�s un certain temps.
		/// </summary>
		TEST_METHOD(Test_getComboValue_03)
		{
			// Initialisation...
			ComboManager combo;

			combo.addCombo();
			combo.addMilliseconds(99999);

			// Validation des r�sultats.
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

			// Validation des r�sultats.
			Assert::AreEqual(3, combo.getComboValue());
		}
	};
}