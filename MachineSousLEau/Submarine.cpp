#include "Submarine.h"

Submarine::Submarine(sf::Vector2f pos)
{
	Velocity = sf::Vector2f(0, 0);
	ScreenPosition = pos;
	AccelerationSpeed = (0.1);


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

float Submarine::getSpeed() const
{
	return sqrt(Velocity.x * Velocity.x + Velocity.y * Velocity.y);
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

void Submarine::upgradeMotorLevel()
{
	if (motorLevel < 3)
	{
		motorLevel++;
		setSpeedPower();
	}
}

void Submarine::reduceMotorLevel()
{
	if (motorLevel > 0)
	{
		motorLevel--;
		setSpeedPower();
	}
}

void Submarine::setSpeedPower()
{
	speedPower = (1.f / 3.f) * motorLevel;
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
	Velocity.x -= cos(Rotation / 180 * 3.1415) * AccelerationSpeed * speedPower;
	Velocity.y -= sin(Rotation / 180 * 3.1415) * AccelerationSpeed * speedPower;

	Coordinate += Velocity * deltaTime;
	Velocity /= 1.0005f;
}