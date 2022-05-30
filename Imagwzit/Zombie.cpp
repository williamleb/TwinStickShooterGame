/*

Fichier cr�� par William Lebel (1638175)

Dans le cadre du cours Programmation de jeux vid�o III.

*/
#include "Zombie.h"
#include "Game.h"

Zombie::Zombie()
{
	target = sf::Vector2f(0, 0);
	setSpeed(ZOMBIE_DEFAULT_SPEED);
	spawningTimer = 0;
}

void Zombie::update(const float deltaT)
{
	if (activated())
	{
		Movable::update(deltaT);
	}
}

void Zombie::updateWithoutCollision(const float deltaT, Zombie* allZombies)
{
	if (activated())
	{
		if (state == ZombieState::Walking)
		{
			float oldX = getPosition().x;
			float oldY = getPosition().y;
			// On met � jour le zombie.
			Movable::update(deltaT);

			// Si le zombie entre en collision avec un autre zombie que lui-m�me,
			// on le remet � la position qu'il avait avant d'�tre mis � jour.
			int count = 0;
			for (int i = 0; i < Game::NBR_OF_LOADED_ZOMBIES; i++)
			{
				if (allZombies[i].activated())
				{
					if (collidesWith(allZombies[i]))
					{
						count++;
						if (count == 2)
						{
							setPosition(oldX, oldY);
						}
					}
				}
			}
		}
		else
		{
			// Si le zombie est en train d'appara�tre...

			// On le fait tourner sur lui-m�me et s'agrandir.
			float ratio = (float)spawningTimer / (float)NBR_MILLISECONDS_OF_SPAWNING;

			float angleOfRotation = 360.0f * ratio;
			setRotation(angleOfRotation + getAngle());

			setScale(ratio, ratio);

			spawningTimer += deltaT * 1000;
			// Si �a fait assez longtemps qu'il est en train d'appara�tre,
			// on le met dans un �tat normal.
			if (spawningTimer >= NBR_MILLISECONDS_OF_SPAWNING)
			{
				setRotation(getAngle());
				setScale(1, 1);
				spawningTimer = 0;
				state = ZombieState::Walking;
			}
		}

	}
}

const sf::Vector2f& Zombie::getTarget() const
{
	return target;
}

void Zombie::setTarget(const sf::Vector2f& newTarget, bool mustComeCloser)
{
	target = newTarget;

	if (mustComeCloser)
	{
		// Le zombie doit se diriger vers sa cible.
		setAngle(getAngleWith(target.x, target.y));
	}
	else
	{
		// Ou s'en �loigner.
		setAngle(getAngleWith(target.x, target.y) + 180);
	}
}

void Zombie::setTarget(const Player& newTarget, bool mustComeCloser)
{
	// App�le la deuxi�me m�thode Zombie::setTarget.
	setTarget(sf::Vector2f(newTarget.getPosition().x, newTarget.getPosition().y), mustComeCloser);
}

ZombieState Zombie::getState() const
{
	return state;
}

void Zombie::activate()
{
	state = ZombieState::Spawning;
	spawningTimer = 0;
	setScale(0, 0);
	Activatable::activate();
}

void Zombie::activate(const sf::Vector2f& position, const sf::Vector2f& direction)
{
	state = ZombieState::Spawning;
	spawningTimer = 0;
	setScale(0, 0);
	Activatable::activate(position, direction);
}
