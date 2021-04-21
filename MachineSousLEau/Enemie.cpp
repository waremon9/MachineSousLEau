#include "Enemie.h"

Enemie::Enemie()
{
	_ShapeMinimap = new sf::CircleShape(3, 10);
	_ShapeMinimap->setFillColor(sf::Color::Yellow);
	_ShapeMinimap->setOrigin(1.5, 1.5);

	_Shape = new sf::CircleShape(15, 20);
	_Shape->setFillColor(sf::Color::Yellow);
	_Shape->setOrigin(15, 15);
}

Enemie::Enemie(sf::Vector2f coord)
{
	_ShapeMinimap = new sf::CircleShape(3, 10);
	_ShapeMinimap->setFillColor(sf::Color::Yellow);
	_ShapeMinimap->setOrigin(1.5, 1.5);

	_Shape = new sf::CircleShape(15, 20);
	_Shape->setFillColor(sf::Color::Yellow);
	_Shape->setOrigin(15, 15);
	setCoordinate(coord);
}

sf::CircleShape* Enemie::getShape() { return _Shape; }

sf::CircleShape* Enemie::getShapeMinimap()
{
	return _ShapeMinimap;
}

sf::Vector2f Enemie::getCoordinate() const { return Coordinate; }

void Enemie::setCoordinate(sf::Vector2f coord)
{
	Coordinate = coord;
}

void Enemie::setScreenPosition(sf::Vector2f pos)
{
	_Shape->setPosition(pos);
}

void Enemie::Tick(float deltaTime)
{

}