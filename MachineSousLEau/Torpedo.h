#pragma once
#include <SFML/Graphics.hpp>

class Torpedo
{
private:
	sf::RectangleShape* Torp;
	sf::Vector2f Coordinate;
	sf::Vector2f ScreenPosition;
	sf::Vector2f Direction;
	float Speed;
	float AccelerationSpeed;
	float MaxSpeed;
	float Rotation;
	float LifeSpan;

public:
	Torpedo(sf::Vector2f, float);

	sf::RectangleShape* getShape();
	sf::Vector2f getCoordinate() const;
	sf::Vector2f getScreenPosition() const;
	bool LifeSpanEnded() const;

	void setCoordinate(sf::Vector2f);
	void setScreenPosition(sf::Vector2f);
	void setRotation(float);
	void Tick(float);
};

