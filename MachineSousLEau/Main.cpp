#include <SFML/Graphics.hpp>
#include <vector>
#include "Submarine.h"
#include "Enemie.h"
#include <iostream>

#define PI 3.14159265

void UpdateMinimap();

std::vector<Enemie*> AllEnemies;
std::vector<sf::CircleShape> AllEnemiesIcon;
Submarine* Player;
sf::CircleShape* PlayerIcon;
sf::CircleShape* GameWindow;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(1500, 850), "SFML window");

	//LeftPanel
	sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(650, 850));
	rect->setFillColor(sf::Color(100, 180, 100, 70));
	rect->setOutlineColor(sf::Color::Green);
	rect->setOutlineThickness(-5);
	//RightPanel
	sf::RectangleShape* rect2 = new sf::RectangleShape(sf::Vector2f(850, 850));
	rect2->setFillColor(sf::Color(100, 100, 100, 150));
	rect2->setPosition(650, 0);
	//GameCamera
	GameWindow = new sf::CircleShape(850 / 2, 80);
	GameWindow->setFillColor(sf::Color::Black);
	GameWindow->setOutlineColor(sf::Color::Green);
	GameWindow->setOutlineThickness(-5);
	GameWindow->setPosition(650, 0);
	//Minimap
	sf::CircleShape* Minimap = new sf::CircleShape(120, 40);
	Minimap->setFillColor(sf::Color::Black);
	Minimap->setOutlineColor(sf::Color::Green);
	Minimap->setOutlineThickness(-2);
	Minimap->setPosition(20, 20);
	//Player minimap icon
	PlayerIcon = new sf::CircleShape(5, 10);
	PlayerIcon->setFillColor(sf::Color::Red);
	PlayerIcon->setOrigin(5, 5);
	PlayerIcon->setPosition(Minimap->getPosition() + sf::Vector2f(Minimap->getRadius(), Minimap->getRadius()));

	Player = new Submarine();
	Player->setPosition(GameWindow->getPosition() + sf::Vector2f(GameWindow->getRadius(), GameWindow->getRadius()));

	AllEnemies.push_back(new Enemie(GameWindow->getPosition() + sf::Vector2f(265,565)));
	AllEnemies.push_back(new Enemie(GameWindow->getPosition() + sf::Vector2f(265+50,565)));
	AllEnemies.push_back(new Enemie(GameWindow->getPosition() + sf::Vector2f(265+100,565)));
	AllEnemies.push_back(new Enemie(GameWindow->getPosition() + sf::Vector2f(265+150,565)));
	AllEnemies.push_back(new Enemie(GameWindow->getPosition() + sf::Vector2f(265+200,565)));
	AllEnemies.push_back(new Enemie(GameWindow->getPosition() + sf::Vector2f(265+250,565)));
	//AllEnemies.push_back(new Enemie(GameWindow->getPosition() + sf::Vector2f(700,386)));
	//AllEnemies.push_back(new Enemie(GameWindow->getPosition() + sf::Vector2f(250,352)));


	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		UpdateMinimap();

		// Clear screen
		window.clear();

		window.draw(*rect);
		window.draw(*rect2);

		window.draw(*GameWindow);
		window.draw(*Player->getShape());

		for (Enemie* e : AllEnemies) {
			window.draw(*e->getShape());
		}

		window.draw(*Minimap);
		window.draw(*PlayerIcon);
		for (sf::CircleShape cs : AllEnemiesIcon) {
			window.draw(cs);
		}

		// Update the window
		window.display();
	}

	return 0;
}

void UpdateMinimap() {
	AllEnemiesIcon.clear();
	sf::Vector2f posP = Player->getPosition() - GameWindow->getPosition();
	for (Enemie* e : AllEnemies) {
		sf::Vector2f posE = e->getPosition() - GameWindow->getPosition();

		float x = (posE.x - posP.x);
		float y = (posE.y - posP.y);

		float Distance = sqrt(x * x + y * y);
		float Angle = std::atan(y / x);

		float xP = PlayerIcon->getPosition().x - (1.f / 6.f) * Distance * std::cos(Angle);
		float yP = PlayerIcon->getPosition().y - (1.f / 6.f) * Distance * std::sin(Angle);

		sf::CircleShape icon(3, 10);
		icon.setFillColor(sf::Color::Yellow);
		icon.setOrigin(1.5, 1.5);
		icon.setPosition(xP, yP);
		AllEnemiesIcon.push_back(icon);
	}
}