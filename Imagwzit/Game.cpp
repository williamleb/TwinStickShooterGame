/*

Fichier en partie créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

L'autre partie comprend une partie du code de base
fourni dans le cadre du TP1.

*/
#include "Game.h"
#include "Inputs.h"
#include <sstream>
#include <iostream>
#include <cmath>

Game::Game()
	: handGun(projectiles), submachineGun(projectiles), flamethrower(projectiles), scatterGun(projectiles), missileLauncher(projectiles), player(inputs, &handGun)
{
	mainWin.create(VideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32), "I made a game with zombies in it!");  // , Style::Titlebar); / , Style::FullScreen);
	view = View(sf::FloatRect(0, 0, LARGEUR_ECRAN, HAUTEUR_ECRAN));
	view.setCenter(LARGEUR_MONDE / 2, HAUTEUR_MONDE / 2);

	//Synchonisation coordonnée à l'écran!  Normalement 60 frames par secondes.
	//mainWin.setVerticalSyncEnabled(true);
	mainWin.setFramerateLimit(FRAME_RATE);  //Équivalent... normalement, mais pas toujours. À utiliser si la synchonisation de l'écran fonctionne mal.
	//https://www.sfml-dev.org/tutorials/2.0/window-window.php#controlling-the-framerate

	gameState = GameState::Starting;
}

int Game::run()
{
	if (!init())
	{
		return EXIT_FAILURE;
	}
	// Tant que le jeu doit continuer...
	bool mustContinue = true;
	while (mustContinue)
	{
		bool isUsingController = false;

		// Afficher l'écran de début.
		startMenu.adjustToView(mainWin.getView());
		while (mainWin.isOpen() && gameState == GameState::Starting)
		{
			if (startMenu.show(mainWin, isUsingController))
			{
				gameState = GameState::Running;
				player.isUsingController(isUsingController);
			}
		}
		// On fait jouer le joueur.
		while (mainWin.isOpen() && gameState == GameState::Running)
		{
			getInputs();
			bool gameIsRunning = update();
			if (!gameIsRunning)
			{
				gameState = GameState::Ending;
			}
			draw();
		}
		// Prépare l'écran de fin.
		endMenu.adjustToView(mainWin.getView());
		endMenu.setScore(score);
		endMenu.setTime(totalTime);
		// Afficher l'écran de fin.
		while (mainWin.isOpen() && gameState == GameState::Ending)
		{
			if (endMenu.show(mainWin, mustContinue))
			{
				gameState = GameState::Starting;
			}
		}
		if (mustContinue)
		{
			resetGameValues();
		}
	}

	return EXIT_SUCCESS;
}

bool Game::init()
{
	srand(time(NULL));

	// Chargement des armes ------------------------------------------------
	handGun.setType(WeaponType::HandGunT);
	submachineGun.setType(WeaponType::SubmachineGunT);
	flamethrower.setType(WeaponType::FlamethrowerT);
	scatterGun.setType(WeaponType::ScatterGunT);
	missileLauncher.setType(WeaponType::MissileLauncherT);

	// Assignations aux types ----------------------------------------------
	// Assignation des différents projectiles à leur type --------
	int indexOfCurrentProjectile = 0;

	// Tirs normaux: 13% des projectiles.
	int nbrOfBullets = NBR_OF_LOADED_PROJECTILES * 0.13f;
	for (int i = 0; i < nbrOfBullets; i++)
	{
		projectiles[indexOfCurrentProjectile].setType(ProjectileType::BulletT);
		indexOfCurrentProjectile++;
	}

	// Flammes: 67% des projectiles.
	int nbrOfFlames = NBR_OF_LOADED_PROJECTILES * 0.67f;
	for (int i = 0; i < nbrOfFlames; i++)
	{
		projectiles[indexOfCurrentProjectile].setType(ProjectileType::FlameT);
		indexOfCurrentProjectile++;
	}

	// Scatters: 16% des projectiles.
	int nbrOfScatters = NBR_OF_LOADED_PROJECTILES * 0.16f;
	for (int i = 0; i < nbrOfScatters; i++)
	{
		projectiles[indexOfCurrentProjectile].setType(ProjectileType::ScatterT);
		indexOfCurrentProjectile++;
	}

	// Missiles: 4% des projectiles.
	int nbrOfMissiles = NBR_OF_LOADED_PROJECTILES * 0.04f;
	for (int i = 0; i < nbrOfMissiles; i++)
	{
		projectiles[indexOfCurrentProjectile].setType(ProjectileType::MissileT);
		indexOfCurrentProjectile++;
	}

	// Si on n'a pas chargé tous les projectiles (à cause d'un tronquage du nombre à
	// virgule vers un entier), on rempli ce qui reste avec des projectiles de base.
	if (nbrOfBullets + nbrOfFlames + nbrOfMissiles + nbrOfScatters != NBR_OF_LOADED_PROJECTILES)
	{
		for (int i = indexOfCurrentProjectile; i < NBR_OF_LOADED_PROJECTILES; i++)
		{
			projectiles[i].setType(ProjectileType::BulletT);
		}
	}

	// Assignation des différents ammo packs à leur type ---------
	for (int i = 0; i < NBR_OF_LOADED_AMMOPACKS; i++)
	{
		ammoPacks[i].setWeaponType((WeaponType)((i % 4) + 1));
	}

	// Chargement des assets -----------------------------------------------
	if (!terrainT.loadFromFile("Sprites\\Terrain.jpg"))
	{
		return false;
	}

	if (!joueurT.loadFromFile("Sprites\\FreeArt\\Joueur.png"))
	{
		return false;
	}

	if (!zombieT[0].loadFromFile("Sprites\\FreeArt\\Zombie1.png"))
	{
		return false;
	}

	if (!zombieT[1].loadFromFile("Sprites\\FreeArt\\Zombie2.png"))
	{
		return false;
	}

	if (!zombieT[2].loadFromFile("Sprites\\FreeArt\\Zombie3.png"))
	{
		return false;
	}

	if (!bulletT.loadFromFile("Sprites\\Projectiles\\Bullet.png"))
	{
		return false;
	}

	if (!flameT.loadFromFile("Sprites\\Projectiles\\Flame.png"))
	{
		return false;
	}

	if (!missileT.loadFromFile("Sprites\\Projectiles\\Missile.png"))
	{
		return false;
	}

	if (!scatterT.loadFromFile("Sprites\\Projectiles\\Scatter.png"))
	{
		return false;
	}

	if (!bulletPackT.loadFromFile("Sprites\\Logos\\BulletLogo.png"))
	{
		return false;
	}

	if (!flamePackT.loadFromFile("Sprites\\Logos\\FlameLogo.png"))
	{
		return false;
	}

	if (!missilePackT.loadFromFile("Sprites\\Logos\\MissileLogo.png"))
	{
		return false;
	}

	if (!scatterPackT.loadFromFile("Sprites\\Logos\\ScatterLogo.png"))
	{
		return false;
	}

	if (!handGunSelectT.loadFromFile("Sprites\\WeaponSelection\\HandGun.png"))
	{
		return false;
	}

	if (!submachineGunSelectT.loadFromFile("Sprites\\WeaponSelection\\SubmachineGun.png"))
	{
		return false;
	}

	if (!flamethrowerSelectT.loadFromFile("Sprites\\WeaponSelection\\Flamethrower.png"))
	{
		return false;
	}

	if (!scatterGunSelectT.loadFromFile("Sprites\\WeaponSelection\\ScatterGun.png"))
	{
		return false;
	}

	if (!missileLauncherSelectT.loadFromFile("Sprites\\WeaponSelection\\MissileLauncher.png"))
	{
		return false;
	}

	if (!controllerHelpT.loadFromFile("Sprites\\Help\\ControllerHelp.png"))
	{
		return false;
	}

	if (!mouseAndKeyboardHelpT.loadFromFile("Sprites\\Help\\KeyboardAndMouseHelp.png"))
	{
		return false;
	}

	if (!police.loadFromFile("Polices\\zombie.otf"))
	{
		return false;
	}

	if (!musique.openFromFile("Sons\\i_maed_a_gam3_w1th_z0mb1es_full_song.ogg"))
	{
		return false;
	}

	// Chargement des ressources de jeu -------------------------------------
	// Terrain
	terrain.setTexture(terrainT);
	terrain.setPosition(0, 0);

	// Joueur
	player.setTexture(joueurT);
	player.setPosition(CENTRE_MONDE_X, CENTRE_MONDE_Y);

	// Zombies
	for (int i = 0; i < NBR_OF_LOADED_ZOMBIES; i++)
	{
		zombies[i].setTexture(zombieT[i % 3]);
	}

	// Texte pour afficher le nombre de vies.
	nbrLifeTxt.setString("Lives: ");
	nbrLifeTxt.setFont(police);
	nbrLifeTxt.setCharacterSize(25);
	nbrLifeTxt.setFillColor(Color(172, 1, 5));
	nbrLifeTxt.setOutlineColor(Color::Black);
	nbrLifeTxt.setOutlineThickness(2);

	// Texte pour afficher le nombre de munitions de l'arme courrante.
	ammoTxt.setString("Ammo: ");
	ammoTxt.setFont(police);
	ammoTxt.setCharacterSize(25);
	ammoTxt.setFillColor(Color(172, 1, 5));
	ammoTxt.setOutlineColor(Color::Black);
	ammoTxt.setOutlineThickness(2);

	// Texte pour afficher le score du joueur.
	scoreTxt.setString("Score: ");
	scoreTxt.setFont(police);
	scoreTxt.setCharacterSize(25);
	scoreTxt.setFillColor(Color(172, 1, 5));
	scoreTxt.setOutlineColor(Color::Black);
	scoreTxt.setOutlineThickness(2);

	// Texte pour afficher le temps total de jeu
	timeTxt.setString("Time: ");
	timeTxt.setFont(police);
	timeTxt.setCharacterSize(25);
	timeTxt.setFillColor(Color(172, 1, 5));
	timeTxt.setOutlineColor(Color::Black);
	timeTxt.setOutlineThickness(2);

	// Textes pour afficher les scores lorsqu'un zombie est tué.
	for (int i = 0; i < NBR_OF_LOADED_ZOMBIES; i++)
	{
		zombieScoreTxts[i].setFont(police);
		zombieScoreTxts[i].setCharacterSize(14);
		zombieScoreTxts[i].setFillColor(Color(172, 1, 5));
		zombieScoreTxts[i].setOutlineColor(Color::Black);
		zombieScoreTxts[i].setOutlineThickness(1);
	}

	// Projectiles
	for (int i = 0; i < NBR_OF_LOADED_PROJECTILES; i++)
	{
		switch (projectiles[i].getType())
		{
		case ProjectileType::BulletT:
			projectiles[i].setTexture(bulletT);
			break;
		case ProjectileType::FlameT:
			projectiles[i].setTexture(flameT);
			break;
		case ProjectileType::MissileT:
			projectiles[i].setTexture(missileT);
			break;
		case ProjectileType::ScatterT:
			projectiles[i].setTexture(scatterT);
			break;
		}
	}

	// Packs de munitions
	for (int i = 0; i < NBR_OF_LOADED_AMMOPACKS; i++)
	{
		switch (ammoPacks[i].getWeaponType())
		{
		case WeaponType::HandGunT:
			ammoPacks[i].setTexture(bulletPackT);
			break;
		case WeaponType::SubmachineGunT:
			ammoPacks[i].setTexture(bulletPackT);
			break;
		case WeaponType::FlamethrowerT:
			ammoPacks[i].setTexture(flamePackT);
			break;
		case WeaponType::ScatterGunT:
			ammoPacks[i].setTexture(scatterPackT);
			break;
		case WeaponType::MissileLauncherT:
			ammoPacks[i].setTexture(missilePackT);
			break;
		}
	}

	// Le menu de sélection des armes
	handGunSelect.setTexture(handGunSelectT);
	submachineGunSelect.setTexture(submachineGunSelectT);
	flamethrowerSelect.setTexture(flamethrowerSelectT);
	scatterGunSelect.setTexture(scatterGunSelectT);
	missileLauncherSelect.setTexture(missileLauncherSelectT);

	// Le menu du début
	startMenu.initializeBackgroundImage(terrainT);
	startMenu.initializeControllerHelp(controllerHelpT, 50, 100);
	startMenu.initializeKeyboardAndMouseHelp(mouseAndKeyboardHelpT, 500, 100);
	startMenu.initializeInstructions("Appuyez sur X (PS) ou A (XBox) pour jouer avec une manette.\n Appuyez sur Enter pour jouer avec le clavier et la souris.",
		police, 20, 50, 600, Color(172, 1, 5));


	// Le menu de fin
	endMenu.initializeBackgroundImage(terrainT);
	endMenu.initializeScore("Score final: ", police, 20, 50, 100, Color(172, 1, 5));
	endMenu.initializeTime("Temps total: ", police, 20, 50, 200, Color(172, 1, 5));
	endMenu.initializeInstructions("Appuyez sur X (PS), A (XBox) ou Enter pour jouer une autre partie.\n Appuyez sur O (PS), B (XBox) ou ESC pour arrêter le programme.",
		police, 20, 50, 300, Color(172, 1, 5));

	// On met le jeu dans un état stable.
	resetGameValues();
	deltaTPerFrame = 1.0f / (float)FRAME_RATE;
	inputs.setNoiseLevel(20);

	//musique.play();
	return true;

}

void Game::getInputs()
{
	// Traitement des inputs génériques ------------------------------------

	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (mainWin.pollEvent(event))
	{
		if (event.type == Event::Closed
				|| Keyboard::isKeyPressed(Keyboard::Escape))
		{
			mainWin.close();
		}
	}

	// Génération de la lise des inputs pour la parties --------------------

	// On efface les inputs du cycle précédent.
	inputs.clear();

	// Gamepad
	for (int i = 0; i < 8; i++)
	{
		if (Joystick::isButtonPressed(0, i))
		{
			inputs.setButtons(i, true);
		}
	}

	inputs.setAxesL(Joystick::getAxisPosition(0, Joystick::Axis::X), Joystick::getAxisPosition(0, Joystick::Axis::Y));
	inputs.setAxesR(Joystick::getAxisPosition(0, Joystick::Axis::Z), Joystick::getAxisPosition(0, Joystick::Axis::R));

	// Clavier
	inputs.setUp(Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W));
	inputs.setDown(Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S));
	inputs.setLeft(Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A));
	inputs.setRight(Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D));

	// Souris
	Vector2f viewPos = mainWin.mapPixelToCoords(Mouse::getPosition(mainWin));
	inputs.setMouse(viewPos.x, viewPos.y);
	inputs.setMouseClick(Mouse::isButtonPressed(Mouse::Left));

	// Change l'arme...
	// Selon la touche pesée.
	if (Keyboard::isKeyPressed(Keyboard::Num1))
	{
		player.changeWeapon(&handGun);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num2))
	{
		player.changeWeapon(&submachineGun);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num3))
	{
		player.changeWeapon(&flamethrower);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num4))
	{
		player.changeWeapon(&scatterGun);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num5))
	{
		player.changeWeapon(&missileLauncher);
	}

	// Selon le bouton de la manette pesé.
	if (!weaponHasBeenChangedByController)
	{
		// L1
		if (inputs.getButtons(4))
		{
			selectNewWeaponLeft(*(player.getCurrentWeapon()));
		}
		// R1
		if (inputs.getButtons(5))
		{
			selectNewWeaponRight(*(player.getCurrentWeapon()));
		}
		weaponHasBeenChangedByController = true;
	}
}

bool Game::update()
{
	// Update les valeurs de temps ------------------------------------------
	// Temps total.
	totalTime += deltaTPerFrame;

	// Temps de changement d'arme par la manette
	if (weaponHasBeenChangedByController)
	{
		controllerWeaponChangeTimer += deltaTPerFrame * 1000;

		// Si ça fait assez longtemps qu'on n'a pas chagé d'arme avec
		// la manette, on permet de le faire de nouveau.
		if (controllerWeaponChangeTimer >= NBR_MILLISECONDS_BEFORE_CONTROLLER_WEAPON_CHANGE)
		{
			weaponHasBeenChangedByController = false;
			controllerWeaponChangeTimer = 0;
		}
	}

	// L'administreur de combos.
	zombieComboManager.addMilliseconds(deltaTPerFrame * 1000);

	// Ajuste la vue -------------------------------------------------------
	view.setCenter(player.getPosition().x, player.getPosition().y);
	ajusterDepassementLimitesVue();	

	// Met à jour les textes -----------------------------------------------
	// Le nombre de vies.
	nbrLifeTxt.setPosition(view.getCenter().x - LARGEUR_ECRAN / 2 + 8, view.getCenter().y - HAUTEUR_ECRAN / 2);
	std::stringstream nbrLivesString;
	nbrLivesString << "Lives: " << player.getNbrLives();
	nbrLifeTxt.setString(nbrLivesString.str());

	// Le score
	scoreTxt.setPosition(view.getCenter().x - LARGEUR_ECRAN / 2 + 8, view.getCenter().y - HAUTEUR_ECRAN / 2 + 20);
	std::stringstream scoreString;
	scoreString << "Score: " << score;
	scoreTxt.setString(scoreString.str());

	// Le Temps
	timeTxt.setPosition(view.getCenter().x - LARGEUR_ECRAN / 2 + 8, view.getCenter().y - HAUTEUR_ECRAN / 2 + 40);
	std::stringstream timeString;
	if ((int)totalTime % 60 < 10)
	{
		timeString << "Time: " << (int)totalTime / 60 << ":0" << (int)totalTime % 60;
	}
	else
	{
		timeString << "Time: " << (int)totalTime / 60 << ":" << (int)totalTime % 60;
	}
	timeTxt.setString(timeString.str());

	// Le nombre de munitions.
	ammoTxt.setPosition(view.getCenter().x - LARGEUR_ECRAN / 2 + 8, view.getCenter().y - HAUTEUR_ECRAN / 2 + 60);
	std::stringstream nbrAmmoString;
	nbrAmmoString << "Ammo: ";
	int nbrAmmo = player.getCurrentWeapon()->getAmmo();
	if (nbrAmmo == Weapon::InfiniteAmmo)
	{
		nbrAmmoString << "Unlimited";
	}
	else
	{
		nbrAmmoString << nbrAmmo;
	}
	ammoTxt.setString(nbrAmmoString.str());

	// Update les entités de jeu -------------------------------------------
	// Le joueur
	player.update(deltaTPerFrame);
	if (player.getCurrentWeapon()->getAmmo() == 0)
	{
		player.changeWeapon(&handGun);
	}


	// Les projectiles actifs
	for (int i = 0; i < NBR_OF_LOADED_PROJECTILES; i++)
	{
		if (projectiles[i].activated())
		{
			projectiles[i].update(deltaTPerFrame);
		}
	}
	
	// Les zombies actifs.
	for (int i = 0; i < NBR_OF_LOADED_ZOMBIES; i++)
	{
		if (zombies[i].activated())
		{
			zombies[i].setTarget(player, player.getState() == PlayerState::Alive || player.getState() == PlayerState::Invincibility);

			// zombies[i].update(deltaTPerFrame);
			zombies[i].updateWithoutCollision(deltaTPerFrame, zombies);
		}
	}

	// Les bonus actifs.
	for (int i = 0; i < NBR_OF_LOADED_AMMOPACKS; i++)
	{
		if (ammoPacks[i].isSpawned())
		{
			ammoPacks[i].update(deltaTPerFrame);
		}
	}

	// Les textes de score actifs.
	for (int i = 0; i < NBR_OF_LOADED_ZOMBIES; i++)
	{
		if (zombieScoreTxts[i].isSpawned())
		{
			zombieScoreTxts[i].addTime(deltaTPerFrame * 1000);
		}
	}

	// Gère l'apparition des zombies ---------------------------------------
	// Spawn un zombie si ça fait assez de temps.
	zombieSpawnTimer += deltaTPerFrame * 1000;

	// Change le temps que ça prend à faire apparaître un zombie
	// selon le temps de jeu total.
	int millisecondsForZombieToSpawn = 0;
	if (totalTime >= 600)
	{
		millisecondsForZombieToSpawn = 150;
	}
	else if (totalTime >= 300)
	{
	
		millisecondsForZombieToSpawn = 250;
	}
	else if (totalTime >= 180)
	{
		millisecondsForZombieToSpawn = 500;
	}
	else if (totalTime >= 120)
	{
		millisecondsForZombieToSpawn = 600;
	}
	else if (totalTime >= 60)
	{
		millisecondsForZombieToSpawn = 750;
	}
	else if (totalTime >= 30)
	{
		millisecondsForZombieToSpawn = 850;
	}
	else
	{
		millisecondsForZombieToSpawn = 1000;
	}

	if (zombieSpawnTimer >= millisecondsForZombieToSpawn)
	{
		spawnZombie();
		zombieSpawnTimer = 0;
	}

	// Regarde les collisions -----------------------------------------------
	// Pour tous les zombies actifs...
	for (int i = 0; i < NBR_OF_LOADED_ZOMBIES; i++)
	{
		if (zombies[i].activated())
		{
			// Si le zombie touche au joueur...
			if (zombies[i].collidesWith(player))
			{
				player.loseALife();
			}

			// Pour toues les projectiles actifs...
			for (int j = 0; j < NBR_OF_LOADED_PROJECTILES; j++)
			{
				// Si le zombie et le projectile sont en collision...
				if (projectiles[j].activated()
						&& zombies[i].collidesWith(projectiles[j]))
				{
					// Désactive le projectile si ce n'est pas une Flame ou un Missile.
					if (projectiles[j].getType() != ProjectileType::FlameT
							&& projectiles[j].getType() != ProjectileType::MissileT)
					{
						projectiles[j].deactivate();
					}
					// Désactive le zombie.
					zombies[i].deactivate();

					// Gère le score du zombie mort.
					int scoreAAjouter = std::min(100 + 10 * zombieComboManager.getComboValue(), 500);
					score += scoreAAjouter;
					scoreForNewLife += scoreAAjouter;

					if (scoreForNewLife >= SCORE_FOR_NEW_LIFE)
					{
						scoreForNewLife -= SCORE_FOR_NEW_LIFE;
						player.addALife();
					}
					
					zombieComboManager.addCombo();

					// Apparition du ScoreText.
					int indexOfScoreText = searchAvailableScoreText();
					zombieScoreTxts[i].spawn(std::to_string(scoreAAjouter).c_str(), zombies[i].getPosition());
					
					// Gère l'apparition des munitions par terre.
					// On a environs 5% de chance qu'un zombie laisse un pack de munitions.
					if ((float)rand()/(float)RAND_MAX * 100 < 5 )
					{
						spawnAmmoPack(zombies[i].getPosition());
					}
					break;
				}
			}
		}
	}

	// Pour tous les packs de munitions actifs...
	for (int i = 0; i < NBR_OF_LOADED_AMMOPACKS; i++)
	{
		if (ammoPacks[i].isSpawned())
		{
			// Si le joueur le touche...
			if (ammoPacks[i].collidesWith(player))
			{
				// Ramasse le pack.
				switch (ammoPacks[i].getWeaponType())
				{
				case WeaponType::HandGunT:
					ammoPacks[i].pick(handGun);
					break;
				case WeaponType::SubmachineGunT:
					ammoPacks[i].pick(submachineGun);
					break;
				case WeaponType::FlamethrowerT:
					ammoPacks[i].pick(flamethrower);
					break;
				case WeaponType::ScatterGunT:
					ammoPacks[i].pick(scatterGun);
					break;
				case WeaponType::MissileLauncherT:
					ammoPacks[i].pick(missileLauncher);
					break;
				}
			}
		}
	}

	return player.getState() != PlayerState::Dead;
}

void Game::draw()
{
	mainWin.clear();
	mainWin.setView(view);

	// Affiche tous les éléments du jeu et de l'interface.
	mainWin.draw(terrain);
	for (int i = 0; i < NBR_OF_LOADED_AMMOPACKS; i++)
	{
		if (ammoPacks[i].isSpawned())
		{
			mainWin.draw(ammoPacks[i]);
		}
	}
	for (int i = 0; i < NBR_OF_LOADED_PROJECTILES; i++)
	{
		if (projectiles[i].activated())
		{
			mainWin.draw(projectiles[i]);
		}
	}
	mainWin.draw(player);
	for (int i = 0; i < NBR_OF_LOADED_ZOMBIES; i++)
	{
			if (zombies[i].activated())
			{
				mainWin.draw(zombies[i]);
			}
	}
	for (int i = 0; i < NBR_OF_LOADED_ZOMBIES; i++)
	{
		if (zombieScoreTxts[i].isSpawned())
		{
			mainWin.draw(zombieScoreTxts[i]);
		}
	}
	mainWin.draw(nbrLifeTxt);
	mainWin.draw(scoreTxt);
	mainWin.draw(timeTxt);
	mainWin.draw(ammoTxt);
	drawWeaponSelection();

	mainWin.display();
}

void Game::ajusterDepassementLimitesVue()
{
	if (view.getCenter().x < LIMITE_VUE_MIN_X)
	{
		view.setCenter(LIMITE_VUE_MIN_X, view.getCenter().y);
	}
	else if (view.getCenter().x > LIMITE_VUE_MAX_X)
	{
		view.setCenter(LIMITE_VUE_MAX_X, view.getCenter().y);
	}

	if (view.getCenter().y < LIMITE_VUE_MIN_Y)
	{
		view.setCenter(view.getCenter().x, LIMITE_VUE_MIN_Y);
	}
	else if (view.getCenter().y > LIMITE_VUE_MAX_Y)
	{
		view.setCenter(view.getCenter().x, LIMITE_VUE_MAX_Y);
	}
}

int Game::searchAvailableZombie() const
{
	int indexOfZombie = -1;
	int currentIndex = 0;
	// Tant qu'on ne trouve pas de zombie qui correspond à la demande et
	// qu'on n'a pas fini de parcourir le tableau...
	while (indexOfZombie == -1 && currentIndex < NBR_OF_LOADED_ZOMBIES)
	{
		// Si on trouve un zombie qui n'est pas déjà activé...
		if (!(zombies[currentIndex].activated()))
		{
			// On sauvegarde sa position.
			indexOfZombie = currentIndex;
		}
		++currentIndex;
	}
	return indexOfZombie;
}

void Game::spawnZombie()
{
	// Si on trouve un zombie...
	int indexOfAvailableZombie = searchAvailableZombie();
	if (indexOfAvailableZombie != -1)
	{
		// On peut essayer de lui trouver une position.
		sf::Vector2f position;
		sf::FloatRect zombieSize = zombies[indexOfAvailableZombie].getGlobalBounds();
		sf::Vector2f posP = player.getPosition();

		// Tant que la position est trop près du joueur...
		bool positionIsNotValid = true;
		while (positionIsNotValid)
		{
			position.x = rand() % (LARGEUR_MONDE - (int)zombieSize.width * 2) + zombieSize.width;
			position.y = rand() % (HAUTEUR_MONDE - (int)zombieSize.height * 2) + zombieSize.height;

			// Vérifie si la position est assez loin du joueur.
			// (posPX - posZX)^2 + (posPY - posZY)^2 = dist^2
			if ( (posP.x - position.x) * (posP.x - position.x) + (posP.y - position.y) * (posP.y - position.y) >= MIN_DIST_FROM_PLAYER_TO_SPAWN * MIN_DIST_FROM_PLAYER_TO_SPAWN)
			{
				positionIsNotValid = false;

				zombies[indexOfAvailableZombie].activate(position);

				// Regarde que le zombie ne rentre pas en collision avec un autre zombie que lui-même.à
				// (pour ne pas que deux zommbies soient pris l'un dans l'autre).
				for (int i = 0; i < NBR_OF_LOADED_ZOMBIES; i++)
				{
					if(i != indexOfAvailableZombie)
					{
						if (zombies[indexOfAvailableZombie].collidesWith(zombies[i]))
						{
							zombies[indexOfAvailableZombie].deactivate();
							positionIsNotValid = true;
						}
					}
				}
			}
		}
	}
}

int Game::searchAvailableAmmoPack(WeaponType type) const
{
	int indexOfAmmoPack = -1;
	int currentIndex = 0;
	// Tant qu'on ne trouve pas de pack de munition qui correspond à la demande et
	// qu'on n'a pas fini de parcourir le tableau...
	while (indexOfAmmoPack == -1 && currentIndex < NBR_OF_LOADED_AMMOPACKS)
	{
		// Si on trouve un pack de munitions qui n'est pas déjà sur le jeu
		// et qui correspond au type recherch...
		if (!(ammoPacks[currentIndex].isSpawned())
				&& ammoPacks[currentIndex].getWeaponType() == type)
		{
			// On sauvegarde sa position.
			indexOfAmmoPack = currentIndex;
		}
		++currentIndex;
	}
	return indexOfAmmoPack;
}

void Game::spawnAmmoPack(const sf::Vector2f& position)
{
	// On choisi au hasard le type de pack de munitions qu'on veut.
	WeaponType type = (WeaponType)((rand() % 4) + 1);

	// Si on trouve un pack de munition correspondant à la demande...
	int indexOfAvailableAmmoPack = searchAvailableAmmoPack(type);
	if (indexOfAvailableAmmoPack != -1)
	{
		// On le fait apparaître.
		ammoPacks[indexOfAvailableAmmoPack].spawn(position);
	}
}

int Game::searchAvailableScoreText() const
{
	int indexOfScoreText = -1;
	int currentIndex = 0;
	// Tant qu'on ne trouve pas un texte de score qui correspond à la demande et
	// qu'on n'a pas fini de parcourir le tableau...
	while (indexOfScoreText == -1 && currentIndex < NBR_OF_LOADED_ZOMBIES)
	{
		// Si on trouve un texte de score qui n'est pas déjà sur le jeu...
		if (!(zombieScoreTxts[currentIndex].isSpawned()))
		{
			// On sauvegarde sa position.
			indexOfScoreText = currentIndex;
		}
		++currentIndex;
	}
	return indexOfScoreText;
}

void Game::drawWeaponSelection()
{
	const	float POS_X = view.getCenter().x - LARGEUR_ECRAN / 2 + 8;
	const float POS_Y = view.getCenter().y - HAUTEUR_ECRAN / 2 + 100;

	int offsetX = 0;

	// Affiche les armes activées les unes à la suite des autres.
	// Hand gun
	if (handGun.getAmmo() != 0)
	{
		handGunSelect.setPosition(POS_X + offsetX, POS_Y);
		offsetX += handGunSelect.getGlobalBounds().width + 5;

		// Choisit la couleur selon si l'arme est activée ou non.
		if (player.getCurrentWeapon()->getType() == WeaponType::HandGunT)
		{
			handGunSelect.setColor(Color::White);
		}
		else
		{
			handGunSelect.setColor(Color::Red);
		}

		mainWin.draw(handGunSelect);
	}

	// Submachine Gun
	if (submachineGun.getAmmo() != 0)
	{
		submachineGunSelect.setPosition(POS_X + offsetX, POS_Y);
		offsetX += submachineGunSelect.getGlobalBounds().width + 5;

		// Choisit la couleur selon si l'arme est activée ou non.
		if (player.getCurrentWeapon()->getType() == WeaponType::SubmachineGunT)
		{
			submachineGunSelect.setColor(Color::White);
		}
		else
		{
			submachineGunSelect.setColor(Color::Red);
		}

		mainWin.draw(submachineGunSelect);
	}

	// Flamethrower
	if (flamethrower.getAmmo() != 0)
	{
		flamethrowerSelect.setPosition(POS_X + offsetX, POS_Y);
		offsetX += flamethrowerSelect.getGlobalBounds().width + 5;

		// Choisit la couleur selon si l'arme est activée ou non.
		if (player.getCurrentWeapon()->getType() == WeaponType::FlamethrowerT)
		{
			flamethrowerSelect.setColor(Color::White);
		}
		else
		{
			flamethrowerSelect.setColor(Color::Red);
		}

		mainWin.draw(flamethrowerSelect);
	}

	// Scatter Gun
	if (scatterGun.getAmmo() != 0)
	{
		scatterGunSelect.setPosition(POS_X + offsetX, POS_Y);
		offsetX += scatterGunSelect.getGlobalBounds().width + 5;

		// Choisit la couleur selon si l'arme est activée ou non.
		if (player.getCurrentWeapon()->getType() == WeaponType::ScatterGunT)
		{
			scatterGunSelect.setColor(Color::White);
		}
		else
		{
			scatterGunSelect.setColor(Color::Red);
		}

		mainWin.draw(scatterGunSelect);
	}

	// Missile Launcher
	if (missileLauncher.getAmmo() != 0)
	{
		missileLauncherSelect.setPosition(POS_X + offsetX, POS_Y);
		offsetX += missileLauncherSelect.getGlobalBounds().width + 5;

		// Choisit la couleur selon si l'arme est activée ou non.
		if (player.getCurrentWeapon()->getType() == WeaponType::MissileLauncherT)
		{
			missileLauncherSelect.setColor(Color::White);
		}
		else
		{
			missileLauncherSelect.setColor(Color::Red);
		}

		mainWin.draw(missileLauncherSelect);
	}

}

void Game::selectNewWeaponLeft(const Weapon& currentWeapon)
{
	// Détermine l'arme qui est immédiatement à gauche dans l'interface.
	switch (currentWeapon.getType())
	{
	case HandGunT:
		selectNewWeaponLeft(currentWeapon, missileLauncher);
		break;
	case SubmachineGunT:
		selectNewWeaponLeft(currentWeapon, handGun);
		break;
	case FlamethrowerT:
		selectNewWeaponLeft(currentWeapon, submachineGun);
		break;
	case ScatterGunT:
		selectNewWeaponLeft(currentWeapon, flamethrower);
		break;
	case MissileLauncherT:
		selectNewWeaponLeft(currentWeapon, scatterGun);
		break;
	}
}

void Game::selectNewWeaponLeft(const Weapon& currentWeapon, const Weapon& leftWeapon)
{
	// Si on a fait le tour des armes sans trouver une autre arme valide, on arrête la
	// recherche: on ne change pas d'arme.
	if (leftWeapon.getType() != currentWeapon.getType())
	{
		// On vérifie que l'arme de gauche possède des munitions.
		// Si oui, on change pour cette arme.
		// Sinon, on regarde l'arme à gauche de l'arme de gauche.
		switch (leftWeapon.getType())
		{
		case HandGunT:
			if (handGun.getAmmo() == 0)
			{
				selectNewWeaponLeft(currentWeapon, missileLauncher);
			}
			else
			{
				player.changeWeapon(&handGun);
			}
			break;
		case SubmachineGunT:
			if (submachineGun.getAmmo() == 0)
			{
				selectNewWeaponLeft(currentWeapon, handGun);
			}
			else
			{
				player.changeWeapon(&submachineGun);
			}
			break;
		case FlamethrowerT:
			if (flamethrower.getAmmo() == 0)
			{
				selectNewWeaponLeft(currentWeapon, submachineGun);
			}
			else
			{
				player.changeWeapon(&flamethrower);
			}
			break;
		case ScatterGunT:
			if (scatterGun.getAmmo() == 0)
			{
				selectNewWeaponLeft(currentWeapon, flamethrower);
			}
			else
			{
				player.changeWeapon(&scatterGun);
			}
			break;
		case MissileLauncherT:
			if (missileLauncher.getAmmo() == 0)
			{
				selectNewWeaponLeft(currentWeapon, scatterGun);
			}
			else
			{
				player.changeWeapon(&missileLauncher);
			}
			break;
		}
	}
}

void Game::selectNewWeaponRight(const Weapon& currentWeapon)
{
	// Détermine l'arme qui est immédiatement à droite dans l'interface.
	switch (currentWeapon.getType())
	{
	case HandGunT:
		selectNewWeaponRight(currentWeapon, submachineGun);
		break;
	case SubmachineGunT:
		selectNewWeaponRight(currentWeapon, flamethrower);
		break;
	case FlamethrowerT:
		selectNewWeaponRight(currentWeapon, scatterGun);
		break;
	case ScatterGunT:
		selectNewWeaponRight(currentWeapon, missileLauncher);
		break;
	case MissileLauncherT:
		selectNewWeaponRight(currentWeapon, handGun);
		break;
	}
}

void Game::selectNewWeaponRight(const Weapon& currentWeapon, const Weapon& rightWeapon)
{
	// Si on a fait le tour des armes sans trouver une autre arme valide, on arrête la
	// recherche: on ne change pas d'arme.
	if (rightWeapon.getType() != currentWeapon.getType())
	{
		// On vérifie que l'arme de droite possède des munitions.
		// Si oui, on change pour cette arme.
		// Sinon, on regarde l'arme à droite de l'arme de droite.
		switch (rightWeapon.getType())
		{
		case HandGunT:
			if (handGun.getAmmo() == 0)
			{
				selectNewWeaponRight(currentWeapon, submachineGun);
			}
			else
			{
				player.changeWeapon(&handGun);
			}
			break;
		case SubmachineGunT:
			if (submachineGun.getAmmo() == 0)
			{
				selectNewWeaponRight(currentWeapon, flamethrower);
			}
			else
			{
				player.changeWeapon(&submachineGun);
			}
			break;
		case FlamethrowerT:
			if (flamethrower.getAmmo() == 0)
			{
				selectNewWeaponRight(currentWeapon, scatterGun);
			}
			else
			{
				player.changeWeapon(&flamethrower);
			}
			break;
		case ScatterGunT:
			if (scatterGun.getAmmo() == 0)
			{
				selectNewWeaponRight(currentWeapon, missileLauncher);
			}
			else
			{
				player.changeWeapon(&scatterGun);
			}
			break;
		case MissileLauncherT:
			if (missileLauncher.getAmmo() == 0)
			{
				selectNewWeaponRight(currentWeapon, handGun);
			}
			else
			{
				player.changeWeapon(&missileLauncher);
			}
			break;
		}
	}
}

void Game::resetGameValues()
{
	static int nbrOfGames = 0;

	// On remet les valeurs de temps à 0.
	zombieSpawnTimer = 1000;
	totalTime = 0.0f;
	weaponHasBeenChangedByController = false;
	controllerWeaponChangeTimer = 0;

	// On remet les valeurs de score à 0.
	score = 0;
	scoreForNewLife = 0;

	// On remet la vue au centre.
	view.setCenter(LARGEUR_MONDE / 2, HAUTEUR_MONDE / 2);

	// Si on avait une partie avant, on doit effacer les
	// objets de jeu présents sur le jeu et jeter les
	// munitions des armes.
	if(nbrOfGames > 0)
	{
		// On remet le joueur au centre du monde.
		player.setPosition(LARGEUR_MONDE / 2, HAUTEUR_MONDE / 2);

		for (int i = 0; i < NBR_OF_LOADED_ZOMBIES; i++)
		{
			zombies[i].deactivate();
			zombieScoreTxts[i].deSpawn();
		}
		for (int i = 0; i < NBR_OF_LOADED_PROJECTILES; i++)
		{
			projectiles[i].deactivate();
		}
		for (int i = 0; i < NBR_OF_LOADED_AMMOPACKS; i++)
		{
			ammoPacks[i].deSpawn();
		}
		for (int i = 0; i < 5; i++)
		{
			player.addALife();
		}
		submachineGun.throwAllAmmo();
		flamethrower.throwAllAmmo();
		scatterGun.throwAllAmmo();
		missileLauncher.throwAllAmmo();
	}

	nbrOfGames++;
}