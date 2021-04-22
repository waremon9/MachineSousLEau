#pragma once
#include <SFML/Graphics.hpp>

class Submarine
{
private:
	sf::RectangleShape* Sub;
	sf::Vector2f Coordinate;
	sf::Vector2f ScreenPosition;
	sf::Vector2f Velocity;
	float Rotation;
	float AccelerationSpeed;
	int motorLevel;
	int MaxMotorLevel;
	int MinMotorLevel;
	float speedPower;

	//Torpedo system
	float baseTorpedoCountdown;
	float torpedoCountdown;
	int torpedoCount;
	int maxTorpedo;

public:
	Submarine(sf::Vector2f);

	sf::RectangleShape* getShape();
	sf::Vector2f getCoordinate() const;
	sf::Vector2f getScreenPosition() const;
	float getRotation() const;
	float getSpeed() const;
	int getMotorLevel() const;
	int getMinMotorLevel() const;
	int getQteMotorLevel() const;

	int getTorpedoCount() const;
	void useTorpedo();

	void addVelocity(sf::Vector2f);
	void addRotation(float);
	void resetVelocity();

	void upgradeMotorLevel();
	void reduceMotorLevel();
	void setSpeedPower();
	void setCoordinate(sf::Vector2f);
	void setRotation(float);
	void Tick(float);
};

