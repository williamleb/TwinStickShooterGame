/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#include "ComboManager.h"

ComboManager::ComboManager()
{
	comboActivated = false;
	comboValue = 0;
	millisecondsSinceLastCombo = 0;
}

void ComboManager::addMilliseconds(const unsigned int milliseconds)
{
	if (comboActivated)
	{
		millisecondsSinceLastCombo += milliseconds;

		// Si le temps depuis le dernier combo est plus grand que le temps
		// qu'on possède pour faire un combo, on remet le combo à 0.
		if (millisecondsSinceLastCombo > DEFAULT_DEACTIVATION_TIME)
		{
			comboActivated = false;
			comboValue = 0;
		}
	}
}

void ComboManager::addCombo()
{
	comboActivated = true;
	comboValue++;
	// On redémarre le timer, parce qu'on a fait un combo.
	millisecondsSinceLastCombo = 0;
}

int ComboManager::getComboValue() const
{
	return comboValue; 
}