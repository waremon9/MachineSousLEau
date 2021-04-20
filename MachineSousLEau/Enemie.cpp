#include "Enemie.h"

Enemie::Enemie()
{
	_Shape = new sf::CircleShape(15, 20);
	_Shape->setFillColor(sf::Color::Yellow);
	_Shape->setOrigin(15, 15);
}

Enemie::Enemie(sf::Vector2f pos)
{

	_Shape = new sf::CircleShape(15, 20);
	_Shape->setFillColor(sf::Color::Yellow);
	_Shape->setOrigin(15, 15);
	setPosition(pos);
}

sf::CircleShape* Enemie::getShape() { return _Shape; }

sf::Vector2f Enemie::getPosition() const { return Position; }

void Enemie::setPosition(sf::Vector2f pos)
{
	Position = pos;
	_Shape->setPosition(Position);
}

void Enemie::Tick(float deltaTime)
{

}