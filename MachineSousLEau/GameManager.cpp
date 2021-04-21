#include "GameManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Submarine.h"
#include "Enemie.h"
#include "Torpedo.h"

#define PI 3.14159265

GameManager* GameManager::Instance = nullptr;

GameManager::GameManager() {

}

void GameManager::initialize() {

    srand((unsigned)time(NULL));

    // Create the main window
    Window = new sf::RenderWindow(sf::VideoMode(1500, 850), "SFML window");

    DeltaClock = new sf::Clock;
    DeltaTime = 0;

    MaxEnemieNumber = 100;
    BaseEnemieSpawnCooldown = EnemieSpawnCooldown = 0.8;

    //LeftPanel
    rect = new sf::RectangleShape(sf::Vector2f(650, 850));
    rect->setFillColor(sf::Color(100, 180, 100, 70));
    rect->setOutlineColor(sf::Color::Green);
    rect->setOutlineThickness(-5);
    //RightPanel
    rect2 = new sf::RectangleShape(sf::Vector2f(850, 850));
    rect2->setFillColor(sf::Color(100, 100, 100, 150));
    rect2->setPosition(650, 0);
    //GameCamera
    GameWindow = new sf::CircleShape(850 / 2, 80);
    GameWindow->setFillColor(sf::Color(14,28,70));
    GameWindow->setOutlineColor(sf::Color::Green);
    GameWindow->setOutlineThickness(-5);
    GameWindow->setPosition(650, 0);
    //Minimap
    Minimap = new sf::CircleShape(120, 40);
    Minimap->setFillColor(sf::Color::Black);
    Minimap->setOutlineColor(sf::Color::Green);
    Minimap->setOutlineThickness(-2);
	Minimap->setPosition(20, 20);
	//Minimap sonar
	Sonar = new sf::RectangleShape(sf::Vector2f(Minimap->getRadius(), 2));
    Sonar->setFillColor(sf::Color::Green);
    Sonar->setOrigin(0, Sonar->getSize().y / 2.f);
    Sonar->setPosition(Minimap->getPosition().x + Minimap->getRadius(), Minimap->getPosition().y + Minimap->getRadius());
    //Player minimap icon
    PlayerIcon = new sf::CircleShape(5, 10);
    PlayerIcon->setFillColor(sf::Color::Red);
    PlayerIcon->setOrigin(5, 5);
    PlayerIcon->setPosition(Minimap->getPosition() + sf::Vector2f(Minimap->getRadius(), Minimap->getRadius()));

    Player = new Submarine(GameWindow->getPosition() + sf::Vector2f(GameWindow->getRadius(), GameWindow->getRadius()));
    Player->setCoordinate(GameWindow->getPosition() + sf::Vector2f(GameWindow->getRadius(), GameWindow->getRadius()));

    SpawnEnemie();
}

void GameManager::gameLoop() {
    //game loop
    while (Window->isOpen())
    {
        updateDeltaTime();

        processEvent();

        updateEntity();

        deleteElement();

        updateScreen();
    }
}

float GameManager::distanceTwoPoint(sf::Vector2f a, sf::Vector2f b)
{
    float X = (a.x - b.x);
    float Y = (a.y - b.y);

    return abs(sqrt(X * X + Y * Y));
}

Submarine* GameManager::getPlayer() const
{
    return Player;
}

sf::CircleShape* GameManager::getGameWindow() const
{
    return GameWindow;
}

void GameManager::updateDeltaTime()
{
    DeltaTime = DeltaClock->getElapsedTime().asSeconds();
    DeltaClock->restart();
}

void GameManager::processEvent()
{
    //Process event
    sf::Event event;
    while (Window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            Window->close();

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
            Player->motorIsOn(true);
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
            Player->motorIsOn(false);
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right))
            RightDown = true;
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))
            LeftDown = true;

        if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Right))
            RightDown = false;
        if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Left))
            LeftDown = false;

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
            ShootTorpedo();
    }
}

void GameManager::updateEntity()
{
    UpdateSpawnCooldown();

    for (Enemie* e : AllEnemies) {
        e->Tick(DeltaTime);
    }

    UpdateMinimap();

    float RotationSpeed = 0.01;
    if (RightDown) Player->addRotation(RotationSpeed);
    if (LeftDown) Player->addRotation(-RotationSpeed);

    Player->Tick(DeltaTime);

    for (Torpedo* t : AllTorpedo) {
        t->Tick(DeltaTime);
    }
}

void GameManager::deleteElement()
{
	for (int i = AllEnemies.size() - 1; i >= 0; i--) {
		if (distanceTwoPoint(AllEnemies[i]->getCoordinate(), Player->getCoordinate()) > 2000) {
			delete AllEnemies[i];
			AllEnemies.erase(AllEnemies.begin() + i);
		}
	}

	for (int i = AllTorpedo.size() - 1; i >= 0; i--) {
		if (AllTorpedo[i]->LifeSpanEnded()) {
			delete AllTorpedo[i];
            AllTorpedo.erase(AllTorpedo.begin() + i);
		}
	}
}

void GameManager::updateScreen()
{
    // Clear screen
    Window->clear();

    //Panel
    Window->draw(*rect);
    Window->draw(*rect2);

    //Game right panel
    Window->draw(*GameWindow);
    Window->draw(*Player->getShape());

    for (Enemie* e : AllEnemies) {
        sf::Vector2f relativePosition(e->getCoordinate() - Player->getCoordinate());

        if (distanceTwoPoint(e->getCoordinate(), Player->getCoordinate()) < GameWindow->getRadius() + GameWindow->getOutlineThickness()) {
            e->setScreenPosition(Player->getScreenPosition() + relativePosition);

            Window->draw(*e->getShape());
        }
    }

    for (Torpedo* t : AllTorpedo) {
		sf::Vector2f relativePosition(t->getCoordinate() - Player->getCoordinate());

		if (distanceTwoPoint(t->getCoordinate(), Player->getCoordinate()) < GameWindow->getRadius() + GameWindow->getOutlineThickness()) {
			t->setScreenPosition(Player->getScreenPosition() + relativePosition);

			Window->draw(*t->getShape());
		}
    }

    Window->draw(*Minimap);
    for (Enemie* e : AllEnemies) {
        if (distanceTwoPoint(e->getShapeMinimap()->getPosition(), PlayerIcon->getPosition()) < Minimap->getRadius() + Minimap->getOutlineThickness()){
            Window->draw(*e->getShapeMinimap());
        }
    }
    UpdateSonar();
	Window->draw(*Sonar);
	Window->draw(*PlayerIcon);

    // Update the window
    Window->display();
}

GameManager* GameManager::getInstance()
{
    if (Instance == nullptr) {
        Instance = new GameManager();
        Instance->initialize();
    }
    return Instance;
}

void GameManager::UpdateMinimap()
{
    AllEnemiesIcon.clear();
    sf::Vector2f posP = Player->getCoordinate();
    for (Enemie* e : AllEnemies) {
        sf::Vector2f posE = e->getCoordinate();

        float x = (posP.x - posE.x);
        float y = (posP.y - posE.y);

        float Distance = sqrt(x * x + y * y);
        float Angle = std::atan2(y, -x);

        Angle = Angle - (90 - Player->getRotation()) / 180*PI;

        float reduction = 10;

        float xP = PlayerIcon->getPosition().x + (1.f / reduction) * Distance * std::cos(Angle);
        float yP = PlayerIcon->getPosition().y - (1.f / reduction) * Distance * std::sin(Angle);

        sf::CircleShape* icon = e->getShapeMinimap();
        icon->setPosition(xP, yP);
    }
}

void GameManager::UpdateSonar()
{
    SonarRotation += DeltaTime * 135;
    if(SonarRotation>=360) SonarRotation-=360;
    Sonar->setRotation(SonarRotation);

    for (Enemie* e : AllEnemies) {
        sf::Vector2f angle(e->getShapeMinimap()->getPosition() - PlayerIcon->getPosition());
        float RotaEnemie = atan2(angle.y,angle.x) * 180 / PI;
        while (RotaEnemie >= 360) RotaEnemie -= 360;
        while (RotaEnemie < 0) RotaEnemie += 360;

        if (SonarRotation - RotaEnemie <= 0.5 && SonarRotation - RotaEnemie >0) e->resetIntensity();
    }
}

void GameManager::SpawnEnemie()
{
    float maxSpawingDistance = 1500;
    float minSpawningDistance = GameWindow->getRadius() * 1.1f;

    float randomDistance = RandomFloat(minSpawningDistance, maxSpawingDistance);
    float randomAngle = RandomFloat(0, 360);

    sf::Vector2f randomRelativeCoordinate(cos(randomAngle / 180 * 3.1415) * randomDistance, sin(randomAngle / 180 * 3.1415) * randomDistance);

    AllEnemies.push_back(new Enemie(randomRelativeCoordinate + Player->getCoordinate()));
}

void GameManager::UpdateSpawnCooldown()
{
    EnemieSpawnCooldown -= DeltaTime;

    int QteSpawn = 1;

    if (EnemieSpawnCooldown <= 0) {
        EnemieSpawnCooldown = BaseEnemieSpawnCooldown;
        for (int i = 0; i < QteSpawn; i++) {
            if (AllEnemies.size() <= MaxEnemieNumber)SpawnEnemie();
        }
    }
}

float GameManager::RandomFloat(float LO, float HI)
{
    return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
}

void GameManager::ShootTorpedo()
{
    AllTorpedo.push_back(new Torpedo(Player->getCoordinate(), Player->getRotation()));
}
