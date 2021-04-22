#include "Torpedo.h"
#include "GameManager.h"
#include "Submarine.h"


Torpedo::Torpedo(sf::Vector2f coord, float rota)
{
	AccelerationSpeed = 75;
	Speed = 5;
	MaxSpeed = 100;
	LifeSpan = 5;
	Coordinate = coord;
	ScreenPosition = GameManager::getInstance()->getPlayer()->getScreenPosition();
	Rotation = rota;
	Direction = sf::Vector2f(-cos(Rotation/180*3.1415) * Speed, -sin(Rotation/180*3.1415) * Speed);
	Torp = new sf::RectangleShape(sf::Vector2f(8, 4));
	Torp->setOrigin(Torp->getSize() / 2.f);
	Torp->setFillColor(sf::Color::Magenta);
	Torp->setPosition(ScreenPosition);
	Torp->setRotation(Rotation);

	Dead = false;
}

sf::RectangleShape* Torpedo::getShape()
{
	return Torp;
}

sf::Vector2f Torpedo::getCoordinate() const
{
	return Coordinate;
}

sf::Vector2f Torpedo::getScreenPosition() const
{
	return ScreenPosition;
}

bool Torpedo::LifeSpanEnded() const
{
	return LifeSpan <= 0;
}

bool Torpedo::isDead() const
{
	return Dead;
}

void Torpedo::setDead(bool b)
{
	Dead = b;
}

void Torpedo::setCoordinate(sf::Vector2f coord)
{
	Coordinate = coord;
}

void Torpedo::setScreenPosition(sf::Vector2f sp)
{
	ScreenPosition = sp;
	Torp->setPosition(ScreenPosition);
}

void Torpedo::setRotation(float rota)
{
	Rotation = rota;
}
#include <iostream>
void Torpedo::Tick(float dt)
{
	if (Speed < MaxSpeed) {
		Speed += AccelerationSpeed * dt;
		if (Speed >= MaxSpeed) Speed = MaxSpeed;
	}
	Coordinate += Direction * Speed * dt;

	LifeSpan -= dt;
}
