#pragma once
#include <SFML/Graphics.hpp>

class Enemie;
class Submarine;
class Torpedo;

class GameManager
{
private:
	static GameManager* Instance;
	GameManager();

	sf::RenderWindow* Window;
	sf::Clock* DeltaClock;
	float DeltaTime;

	std::vector<Enemie*> AllEnemies;
	std::vector<Torpedo*> AllTorpedo;
	std::vector<sf::CircleShape*> AllEnemiesIcon;
	Submarine* Player;
	sf::CircleShape* PlayerIcon;
	sf::CircleShape* GameWindow;
	sf::CircleShape* Minimap;
	sf::Sprite* SpeedIndicator;
	sf::RectangleShape* rect;
	sf::RectangleShape* rect2;
	sf::RectangleShape* Sonar;
	sf::RectangleShape* SpeedCursor;
	sf::RectangleShape* MotorPower;
	sf::RectangleShape* MotorPowerCursor;

	void updateDeltaTime();
	void processEvent();
	void updateEntity();
	void deleteElement();
	void updateScreen();

	void initialize();

	void UpdateMinimap();
	void UpdateSonar();
	void UpdateSpeedCursor();
	void UpdateMotorLevelCursor();
	void SpawnEnemie();
	void UpdateSpawnCooldown();
	float RandomFloat(float, float);
	void ShootTorpedo();

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

	Submarine* getPlayer() const;
	sf::CircleShape* getGameWindow() const;

	sf::RenderWindow* getWindow() const { return Window; }
};

