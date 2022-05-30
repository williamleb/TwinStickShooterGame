/*

Fichier créé par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vidéo III.

*/
#include "Player.h"
#include <cmath>
#include "Game.h"

Player::Player(Inputs& inputs, Weapon* weapon) 
	: inputs(inputs), currentWeapon(weapon)
{
	setSpeed(PLAYER_DEFAULT_SPEED);
	state = PlayerState::Alive;
	faintingTimer = 0;
	invincibilityTimer = 0;
	lives = DEFAULT_NBR_OF_LIVES;
	usingController = false;
}

void Player::update(const float deltaT)
{
	// Update différemment selon l'état du joueur.
	if (state == PlayerState::Alive || state == PlayerState::Invincibility)
	{
		// Clavier/souris -----------------------------------------------------------------------------
		if (!usingController)
		{
			// Commandes de directions -----------------------------------------
			// Dépendemment de la touche qu'il appuie, on change son angle
			// et on le fait avancer (en l'updatant au niveau du
			// movable).
			if (inputs.getUp())
			{
				// S'il appuie HAUT + DROITE...
				if (inputs.getRight())
				{
					setAngle(315, false);
				}
				// S'il appuie HAUT + GAUCHE...
				else if (inputs.getLeft())
				{
					setAngle(225, false);
				}
				// S'il appuie HAUT...
				else
				{
					setAngle(270, false);
				}
				Movable::update(deltaT);
			}
			else if (inputs.getDown())
			{
				// S'il appuie BAS + DROITE...
				if (inputs.getRight())
				{
					setAngle(45, false);
				}
				// S'il appuie BAS + GAUCHE...
				else if (inputs.getLeft())
				{
					setAngle(135, false);
				}
				// S'il appuie BAS...
				else
				{
					setAngle(90, false);
				}
				Movable::update(deltaT);
			}
			// S'il appuie GAUCHE...
			else if (inputs.getRight())
			{
				setAngle(0, false);
				Movable::update(deltaT);
			}
			// S'il appuie DROITE...
			else if (inputs.getLeft())
			{
				setAngle(180, false);
				Movable::update(deltaT);
			}

			// Commandes de visée ------------------------------------------------
			// On change l'angle du joueur pour qu'il pointe la souris.
			setRotation(getAngleWith(inputs.getMouseX(), inputs.getMouseY()));

			// Commande de tir ---------------------------------------------------
			// On tire si on a cliqué.
			if (inputs.getMouseClick())
			{
				fire();
			}
		}
		// Manette ------------------------------------------------------------------------------------
		else
		{

			// Commandes de directions -----------------------------------------
			// La direction dépend du joystick droit.
			if (inputs.getAxeXL() != 0 || inputs.getAxeYL() != 0)
			{
				sf::Vector2f leftAxisDirection(inputs.getAxeXL(), inputs.getAxeYL());
				float angle = Movable::convertDirectionToAngle(leftAxisDirection);
				setAngle(angle, false);
				Movable::update(deltaT);
			}

			// Commandes de visée ------------------------------------------------
			// La visée dépend du joystick gauche.
			if (inputs.getAxeXR() != 0 || inputs.getAxeYR() != 0)
			{
				sf::Vector2f rightAxisDirection(inputs.getAxeXR(), inputs.getAxeYR());
				float angle = Movable::convertDirectionToAngle(rightAxisDirection);
				setRotation(angle);
			}

			// Commande de tir ---------------------------------------------------
			// On tire si on a appuyé sur la gachette droite.
			if (inputs.getButtons(7))
			{
				fire();
			}
		}

		// On empêche le joueur de sortir du jeu.
		float demiWidth = getGlobalBounds().width / 2.0f;
		float demiHeight = getGlobalBounds().height / 2.0f;
		setPosition(std::max(0.0f + demiWidth, std::min(getPosition().x, Game::LARGEUR_MONDE - demiWidth)),
			std::max(0.0f + demiHeight, std::min(getPosition().y, Game::HAUTEUR_MONDE - demiHeight)));

		// On ajoute le temps à l'arme.
		currentWeapon->addTime(deltaT * 1000);

		// Si le joueur est invincible, on update
		// son status d'invincibilité.
		if (state == PlayerState::Invincibility)
		{
			invincibilityTimer += deltaT * 1000;
			// Si ça fait assez de temps qu'il est invincible, on le
			// remet dans un état normal.
			if (invincibilityTimer >= NBR_MILLISECONDS_INVINCIBILITY)
			{
				invincibilityTimer = 0;
				state = PlayerState::Alive;
				setColor(Color(255, 255, 255, 255));
			}
		}
	}
	else
	{
		setAngle(90);

		// Si le joueur est évanoui, on continue de le mettre à jour.
		if (state == PlayerState::Fainting)
		{
			faintingTimer += deltaT * 1000;
			// Si ça fait assez longtemps qu'il est évanoui, on
			// le remet sur pied et on lui donne une invincibilité.
			if (faintingTimer >= NBR_MILLISECONDS_FAINT)
			{
				faintingTimer = 0;
				state = PlayerState::Invincibility;
				setColor(Color(255, 255, 255, 127));
			}
		}
	}
}

void Player::fire()
{
	sf::Vector2f direction = Movable::convertAngleToDirection(getRotation());
	currentWeapon->fire(getPosition(), direction);
}

const Weapon* Player::getCurrentWeapon() const
{
	return currentWeapon;
}

void Player::changeWeapon(Weapon* weapon)
{
	currentWeapon = weapon;
}

PlayerState Player::getState() const
{
	return state;
}

int Player::getNbrLives() const
{
	return lives;
}

void Player::loseALife()
{
	// On fait perdre une vie au joueur seulement s'il est en vie.
	if (state == PlayerState::Alive)
	{
		lives--;

		// S'il n'a plus de vie, il meurt.
		// Sinon, il s'évanouit.
		if (lives == 0)
		{
			state = PlayerState::Dead;
		}
		else
		{
			state = PlayerState::Fainting;
			setColor(Color(0, 0, 0, 255));
		}
	}
}

void Player::addALife()
{
	lives++;
	if (lives > 0)
	{
		state = state = PlayerState::Alive;
	}
}

void Player::isUsingController(const bool usingController)
{
	this->usingController = usingController;
}