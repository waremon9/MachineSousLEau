#include "Enemie.h"

Enemie::Enemie()
{
	_ShapeMinimap = new sf::CircleShape(3, 10);
	_ShapeMinimap->setFillColor(sf::Color(150, 255, 150, 0));
	_ShapeMinimap->setOrigin(1.5, 1.5);

	_Shape = new sf::CircleShape(15, 20);
	_Shape->setFillColor(sf::Color::Yellow);
	_Shape->setOrigin(15, 15);
	DotIntensity = 0;
	Dead = false;
}

Enemie::Enemie(sf::Vector2f coord)
{
	_ShapeMinimap = new sf::CircleShape(3, 10);
	_ShapeMinimap->setFillColor(sf::Color(150, 255, 150, 0));
	_ShapeMinimap->setOrigin(1.5, 1.5);

	_Shape = new sf::CircleShape(15, 20);
	_Shape->setFillColor(sf::Color::Yellow);
	_Shape->setOrigin(15, 15);
	setCoordinate(coord);

	DotIntensity = 0;
	Dead = false;
}

sf::CircleShape* Enemie::getShape() { return _Shape; }

sf::CircleShape* Enemie::getShapeMinimap()
{
	return _ShapeMinimap;
}

sf::Vector2f Enemie::getCoordinate() const { return Coordinate; }

bool Enemie::getDead() const
{
	return Dead;
}


void Enemie::setCoordinate(sf::Vector2f coord)
{
	Coordinate = coord;
}

void Enemie::setScreenPosition(sf::Vector2f pos)
{
	_Shape->setPosition(pos);
}

void Enemie::setDead(bool b)
{
	Dead = b;
}

void Enemie::Tick(float deltaTime)
{
	if (DotIntensity > 0) {

		DotIntensity -= deltaTime/3.f;
		if (DotIntensity <= 0) DotIntensity = 0;

		sf::Color temp = getShapeMinimap()->getFillColor();
		temp.a = DotIntensity * 255;
		_ShapeMinimap->setFillColor(temp);
	}
}

void Enemie::resetIntensity()
{
	DotIntensity = 1;
}
