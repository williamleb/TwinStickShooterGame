/*

Fichier cr�� en partie par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vid�o III.

L'autre partie a �t� fourni dans le cadre du travail partique 1.

*/
#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Inputs.h"
#include "Player.h"
#include "Zombie.h"
#include "AmmoPack.h"
#include "Weapon.h"
#include "ComboManager.h"
#include "ScoreText.h"
#include "GameState.h"
#include "StartMenu.h"
#include "EndMenu.h"

using namespace sf;

/// <summary>
/// Repr�sente un jeu.
/// </summary>
class Game
{
public:
	Game();
	int run();

	static const int NBR_OF_LOADED_ZOMBIES = 50;
	static const int NBR_OF_LOADED_PROJECTILES = 75;
	static const int NBR_OF_LOADED_AMMOPACKS = 15;

	static const int LARGEUR_ECRAN = 1280;
	static const int HAUTEUR_ECRAN = 720;

	static const int LARGEUR_MONDE = 3384;
	static const int HAUTEUR_MONDE = 1656;

	static const int CENTRE_MONDE_X = LARGEUR_MONDE / 2;
	static const int CENTRE_MONDE_Y = HAUTEUR_MONDE / 2;

private:

	static const int FRAME_RATE = 60;

	// La distance minimale du joueur qu'un zombie peut spawner.
	static const int MIN_DIST_FROM_PLAYER_TO_SPAWN = 250;

	// Le score que le joueur doit atteindre pour avoir une nouvelle vie.
	static const int SCORE_FOR_NEW_LIFE = 50'000;

	// Si le joueur change d'arme avec une manette, il ne peut pas rechanger tout de suite.
	// Cette constante sert � savoir � quelle fr�quence le joueur peut changer d'arme avec
	// la manette.
	static const int NBR_MILLISECONDS_BEFORE_CONTROLLER_WEAPON_CHANGE = 250;

	// Puisque la vue utilise des positions centrales, les limites d'affichage
	// sont les positions centrales des cadres limites.
	static const int LIMITE_VUE_MIN_X = LARGEUR_ECRAN / 2;
	static const int LIMITE_VUE_MIN_Y = HAUTEUR_ECRAN / 2;
	static const int LIMITE_VUE_MAX_X = LARGEUR_MONDE - LIMITE_VUE_MIN_X;
	static const int LIMITE_VUE_MAX_Y = HAUTEUR_MONDE - LIMITE_VUE_MIN_Y;

	StartMenu startMenu;
	EndMenu endMenu;

	// Textures
	Texture terrainT;
	Texture joueurT;
	Texture zombieT[3];
	Texture bulletT;
	Texture flameT;
	Texture missileT;
	Texture scatterT;
	Texture bulletPackT;
	Texture flamePackT;
	Texture missilePackT;
	Texture scatterPackT;
	Texture handGunSelectT;
	Texture submachineGunSelectT;
	Texture flamethrowerSelectT;
	Texture scatterGunSelectT;
	Texture missileLauncherSelectT;
	Texture controllerHelpT;
	Texture mouseAndKeyboardHelpT;
	
	// �l�ments de jeu.
	Sprite terrain;
	Player player;
	Projectile projectiles[NBR_OF_LOADED_PROJECTILES];
	Zombie zombies[NBR_OF_LOADED_ZOMBIES];
	AmmoPack ammoPacks[NBR_OF_LOADED_AMMOPACKS];
	
	// Les diff�rentes armes.
	Weapon handGun;
	Weapon submachineGun;
	Weapon flamethrower;
	Weapon scatterGun;
	Weapon missileLauncher;
	Sprite handGunSelect;
	Sprite submachineGunSelect;
	Sprite flamethrowerSelect;
	Sprite scatterGunSelect;
	Sprite missileLauncherSelect;
	
	// Les �l�ments textuels.
	Font police;
	Text nbrLifeTxt;
	Text ammoTxt;
	Text scoreTxt;
	Text timeTxt;
	ScoreText zombieScoreTxts[NBR_OF_LOADED_ZOMBIES];

	// La musique (non int�gr�e)
	Music musique;

	// Variables pour g�rer le temps dans le jeu
	float deltaTPerFrame;
	int zombieSpawnTimer;
	float totalTime;
	ComboManager zombieComboManager;
	int controllerWeaponChangeTimer;
	bool weaponHasBeenChangedByController;

	// L'�tat du jeu
	GameState gameState;

	// Variables pour g�rer le score
	int score;
	int scoreForNewLife;
	
	/// <summary>
	/// Initializes les assets du jeu et les
	/// �l�ments de jeu.
	/// </summary>
	/// <returns>False si la m�thode a �chou�; true sinon.</returns>
	bool init();
	
	/// <summary>
	/// G�re les inputs du joueur.
	/// Met � jour la structure "inputs".
	/// </summary>
	void getInputs();
	
	/// <summary>
	/// Met � jour la logique du jeu.
	/// </summary>
	/// <returns>True si le joueur est encore en vie; false sinon.</returns>
	bool update();
	
	/// <summary>
	/// Affiche le jeu au joueur.
	/// </summary>
	void draw();
	
	/// <summary>
	/// Fait en sorte que la vue reste dans la zone de jeu.
	/// </summary>
	void ajusterDepassementLimitesVue();
	
	/// <summary>
	/// Cherche dans le tableau des zombies du jeu
	/// et trouve un zombie � activer.
	/// </summary>
	/// <returns>L'index dans le tableau des zombies du zombie � activer.</returns>
	int searchAvailableZombie() const;
	
	/// <summary>
	/// Fait appara�tre un zombie sur la surface du jeu.
	/// </summary>
	void spawnZombie();
	
	/// <summary>
	/// Cherche dans le tableau des packs de munitions du jeu
	/// et trouve un pack de munitions � activer.
	/// </summary>
	/// <param name="type">Le type d'arme du pack de munitions � activer.</param>
	/// <returns>L'index dans le tableau des packs de munitions du pack � activer</returns>
	int searchAvailableAmmoPack(WeaponType type) const;
	
	/// <summary>
	/// Fait appara�tre un pack de munitions dans le jeu.
	/// </summary>
	/// <param name="position">La position du pack.</param>
	void spawnAmmoPack(const sf::Vector2f& position);
	
	/// <summary>
	/// Cherche dans le tableau des textes de score et trouve
	/// un texte de score � activer.
	/// </summary>
	/// <returns>L'index du texte de score dans le tableau des textes de score � activer.</returns>
	int searchAvailableScoreText() const;
		
	/// <summary>
	/// Affiche les armes poss�d�es par le joueur (qui ont des munitions)
	/// dans l'interface du jeu.
	/// </summary>
	void drawWeaponSelection();
	
	/// <summary>
	/// S�lectionne l'arme � gauche de l'arme s�lectionn�e dans l'interface du jeu.
	/// D�termine la premi�re arme � gauche et appelle la deuxi�me m�thode du m�me nom.
	/// </summary>
	/// <param name="currentWeapon">L'arme s�lectionn�e.</param>
	void selectNewWeaponLeft(const Weapon& currentWeapon);
	
	/// <summary>
	/// S�lectionne l'arme � gauche de l'arme s�lectionn�e dans l'interface du jeu.
	/// Cette m�thode fonctionne de mani�re r�cursive.
	/// </summary>
	/// <param name="currentWeapon">L'arme s�lectionn�e.</param>
	/// <param name="leftWeapon">L'arme � gauche pour laquelle v�rifier si elle est prenable
	///													 (si elle a des munitions).</param>
	void selectNewWeaponLeft(const Weapon& currentWeapon, const Weapon& leftWeapon);

	/// <summary>
	/// S�lectionne l'arme � droite de l'arme s�lectionn�e dans l'interface du jeu.
	/// D�termine la premi�re arme � droite et appelle la deuxi�me m�thode du m�me nom.
	/// </summary>
	/// <param name="currentWeapon">L'arme s�lectionn�e.</param>
	void selectNewWeaponRight(const Weapon& currentWeapon);
	
	/// <summary>
	/// S�lectionne l'arme � droite de l'arme s�lectionn�e dans l'interface du jeu.
	/// Cette m�thode fonctionne de mani�re r�cursive.
	/// </summary>
	/// <param name="currentWeapon">L'arme s�lectionn�e.</param>
	/// <param name="rightWeapon">L'arme � droite pour laquelle v�rifier si elle est prenable
	///													 (si elle a des munitions).</param>
	void selectNewWeaponRight(const Weapon& currentWeapon, const Weapon& rightWeapon);
	
	/// <summary>
	/// Remet les valeurs de jeu aux valeurs de base, permettant de jouer
	/// une partie.
	/// </summary>
	void resetGameValues();

	RenderWindow mainWin;
	View view;
	Event event;
	Inputs inputs;
};