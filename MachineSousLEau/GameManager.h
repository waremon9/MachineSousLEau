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
	sf::CircleShape* TorpedoTimer;
	sf::CircleShape* FuelWarning;
	sf::Sprite* SpeedIndicator;
	sf::Sprite* FuelIndicator;
	sf::RectangleShape* FuelCursor;
	sf::RectangleShape* rect;
	sf::RectangleShape* rect2;
	sf::RectangleShape* Sonar;
	sf::RectangleShape* SpeedCursor;
	sf::RectangleShape* TorpedoTimercursor;
	sf::RectangleShape* MotorPower;
	sf::RectangleShape* MotorPowerCursor;
	std::vector<sf::RectangleShape*> TorpedoCharged;
	sf::Texture* BackgroundText;
	std::vector<sf::RectangleShape*> OxygenJauges;
	std::vector<sf::RectangleShape*> OxygenJaugesContent;
	sf::Font* arial;
	sf::Text* MinimapText;
	sf::Text* TorpedoText;
	sf::Text* OxygenText;

	void updateDeltaTime();
	void processEvent();
	void updateEntity();
	void deleteElement();
	void updateScreen();

	void initialize();

	void UpdateMinimap();
	void UpdateSonar();
	void UpdateSpeedCursor();
	void UpdateFuelCursor();
	void UpdateMotorLevelCursor();
	void SpawnEnemie();
	void UpdateSpawnCooldown();
	float RandomFloat(float, float);
	void ShootTorpedo();
	void updateFuelWarning();
	void updateOxygenLevel();
	void RefillOxygen();

	bool RightDown;
	bool LeftDown;

	bool FuelWarningIntensityUp;
	float FuelWarningIntensity;

	int MaxEnemieNumber;
	float BaseEnemieSpawnCooldown;
	float EnemieSpawnCooldown;

	float SonarRotation;

	float OxygenLevelMax;
	float OxygenLevel;
	int OxygenJaugeNumber;

public:
	static GameManager* getInstance();

	void gameLoop();

	float distanceTwoPoint(sf::Vector2f, sf::Vector2f);

	Submarine* getPlayer() const;
	sf::CircleShape* getGameWindow() const;

	void UpdateTimerCursor(float);

	void CollisionCheck();

	sf::RenderWindow* getWindow() const { return Window; }
};

