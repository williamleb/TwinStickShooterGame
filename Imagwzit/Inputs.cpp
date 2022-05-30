/*

Fichier en grande partie tiré du projet ExempleSFML2.1 du cours
Programmation de jeux vidéo III.

Il a été modifié par William Lebel (1638175) pour ajouter un
deuxième axe.

*/
#include "Inputs.h"
#include <cmath>


Inputs::Inputs()
{
	noise = 0;
	axeXL = 0;
	axeYL = 0;
	axeXR = 0;
	axeYR = 0;

	for (int i = 0; i < 8; i++)
	{
		buttons[i] = false;
	}
	for (int i = 0; i < 4; i++)
	{
		directionalKeys[i] = false;
	}
}

void Inputs::setNoiseLevel(const float noiseLevel)
{
	this->noise = noiseLevel;
}

void Inputs::clear()
{
	axeXL = 0;
	axeYL = 0;
	axeXR = 0;
	axeYR = 0;

	for (int i = 0; i < 8; i++)
	{
		buttons[i] = false;
	}
	for (int i = 0; i < 4; i++)
	{
		directionalKeys[i] = false;
	}
}

void Inputs::setAxesL(const float axeX, const float axeY)
{
	if (abs(axeX) > noise)
	{
		this->axeXL = axeX;
	}
	else
	{
		this->axeXL = 0;
	}

	if (abs(axeY) > noise)
	{
		this->axeYL = axeY;
	}
	else
	{
		this->axeYL = 0;
	}
}

void Inputs::setAxesR(const float axeX, const float axeY)
{
	if (abs(axeX) > noise)
	{
		this->axeXR = axeX;
	}
	else
	{
		this->axeXR = 0;
	}

	if (abs(axeY) > noise)
	{
		this->axeYR = axeY;
	}
	else
	{
		this->axeYR = 0;
	}
}

void Inputs::setMouse(const float mouseX, const float mouseY)
{
	this->mouseX = mouseX;
	this->mouseY = mouseY;
}

void Inputs::setButtons(const int button, const bool pressed)
{
	buttons[button] = pressed;
}

void Inputs::setUp(const bool pressed)
{
	directionalKeys[0] = pressed;
}

void Inputs::setDown(const bool pressed)
{
	directionalKeys[1] = pressed;
}

void Inputs::setLeft(const bool pressed)
{
	directionalKeys[2] = pressed;
}

void Inputs::setRight(const bool pressed)
{
	directionalKeys[3] = pressed;
}

bool Inputs::getUp() const
{
	return directionalKeys[0];
}

bool Inputs::getDown() const
{
	return directionalKeys[1];
}

bool Inputs::getLeft() const
{
	return directionalKeys[2];
}

bool Inputs::getRight() const
{
	return directionalKeys[3];
}

bool Inputs::getButtons(const int button) const
{
	return buttons[button];
}

float Inputs::getAxeXL() const
{
	return axeXL;
}

float Inputs::getAxeYL() const
{
	return axeYL;
}

float Inputs::getAxeXR() const
{
	return axeXR;
}

float Inputs::getAxeYR() const
{
	return axeYR;
}

float Inputs::getMouseX() const
{
	return mouseX;
}

float Inputs::getMouseY() const
{
	return mouseY;
}

void Inputs::setMouseClick(const bool pressed)
{
	mouseClick = pressed;
}


bool Inputs::getMouseClick() const
{
	return mouseClick;
}