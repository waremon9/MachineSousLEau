#pragma once
#include <SFML/Graphics.hpp>

class Enemie
{
private:
	sf::CircleShape* _Shape;
	sf::CircleShape* _ShapeMinimap;
	float DotIntensity;
	sf::Vector2f Coordinate;
	sf::Vector2f ScreenPosition;
	bool Dead;

public:
	Enemie();
	Enemie(sf::Vector2f);

	sf::CircleShape* getShape();
	sf::CircleShape* getShapeMinimap();
	sf::Vector2f getCoordinate() const;
	bool getDead() const;

	void setCoordinate(sf::Vector2f);
	void setScreenPosition(sf::Vector2f);
	void setDead(bool);
	void Tick(float);
	void resetIntensity();
};

