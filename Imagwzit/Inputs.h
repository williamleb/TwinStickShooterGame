/*

Fichier en grande partie tir� du projet ExempleSFML2.1 du cours
Programmation de jeux vid�o III.

Il a �t� modifi� par William Lebel (1638175) pour ajouter un
deuxi�me axe et pour certains commentaire.

*/
#pragma once

/// <summary>
/// Repr�sente l'�tat des inputs du joueur.
/// </summary>
class Inputs
{
public:	
	/// <summary>
	/// Cr�e un nouvelle feuille d'�tat d'<see cref="Inputs"/>.
	/// </summary>
	Inputs();	

	/// <summary>
	/// Cette m�thode permet d'�liminier le "bruit" d'un joy analogique.  Ce dernier n'est jamais parfaitement � 0/0, surtout quand le mat�riel vieillit.
	/// Si le mouvement est en de�a d'un certain mimimimum en valeur absolue, alors on passe 0 � la commande effective.
	/// </summary>
	/// <param name="axeXL">Le signal en X venant du gamepad (joystick gauche).</param>
	/// <param name="AxeYL">Le signal en Y venant du gamepad (jostick gauche).</param>
	void setAxesL(const float axeX, const float AxeY);
		

	/// <summary>
	/// Cette m�thode permet d'�liminier le "bruit" d'un joy analogique.  Ce dernier n'est jamais parfaitement � 0/0, surtout quand le mat�riel vieillit.
	/// Si le mouvement est en de�a d'un certain mimimimum en valeur absolue, alors on passe 0 � la commande effective.
	/// </summary>
	/// <param name="axeXR">Le signal en X venant du gamepad (joystick droit).</param>
	/// <param name="AxeYR">Le signal en Y venant du gamepad (jostick droit).</param>
	void setAxesR(const float axeX, const float AxeY);
	
	/// <summary>
	/// Sauvegarde la position de la souris.
	/// </summary>
	/// <param name="axeX">La position de la souris en X.</param>
	/// <param name="AxeY">La position de la souris en Y.</param>
	void setMouse(const float axeX, const float axeY);
	
	/// <summary>
	/// Change le seuil de mouvement des joysticks.
	/// </summary>
	/// <param name="noiseLevel">Le seuil de movement.</param>
	void setNoiseLevel(const float noiseLevel);
	
	/// <summary>
	/// Efface la trace des inputs.
	/// </summary>
	void clear();
	
	/// <summary>
	/// Active ou d�sactives l'�tat des boutons d'une manette.
	/// </summary>
	/// <param name="button">Le num�ro du bouttn.</param>
	/// <param name="pressed">Indique si le bouton est pes� ou non.</param>
	void setButtons(const int button, const bool pressed);
	
	/// <summary>
	/// Active ou d�sactive l'�tat "haut".
	/// </summary>
	/// <param name="pressed">Indique si l'�tat est activ� ou d�sactiv�.</param>
	void setUp(const bool pressed);

	/// <summary>
	/// Active ou d�sactive l'�tat "bas".
	/// </summary>
	/// <param name="pressed">Indique si l'�tat est activ� ou d�sactiv�.</param>
	void setDown(const bool pressed);

	/// <summary>
	/// Active ou d�sactive l'�tat "gauche".
	/// </summary>
	/// <param name="pressed">Indique si l'�tat est activ� ou d�sactiv�.</param>
	void setLeft(const bool pressed);

	/// <summary>
	/// Active ou d�sactive l'�tat "droite".
	/// </summary>
	/// <param name="pressed">Indique si l'�tat est activ� ou d�sactiv�.</param>
	void setRight(const bool pressed);
		
	/// <summary>
	/// Indique si l'�tat "haut" est activ� ou non.
	/// </summary>
	/// <returns>True si l'�tat est activ�; false sinon.</returns>
	bool getUp() const;

	/// <summary>
	/// Indique si l'�tat "bas" est activ� ou non.
	/// </summary>
	/// <returns>True si l'�tat est activ�; false sinon.</returns>
	bool getDown() const;

	/// <summary>
	/// Indique si l'�tat "gauche" est activ� ou non.
	/// </summary>
	/// <returns>True si l'�tat est activ�; false sinon.</returns>
	bool getLeft() const;

	/// <summary>
	/// Indique si l'�tat "droite" est activ� ou non.
	/// </summary>
	/// <returns>True si l'�tat est activ�; false sinon.</returns>
	bool getRight() const;
	
	/// <summary>
	/// Indique si un certain bouton est activ�.
	/// </summary>
	/// <param name="button">Le num�ro du bouton � v�rifier.</param>
	/// <returns>True si le bouton est activ�, false sinon.</returns>
	bool getButtons(const int button) const;
	
	/// <summary>
	/// Retourne la valeur de l'axe X (joystick gauche).
	/// </summary>
	/// <returns>La valeur de l'axe X (joystick gauche)</returns>
	float getAxeXL() const;

	/// <summary>
	/// Retourne la valeur de l'axe Y (joystick gauche).
	/// </summary>
	/// <returns>La valeur de l'axe Y (joystick gauche)</returns>
	float getAxeYL() const;

	/// <summary>
	/// Retourne la valeur de l'axe X (joystick droit).
	/// </summary>
	/// <returns>La valeur de l'axe X (joystick droit)</returns>
	float getAxeXR() const;

	/// <summary>
	/// Retourne la valeur de l'axe Y (joystick droit).
	/// </summary>
	/// <returns>La valeur de l'axe Y (joystick droit)</returns>
	float getAxeYR() const;
	
	/// <summary>
	/// Retourne la position en X de la souris.
	/// </summary>
	/// <returns>La position en X de la souris.</returns>
	float getMouseX() const;

	/// <summary>
	/// Retourne la position en Y de la souris.
	/// </summary>
	/// <returns>La position en Y de la souris.</returns>
	float getMouseY() const;
	
	/// <summary>
	/// Active ou d�sactive le clic de la souris.
	/// </summary>
	/// <param name="pressed">Indique s'il y a un clic ou non.</param>
	void setMouseClick(const bool pressed);
	
	/// <summary>
	/// Indique si il y a un clic de souris.
	/// </summary>
	/// <returns>True s'il y a un clic; false sinon.</returns>
	bool getMouseClick() const;


private:
	float noise;
	float axeXL;
	float axeYL;
	float axeXR;
	float axeYR;

	bool buttons[8];
	bool directionalKeys[4];

	float mouseX;
	float mouseY;
	bool mouseClick;
};

