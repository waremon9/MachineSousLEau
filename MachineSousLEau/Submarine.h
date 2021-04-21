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
	bool Moving;
	float Speed;

public:
	Submarine(sf::Vector2f);

	sf::RectangleShape* getShape();
	sf::Vector2f getCoordinate() const;
	sf::Vector2f getScreenPosition() const;
	float getRotation() const;

	void motorIsOn(bool);
	void addVelocity(sf::Vector2f);
	void addRotation(float);
	void resetVelocity();

	void setCoordinate(sf::Vector2f);
	void setRotation(float);
	void Tick(float);
};

