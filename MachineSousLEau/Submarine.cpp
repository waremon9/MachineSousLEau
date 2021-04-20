#include "Submarine.h"

Submarine::Submarine()
{
	Sub = new sf::CircleShape(20, 25);
	Sub->setFillColor(sf::Color::Red);
	Sub->setOrigin(20,20);
}

sf::CircleShape* Submarine::getShape(){	return Sub;}

sf::Vector2f Submarine::getPosition() const { return Position; }

void Submarine::setPosition(sf::Vector2f pos)
{
	Position = pos;
	Sub->setPosition(Position);
}

void Submarine::Tick(float deltaTime)
{

}