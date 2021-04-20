#pragma once
#include <SFML/Graphics.hpp>

class Submarine
{
private:
	sf::CircleShape* Sub;
	sf::Vector2f Position;

public:
	Submarine();

	sf::CircleShape* getShape();
	sf::Vector2f getPosition() const;

	void setPosition(sf::Vector2f);
	void Tick(float);
};

