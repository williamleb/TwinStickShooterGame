/*

Fichier en grande partie tiré du projet ExempleSFML2.1 du cours
Programmation de jeux vidéo III.

Il a été modifié par William Lebel (1638175) pour ajouter un
deuxième axe et pour certains commentaire.

*/
#pragma once

/// <summary>
/// Représente l'état des inputs du joueur.
/// </summary>
class Inputs
{
public:	
	/// <summary>
	/// Crée un nouvelle feuille d'état d'<see cref="Inputs"/>.
	/// </summary>
	Inputs();	

	/// <summary>
	/// Cette méthode permet d'éliminier le "bruit" d'un joy analogique.  Ce dernier n'est jamais parfaitement à 0/0, surtout quand le matériel vieillit.
	/// Si le mouvement est en deça d'un certain mimimimum en valeur absolue, alors on passe 0 à la commande effective.
	/// </summary>
	/// <param name="axeXL">Le signal en X venant du gamepad (joystick gauche).</param>
	/// <param name="AxeYL">Le signal en Y venant du gamepad (jostick gauche).</param>
	void setAxesL(const float axeX, const float AxeY);
		

	/// <summary>
	/// Cette méthode permet d'éliminier le "bruit" d'un joy analogique.  Ce dernier n'est jamais parfaitement à 0/0, surtout quand le matériel vieillit.
	/// Si le mouvement est en deça d'un certain mimimimum en valeur absolue, alors on passe 0 à la commande effective.
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
	/// Active ou désactives l'état des boutons d'une manette.
	/// </summary>
	/// <param name="button">Le numéro du bouttn.</param>
	/// <param name="pressed">Indique si le bouton est pesé ou non.</param>
	void setButtons(const int button, const bool pressed);
	
	/// <summary>
	/// Active ou désactive l'état "haut".
	/// </summary>
	/// <param name="pressed">Indique si l'état est activé ou désactivé.</param>
	void setUp(const bool pressed);

	/// <summary>
	/// Active ou désactive l'état "bas".
	/// </summary>
	/// <param name="pressed">Indique si l'état est activé ou désactivé.</param>
	void setDown(const bool pressed);

	/// <summary>
	/// Active ou désactive l'état "gauche".
	/// </summary>
	/// <param name="pressed">Indique si l'état est activé ou désactivé.</param>
	void setLeft(const bool pressed);

	/// <summary>
	/// Active ou désactive l'état "droite".
	/// </summary>
	/// <param name="pressed">Indique si l'état est activé ou désactivé.</param>
	void setRight(const bool pressed);
		
	/// <summary>
	/// Indique si l'état "haut" est activé ou non.
	/// </summary>
	/// <returns>True si l'état est activé; false sinon.</returns>
	bool getUp() const;

	/// <summary>
	/// Indique si l'état "bas" est activé ou non.
	/// </summary>
	/// <returns>True si l'état est activé; false sinon.</returns>
	bool getDown() const;

	/// <summary>
	/// Indique si l'état "gauche" est activé ou non.
	/// </summary>
	/// <returns>True si l'état est activé; false sinon.</returns>
	bool getLeft() const;

	/// <summary>
	/// Indique si l'état "droite" est activé ou non.
	/// </summary>
	/// <returns>True si l'état est activé; false sinon.</returns>
	bool getRight() const;
	
	/// <summary>
	/// Indique si un certain bouton est activé.
	/// </summary>
	/// <param name="button">Le numéro du bouton à vérifier.</param>
	/// <returns>True si le bouton est activé, false sinon.</returns>
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
	/// Active ou désactive le clic de la souris.
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

