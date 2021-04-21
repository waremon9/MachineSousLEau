#pragma once
#include <SFML/Graphics.hpp>

class Enemie;
class Submarine;

class GameManager
{
private:
	static GameManager* Instance;
	GameManager();

	sf::RenderWindow* Window;
	sf::Clock* DeltaClock;
	float DeltaTime;

	std::vector<Enemie*> AllEnemies;
	std::vector<sf::CircleShape*> AllEnemiesIcon;
	Submarine* Player;
	sf::CircleShape* PlayerIcon;
	sf::CircleShape* GameWindow;
	sf::CircleShape* Minimap;
	sf::RectangleShape* rect;
	sf::RectangleShape* rect2;
	sf::RectangleShape* Sonar;

	void updateDeltaTime();
	void processEvent();
	void updateEntity();
	void deleteElement();
	void updateScreen();

	void initialize();

	void UpdateMinimap();
	void UpdateSonar();
	void SpawnEnemie();
	void UpdateSpawnCooldown();
	float RandomFloat(float, float);

	bool RightDown;
	bool LeftDown;

	int MaxEnemieNumber;
	float BaseEnemieSpawnCooldown;
	float EnemieSpawnCooldown;

	float SonarRotation;

public:
	static GameManager* getInstance();

	void gameLoop();

	float distanceTwoPoint(sf::Vector2f, sf::Vector2f);

	sf::RenderWindow* getWindow() const { return Window; }
};

