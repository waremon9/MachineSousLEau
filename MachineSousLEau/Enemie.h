#pragma once
#include <SFML/Graphics.hpp>

class Enemie
{
private:
	sf::CircleShape* _Shape;
	sf::Vector2f Position;

public:
	Enemie();
	Enemie(sf::Vector2f);

	sf::CircleShape* getShape();
	sf::Vector2f getPosition() const;

	void setPosition(sf::Vector2f);
	void Tick(float);
};

