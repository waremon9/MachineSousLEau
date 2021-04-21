#include "Submarine.h"

Submarine::Submarine(sf::Vector2f pos)
{
	Velocity = sf::Vector2f(0, 0);
	ScreenPosition = pos;
	Moving = false;
	Speed = (0.1);

	Sub = new sf::RectangleShape(sf::Vector2f(54,30));
	Sub->setFillColor(sf::Color::Red);
	Sub->setOrigin(27,15);
	Sub->setPosition(ScreenPosition);

	setCoordinate(sf::Vector2f(0, 0));
	setRotation(90);

}

sf::RectangleShape* Submarine::getShape(){	return Sub;}

sf::Vector2f Submarine::getCoordinate() const { return Coordinate; }

sf::Vector2f Submarine::getScreenPosition() const
{
	return ScreenPosition;
}

float Submarine::getRotation() const
{
	return Rotation;
}

void Submarine::motorIsOn(bool b)
{
	Moving = b;
}

void Submarine::addVelocity(sf::Vector2f v)
{
	Velocity += v;
}

void Submarine::addRotation(float rota)
{
	Rotation += rota;
	Sub->setRotation(Rotation);
}

void Submarine::resetVelocity()
{
	Velocity = sf::Vector2f(0, 0);
}

void Submarine::setCoordinate(sf::Vector2f coord)
{
	Coordinate = coord;
} 

void Submarine::setRotation(float rota)
{
	Rotation = rota;
	Sub->setRotation(Rotation);
}

void Submarine::Tick(float deltaTime)
{
	if (Moving) {
		Velocity.x -= cos(Rotation / 180 * 3.1415) * Speed;
		Velocity.y -= sin(Rotation / 180 * 3.1415) * Speed;
	}
	Coordinate += Velocity * deltaTime;
	Velocity /= 1.0005f;
}