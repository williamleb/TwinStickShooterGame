/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#pragma once

/// <summary>
/// Le ComboManager trace les combos. On peut ajouter des valeurs au combo,
/// mais, après un certain temps sans ajout, la valeur de combo se réinitialise à 0.
/// </summary>
class ComboManager
{
	static const unsigned int DEFAULT_DEACTIVATION_TIME = 500;

	bool comboActivated;
	unsigned int comboValue;
	unsigned int millisecondsSinceLastCombo;
	
public:	
	/// <summary>
	/// Crée un nouveau <see cref="ComboManager"/>.
	/// </summary>
	ComboManager();
	
	/// <summary>
	/// Ajoute des millisecondes pour savoir quand le combo doit se désactiver.
	/// </summary>
	/// <param name="milliseconds">Le nombre de millisecondes à ajouter.</param>
	void addMilliseconds(const unsigned int milliseconds);
		
	/// <summary>
	/// Ajoute un à la valeur du combo.
	/// </summary>
	void addCombo();

	/// <summary>
	/// Retourne la valeur du combo.
	/// </summary>
	/// <returns>La valeur du combo.</returns>
	int getComboValue() const;
};