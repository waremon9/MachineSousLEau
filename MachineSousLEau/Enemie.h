#pragma once
#include <SFML/Graphics.hpp>

class Enemie
{
private:
	sf::CircleShape* _Shape;
	sf::Vector2f Coordinate;
	sf::Vector2f ScreenPosition;

public:
	Enemie();
	Enemie(sf::Vector2f);

	sf::CircleShape* getShape();
	sf::Vector2f getCoordinate() const;

	void setCoordinate(sf::Vector2f);
	void setScreenPosition(sf::Vector2f);
	void Tick(float);
};

