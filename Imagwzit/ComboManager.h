/*

Fichier cr�� par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vid�o III.

*/
#pragma once

/// <summary>
/// Le ComboManager trace les combos. On peut ajouter des valeurs au combo,
/// mais, apr�s un certain temps sans ajout, la valeur de combo se r�initialise � 0.
/// </summary>
class ComboManager
{
	static const unsigned int DEFAULT_DEACTIVATION_TIME = 500;

	bool comboActivated;
	unsigned int comboValue;
	unsigned int millisecondsSinceLastCombo;
	
public:	
	/// <summary>
	/// Cr�e un nouveau <see cref="ComboManager"/>.
	/// </summary>
	ComboManager();
	
	/// <summary>
	/// Ajoute des millisecondes pour savoir quand le combo doit se d�sactiver.
	/// </summary>
	/// <param name="milliseconds">Le nombre de millisecondes � ajouter.</param>
	void addMilliseconds(const unsigned int milliseconds);
		
	/// <summary>
	/// Ajoute un � la valeur du combo.
	/// </summary>
	void addCombo();

	/// <summary>
	/// Retourne la valeur du combo.
	/// </summary>
	/// <returns>La valeur du combo.</returns>
	int getComboValue() const;
};