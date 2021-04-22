#include "Submarine.h"
#include <iostream>

Submarine::Submarine(sf::Vector2f pos)
{
	Velocity = sf::Vector2f(0, 0);
	ScreenPosition = pos;
	AccelerationSpeed = (0.1);

	MaxMotorLevel = 3;
	MinMotorLevel = -1;
	motorLevel = 0;
	baseTorpedoCountdown = 1;
	torpedoCountdown = baseTorpedoCountdown;
	maxTorpedo = 5;
	torpedoCount = 0;

	gasolineLevel = 100;

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
	float dist = sqrt(Velocity.x * Velocity.x + Velocity.y * Velocity.y);
	if (atan2f(-Velocity.y, -Velocity.x) * 180 / 3.1415 >= Rotation - 80 && atan2f(-Velocity.y, -Velocity.x) * 180 / 3.1415 <= Rotation + 80) return dist;
	else return -dist;
}

int Submarine::getMotorLevel() const
{
	return motorLevel;
}

int Submarine::getMinMotorLevel() const
{
	return MinMotorLevel;
}

int Submarine::getQteMotorLevel() const
{
	return MaxMotorLevel - MinMotorLevel;
}

int Submarine::getTorpedoCount() const
{
	return torpedoCount;
}

int Submarine::getMaxTorpedo() const
{
	return maxTorpedo;
}

void Submarine::useTorpedo()
{
	if (torpedoCount > 0)
	{
		torpedoCount--;
	}
}

float Submarine::getGasoline() const
{
	return gasolineLevel;
}

void Submarine::fillGasoline()
{
	gasolineLevel = 100;
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
	if (motorLevel < MaxMotorLevel)
	{
		motorLevel++;
		setSpeedPower();
	}
}

void Submarine::reduceMotorLevel()
{
	if (motorLevel > MinMotorLevel)
	{
		motorLevel--;
		setSpeedPower();
	}
}

void Submarine::setSpeedPower()
{
	speedPower = (1.f / MaxMotorLevel) * motorLevel;
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

	if (gasolineLevel > 0) gasolineLevel -= deltaTime;
	std::cout << "\n" + std::to_string(gasolineLevel);

	if (gasolineLevel > 0)
	{
		Velocity.x -= cos(Rotation / 180 * 3.1415) * AccelerationSpeed * speedPower;
		Velocity.y -= sin(Rotation / 180 * 3.1415) * AccelerationSpeed * speedPower;
	}
	

	Coordinate += Velocity * deltaTime;
	Velocity /= 1.0005f;


	if(torpedoCount < maxTorpedo) torpedoCountdown-= deltaTime;
	if (torpedoCountdown <= 0)
	{
		torpedoCountdown = baseTorpedoCountdown;
		torpedoCount++;
	}
}